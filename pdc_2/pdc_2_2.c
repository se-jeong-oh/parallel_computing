#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// array의 길이
#define ARRAY_LEN 7 

int n_size_;  // 프로세스의 총 갯수
int n_rank_;  // 각 프로세스에 부여된 랭크
int num[ARRAY_LEN] = {1,2,3,4,5,6,7};

int main(int argc, char *argv[]) {
    // MPI 초기화
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &n_size_);
    MPI_Comm_rank(MPI_COMM_WORLD, &n_rank_);

    int block_len, i, j, k = 0;

    if(ARRAY_LEN % n_size_ == 0) block_len = ARRAY_LEN / n_size_;
    else block_len = ARRAY_LEN / n_size_ + 1;
    int array_len = block_len * n_size_;

    int *send_num = (int *)calloc(sizeof(int),block_len);
    int *result = (int *)calloc(sizeof(int),array_len);
    int *total = (int *)calloc(sizeof(int),array_len);
    int *recv = (int *)calloc(sizeof(int),array_len);
    int *r_num = (int *)calloc(sizeof(int),array_len);

    for(i=0;i<ARRAY_LEN;i++) r_num[i] = num[i];

    if (n_rank_ == 0) {
        // 랭크가 0 인 프로세스
        fprintf(stdout, "We have %d processess.\n", n_size_);
    }

    // 모든 프로세스가 여기에 도달할 때 까지 대기
    MPI_Barrier(MPI_COMM_WORLD);

    /*
        Algorithm 1
        전체 배열의 길이를 process의 길이만큼 나눈 다음에 각 프로세스마다 할당.
    */
    // 수열의 형태를 각 프로세스에게 element_wise 하게 변형
    j = 0;
    for(i=n_rank_;i<array_len;i+=n_size_) {
        send_num[j] = r_num[i];
        j++;
    }
    MPI_Scan(send_num, &total[n_rank_*block_len], block_len, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allgather(&total[n_rank_*block_len], block_len, MPI_INT, recv, block_len, MPI_INT, MPI_COMM_WORLD);
    if(n_rank_==0){
        for(i=0;i<block_len;i++)
            for(j=0;j<array_len;j+=block_len) {
                result[k] = recv[i+j];
                k++;
            }
        
        for(i=0;i<array_len;i++) {
            if(i<n_size_) continue;
            else result[i] += result[i-(i%n_size_)-1];
        }

        for(i=0;i<ARRAY_LEN;i++) printf("%d ", result[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}