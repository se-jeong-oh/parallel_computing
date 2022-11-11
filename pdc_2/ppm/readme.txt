- build 방법
    - gcc -o ppm ppm.c
    - 혹은 make 명령어로 실행

- 실행 방법
    - ppm 1.ppm

- 채점 시 특이사항
    - flip, gray, smooth의 결과는 result 폴더에 저장
    - ppm 실행파일과 img 파일은 반드시 같은 경로에 있어야 함.

- 실행 예시
    - 1.ppm 파일을 읽어서 각각 flip, gray scaling, smoothing을 진행한다.
    - 각각의 ppm 파일은 flip1.ppm, gray1.ppm, smooth1.ppm으로 result 디렉토리에 저장된다.

******터미널 실행예시*****************
cse20181655@cspro:~/pdc/pdc_2/ppm$ ./ppm 1.ppm
flip 파일 저장 완료!
gray 파일 저장 완료!
smooth 파일 저장 완료!
*************************************