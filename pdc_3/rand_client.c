#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rand.h"


void main(int argc, char *argv[]) {
    int iters,i;
    long myseed;
    CLIENT *clnt;
    void *result_1;
    double *result_2;
    int *result;
    char *arg;
    char *strings = (char *)malloc(sizeof(char)*50);
    if ( argc != 3 ) {
        fprintf(stderr, "Usage: %s host txt\n", argv[0]);
        exit(1);
    }
    //while(1) continue;
    clnt = clnt_create(argv[1], RAND_PROG, RAND_VERS, "udp");
    if ( clnt == (CLIENT *) NULL ) {
        printf("err");
        clnt_pcreateerror(argv[1]);
        exit(1);
    }
    strcpy(strings, argv[2]);

    result = initialize_random_1(&strings,clnt);
    /*
    if (result_1 == (void *) NULL) {
        clnt_perror(clnt, "call failed");
    }
    //printf("%s\n", buf);
    result_2 = get_next_random_1(buf, clnt);
    if (result_2 == (double *) NULL) {
        clnt_perror(clnt, "call failed");
    }
    else {
        printf("%f\n", *result_2);
    }*/
    printf("%d\n", *result);

    clnt_destroy(clnt);
    exit(0);
}
