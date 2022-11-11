- build 방법
    - mpicc pdc_2.2.c 로 컴파일
    - 혹은 make 명령어 실행

    <local로 실행시>
    - mpiexec -n <process_num> <executable file>로 실행한다.
        - ex) mpiexec -n 4 ./prefix_sum로 실행
        
    <cluster로 실행시>
    - mpiexec -np <process_num> -mca btl ^openib -hostfile <hostfile_name> <executable_file>
        - ex) mpiexec -np 15 -mca btl ^openib -hostfile hosts ./prefix_sum

- 실행 예시 및 채점 시 특이사항
    - 로컬에서 각 process가 실행되는 것을 확인함
    - cspro2에서 실행 시 cspro1, 2, 3, 5, 7 cluster에서 실행되는 것을 확인함.

****************실행 예시*****************************************
cse20181655@cspro:~/pdc/pdc_2$ mpiexec -np 5 -mca btl ^openib -hostfile hosts ./prefix_sum
We have 5 processess, Using METHOD 1. Length of Array is 13.
Randomly generate array.
Initial array : 881 416 173 152 226 504 866 232 44 548 794 511 806 
Prefix sum : 881 1297 1470 1622 1848 2352 3218 3450 3494 4042 4836 5347 6153 
Process (0) Elapsed Time : 0.000062
Process (1) Elapsed Time : 0.000057
Process (2) Elapsed Time : 0.000055
Process (3) Elapsed Time : 0.000046
Process (4) Elapsed Time : 0.000053
*******************************************************************

- constants
    - METHOD : 1, 2, 3에 따라서 각각에 맞는 방법으로 prefix sum을 계산한다. 1과 2는 MPI_Scan을 활용한 방법이고, 3은 MPI_Send와 MPI_Recv를 활용한 방법이다.
    - RANDOM : 해당 값이 TRUE일 경우, ARRAY_LEN에 해당하는 길이 만큼의 array를 random하게 만든다. FALSE일 경우, array가 1부터 1씩 증가하며 값이 채워진다.
    - ARRAY_LEN : 배열의 길이를 뜻한다.