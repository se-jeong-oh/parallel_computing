#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>

char dict[25145][25]; // words.txt has 25144 words, which max length is 24
char rev_dict[25145][25]; // words that reversed
char org_dict[25145][25]; // words not changed
#define LEN 25144
int find_word(char word[]);
int main(int argc, char *argv[])
{
    int threads = atoi(argv[1]);
    omp_set_num_threads(threads);
    char input_name[100];
    strcpy(input_name, argv[2]);
    char output_name[100];
    strcpy(output_name, argv[3]);
    
    FILE *fp = fopen(input_name, "r");
    char buf[1024];
    char rev_buf[1024];
    int i = 0, j = 0, k = 0, idx, len;
    memset(buf, 0, sizeof(buf));
    memset(dict, 0, 25145*25*sizeof(char));
    
    while(fgets(buf, sizeof(buf), fp)) {
        strcpy(org_dict[i], buf);
        for(j=0;j<strlen(buf);j++) {
            if(buf[j] >= 'A' && buf[j] <= 'Z')
                buf[j] += 32;
        }
        buf[strlen(buf)-2] = '\0';
        len = strlen(buf);
        for(j=len-1;j>=0;j--)
            rev_buf[len-1-j] = buf[j];
        rev_buf[len] = '\0';
        strcpy(rev_dict[i], rev_buf); // save words to reversed.
        strcpy(dict[i], buf); // save words to dictionary, sorted.
        i++;
    }
    fclose(fp);
    fp = fopen(output_name,"w");
    double start = omp_get_wtime();

#pragma omp parallel for
    for (i=0;i<LEN;i++) {
        if(find_word(rev_dict[i]) != -1) {
            fputs(org_dict[i], fp);
        }
    }
    printf("Elapsed Time: %f\n", omp_get_wtime()-start);
    //idx = strlen(rev_dict[11]);
    //printf("%d\n", strcmp(dict[11], rev_dict[11]));
    //idx = find_word(dict[11]);
    //printf("%c", dict[12][4]);
    fclose(fp);
}

int find_word(char word[])
{
    int end = LEN;
    int start = 0;
    int idx = (end + start) / 2;
    int mid = (end + start) / 2;
    int rlt = strcmp(word, dict[mid]);
    int buf;
    for(rlt;rlt!=0;rlt=strcmp(word,dict[mid])) {
        //printf("%s %d %d\n", word, mid, rlt);
        if (rlt < 0)
            end = mid;
        else
            start = mid;
        mid = (end + start) / 2;
        if(mid == end || mid == start) {
            mid = -1;
            break;
        }
    }
    return mid;
}