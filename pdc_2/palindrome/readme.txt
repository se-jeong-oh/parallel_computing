- **build 방법**
    - gcc -fopenmp pdc_2.1.c 로 컴파일
    - 혹은 make 명령어 실행
    - ./palindrome <num_threads> <input.txt> <output.txt> 형태로 실행
        - ex) ./palindrome 4 words.txt output.txt

- **실행 예시 및 채점 시 필요한 특이사항**
- 총 400개의 palindrome 단어가 검색됨.
    - 대소문자를 구분하지 않고 palindrome을 찾으며, output.txt에는 원래 dictionary에 들어가 있는대로 대소문자를 구분하여 출력
    - ex) remark 와 Kramer 를 Palindrome으로 판별
- 실행 후에는 해당 palindrome을 찾는데 걸리는 시간만 측정하여 출력함.

****************실행 예시*****************************************
cse20181655@cspro:~/pdc/pdc_2$ ./palindrome 4 words.txt output.txt
Elapsed Time: 0.020018
*******************************************************************

- constants
    - LEN : 읽어들인 dictionary를 저장할 배열의 row 크기. words.txt에 저장되어 있는 단어의 수보다 크거나, MAX_LEN보다 작거나 같아야 한다.
    - COL : dictionary에 저장되어 있는 단어의 최대 길이
    - MAX_LEN : 읽어들일 최대 단어의 개수를 지정한다.