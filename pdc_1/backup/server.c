#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/stat.h>

#define BUF_SIZE 100
#define MAX_CLNT 256

void * handle_clnt(void * arg);
void send_msg(char * msg, int len, void * arg);
void error_handling(char * msg);

int clnt_cnt=0;            // 서버에 접속한 클라이언트의 소켓 관리를 위한 변수와 배열
int clnt_socks[MAX_CLNT];  // 이 둘은 접근과 관련있는 코드가 임계영역을 구성하게 됨에 주목하자.
pthread_mutex_t mutx;

int main(int argc, char *argv[])
{
   int serv_sock, clnt_sock;
   struct sockaddr_in serv_adr, clnt_adr;
   int clnt_adr_sz;
   int thread_number, i;
   pthread_t t_id;
   if(argc!=2) {
      printf("Usage : %s <port>\n", argv[0]);
      exit(1);
   }
   /*
   if(argc!=3) {
      printf("Usage : %s <port> <thread_number>\n", argv[0]);
      exit(1);
   }
   */
   //thread_number = atoi(argv[2]);
   pthread_mutex_init(&mutx, NULL);
   serv_sock=socket(PF_INET, SOCK_STREAM, 0);

   memset(&serv_adr, 0, sizeof(serv_adr));
   serv_adr.sin_family=AF_INET; 
   serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
   serv_adr.sin_port=htons(atoi(argv[1]));
   
   if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
      error_handling("bind() error");
   if(listen(serv_sock, 5)==-1)
      error_handling("listen() error");
   /*
   for(i=0;i<thread_number;i++) {
      pthread_create(&t_id[i], NULL, handle_clnt, (void*)&clnt_sock);
   }
   */
  while(1)
   {
      clnt_adr_sz=sizeof(clnt_adr);
      clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr,&clnt_adr_sz);
      pthread_mutex_lock(&mutx);
      clnt_socks[clnt_cnt++]=clnt_sock;
      pthread_mutex_unlock(&mutx);
   
      pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);
      pthread_detach(t_id);
      printf("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));
   }
   close(serv_sock);
   return 0;
}
   
void * handle_clnt(void * arg)
{
   int clnt_sock=*((int*)arg);
   int str_len=0, i;
   char msg[BUF_SIZE];
   
   while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0)
      send_msg(msg, str_len, arg);
   
   pthread_mutex_lock(&mutx);
   for(i=0; i<clnt_cnt; i++)   // remove disconnected client
   {
      if(clnt_sock==clnt_socks[i])
      {
         while(i++<clnt_cnt-1)
            clnt_socks[i]=clnt_socks[i+1];
         break;
      }
   }
   clnt_cnt--;
   pthread_mutex_unlock(&mutx);
   close(clnt_sock);
   return NULL;
}
void send_msg(char * msg, int len, void * arg)   // send to all
{
   // GET / <PATH> 의 형태
   int i;
   char *save_ptr;
   char *parse_ptr;
   char *cp_msg = (char *)malloc(sizeof(char)*100);
   char *file_name = (char *)malloc(sizeof(char)*100);
   char *file_cont = (char *)malloc(sizeof(char)*100);;
   struct stat sb;
   int clnt_sock=*((int*)arg);
   FILE *fp;
   printf("check!!");
   //pthread_mutex_lock(&mutx);
   strncpy(cp_msg, msg, strlen(msg)+1);
   //pthread_mutex_unlock(&mutx);
   parse_ptr = strtok_r(cp_msg, " ", &save_ptr);
   if (strcmp(parse_ptr, "GET")!=0) {
      printf("Only GET POSSIBLE\n");
      return;
   }
   parse_ptr = strtok_r(NULL, " ", &save_ptr); // ignore '/'
   parse_ptr = strtok_r(NULL, " ", &save_ptr); // PATH
   //pthread_mutex_lock(&mutx);
   strncpy(file_name, parse_ptr, sizeof(parse_ptr)+1); // /var/tmp/cse20181655/
   //pthread_mutex_unlock(&mutx);
   if (stat(file_name, &sb) < 0)
      write(clnt_sock, "404 Not Found", 14);
      //printf("404 Not Found");
   
   fp = fopen(file_name, "r");
   pthread_mutex_lock(&mutx);
   while(fgets(file_cont, sizeof(file_cont), fp)) {
      write(clnt_sock, file_cont, strlen(file_cont));
   }
   pthread_mutex_unlock(&mutx);
   //fflush(stdout);
   //pthread_mutex_lock(&mutx);
   //for(i=0; i<clnt_cnt; i++)
    //  write(clnt_socks[i], msg, len);
   //pthread_mutex_unlock(&mutx);
}
void error_handling(char * msg)
{
   fputs(msg, stderr);
   fputc('\n', stderr);
   exit(1);
}