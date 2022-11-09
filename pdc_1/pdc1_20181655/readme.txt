client program
- multi thread 구현 
- program 시작 시에 몇 개의 thread를 생성할 것인지 인자로 받음
- 요청간의 interval은 random하게 구현 (0~3초 이내)
- 커맨드라인으로 파일이름을 받지는 않고, 내부적으로 랜덤하게 GET 요청.
- 요청 경로는 /var/tmp/cse20181655/
- a.html, b.html, c.html, d.html 중 랜덤으로 GET 요청
- d.html의 경우 존재하지 않는 파일이므로 404를 받아야 함.
- 실행방법 (./client <ip_addr> <port> <thread_num>) : ./client 127.0.0.1 7777 1
- 모든 요청 종료 후 몇 bytes를 전달받았는지 출력 후 terminate

server program
- multi thread 구현
- HTTP GET request만 받도록 구현. 다른 요청은 예외처리
- client로 부터 GET 파일 요청을 받아 <body> </body> 태그 안의 내용을 반환
- 없는 파일을 요청할경우 404 Not Found를 반환
- 실행할 포트 넘버를 인자로 받아 server program 실행
- /var/tmp/cse20181655 아래에 있는 html 파일들에 접근하여 내용을 반환
- 실행방법 (./server <port>) : ./server 7777

- server program을 먼저 실행한 후에 client program을 실행
- 현재 client program을 수정하다가 넘겨주는 thread_num 인자가 1일 때는 (사실상 single thread)
  동작이 문제없이 되지만, thread_num 값이 증가하면 에러가 발생합니다. 현 버전을 수정하다가 
  이전 버전 백업을 해두지 않아 일단 이대로 제출합니다. ./client 127.0.0.1 7777 1 이렇게 실행하면
  문제없이 잘 실행됩니다.


