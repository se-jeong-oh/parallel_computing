#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<pthread.h>

#define BUF_SIZE 100

void * handle_serv(void * arg);
pthread_mutex_t mutx;

int main(int argc, char* argv[])
{
    int my_sock;
    struct sockaddr_in serv_addr;
    int str_len;
    int idx, i;
    pthread_t t_id[5];
    int result;
    int port_num;
    int thread_num;
    //char message[100];
    srand((unsigned)time(NULL));
    pthread_mutex_init(&mutx, NULL);
    /*
    char req[4][100] = {"GET / /var/tmp/cse20181655/a.html",
                        "GET / /var/tmp/cse20181655/b.html",
                        "GET / /var/tmp/cse20181655/c.html",
                        "GET / /var/tmp/cse20181655/d.html"};
                        */
    if(argc != 4)
    {
        printf("%s <IP> <PORT> <thread_num>\n", argv[0]);
        exit(1);
    }
    /*
    my_sock = socket(PF_INET,SOCK_STREAM,0); 
    if(my_sock == -1)
        printf("socket error \n");
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    if(connect(my_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
        printf("connect error\n");
    */
    port_num = atoi(argv[2]);
    thread_num = atoi(argv[3]);
    for(i=0;i<thread_num;i++) {
        pthread_create(&t_id[i], NULL, handle_serv, (void *)&port_num);
        //pthread_join(t_id[i], (void *)&result);
        //pthread_detach(t_id[i]);
        /*
        idx = rand()%4;
        write(my_sock, req[idx], sizeof(req[idx])); // 서버로 요청
        while(read(my_sock,message,sizeof(message))) {
            if (strcmp(message, "</body>\n") == 0)
                break;
            printf("%s", message);
            if (strcmp(message, "404 Not Found\n") == 0)
                break;
        }
        //printf("%s", message); // 한번 요청하고 종료        
        //sleep(3);
        //str_len = read(my_sock,message,sizeof(message));
        //if(str_len==-1)
        //    printf("read error\n");
        //printf("%s \n", message);
        */
    }
    
    for(i=0;i<thread_num;i++) {
        pthread_join(t_id[i], (void *)&result);
    }
    
    //close(my_sock);
    return 0;
}
void * handle_serv(void * arg)
{
    int port_num = *((int *)arg);
    int my_sock;
    int idx;
    int i;
    int bytes = 0;
    struct sockaddr_in serv_addr;
    char message[100];
    char req[4][100] = {"GET / /var/tmp/cse20181655/a.html",
                    "GET / /var/tmp/cse20181655/b.html",
                    "GET / /var/tmp/cse20181655/c.html",
                    "GET / /var/tmp/cse20181655/d.html"};
    my_sock = socket(PF_INET,SOCK_STREAM,0); 
    if(my_sock == -1)
        printf("socket error \n");
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serv_addr.sin_port=htons(port_num);
    if(connect(my_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
        printf("connect error\n");
    for(i=0;i<5;i++){
        idx = rand()%4;
        //pthread_mutex_lock(&mutx);
        //printf("%d", i);
        write(my_sock, req[idx], sizeof(req[idx]));
        //pthread_mutex_unlock(&mutx);
        //pthread_mutex_lock(&mutx);
        while(read(my_sock,message,sizeof(message))) {
            bytes += strlen(message);
            if (strcmp(message, "</body>\n") == 0)
                break;
            printf("%s", message);            
            if (strcmp(message, "404 Not Found\n") == 0) {
                break;
            }
        }
        //pthread_mutex_unlock(&mutx);
        sleep(rand()%3);
        //pthread_mutex_unlock(&mutx);
    }
    printf("%d bytes received from server.\n", bytes);
    close(my_sock);
    return NULL;
}