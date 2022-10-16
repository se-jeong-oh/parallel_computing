#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char* argv[])
{
    int my_sock;
    struct sockaddr_in serv_addr;
    int str_len;
    char message[100];
    char req[100] = "GET / /var/tmp/cse20181655/a.html";
    if(argc != 3)
    {
        printf("%s <IP> <PORT>\n", argv[0]);
        exit(1);
    }
    my_sock = socket(PF_INET,SOCK_STREAM,0); 
    if(my_sock == -1)
        printf("socket error \n");
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));

    if(connect(my_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
        printf("connect error\n");
    write(my_sock, req, sizeof(req)); // 서버로 요청
    read(my_sock,message,sizeof(message));
    printf("%s", message); // 한번 요청하고 종료
    //str_len = read(my_sock,message,sizeof(message));
    //if(str_len==-1)
    //    printf("read error\n");
    //printf("%s \n", message);
    close(my_sock);
    return 0;
}