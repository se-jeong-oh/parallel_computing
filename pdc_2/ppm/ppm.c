#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct {
	char	M, N;
	int		width;
	int		height;
	int		max;
	unsigned char **pixels;
} PPMImage;

int fnWritePPM(char* fileNm, PPMImage* img);
int fnReadPPM(char* fileNm, PPMImage* img);
void fnClosePPM(PPMImage* img);
int fnFlipPPM(char* fileNm, PPMImage* img);
int fnGrayPPM(char* fileNm, PPMImage* img);
int fnSmoothPPM(char* fileNm, PPMImage* img);
/*
TODO
1) filp image horizontally (mirroring) (finish)
2) gray scale -> taking average of red, green, blue (finish)
3) smooth image -> mean of eight neighbors (finish)
*/
int main(int argc, char** argv)
{
	PPMImage img;
	
    char flipNm[1024] = "./result/flip";
    char grayNm[1024] = "./result/gray";
    char smoothNm[1024] = "./result/smooth";

	if(argc != 2){
		fprintf(stderr, "[Usage] : %s <filename>\n", argv[0]);
		exit(1);
	}

    strcat(flipNm, argv[1]);
    strcat(grayNm, argv[1]);
    strcat(smoothNm, argv[1]);

	if(fnReadPPM(argv[1], &img) != TRUE){
		exit(1);
	}

/*
	if(fnWritePPM("./result/1.ppm", &img) == TRUE){
		printf("파일 저장완료!\n");
	}
    */

    if(fnFlipPPM(flipNm, &img) == TRUE){
        printf("flip 파일 저장 완료!\n");
    }

    if(fnGrayPPM(grayNm, &img) == TRUE){
        printf("gray 파일 저장 완료!\n");
    }

    if(fnSmoothPPM(smoothNm, &img) == TRUE){
        printf("smooth 파일 저장 완료!\n");
    }

	fnClosePPM(&img);

	return 0;
}
int fnSmoothPPM(char* fileNm, PPMImage* img)
{
    FILE* fp;
    int r, g, b;
	fp = fopen(fileNm, "w");
	if(fp == NULL){
		fprintf(stderr, "파일 생성에 실패하였습니다.\n");
		return FALSE;
	}

	fprintf(fp, "%c%c\n", 'P', '3');
	fprintf(fp, "%d %d\n" , img->width, img->height);
	fprintf(fp, "%d\n", 255);


	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width * 3; j+=3){
            if(i == 0 || i == img->height -1 || j == 0 || j == img->width*3-3) {
                fprintf(fp, "%d ", img->pixels[i][j]);
                fprintf(fp, "%d ", img->pixels[i][j+1]);
                fprintf(fp, "%d ", img->pixels[i][j+2]);
                continue;
            }
            else {
                r = (img->pixels[i-1][j] + img->pixels[i+1][j] + img->pixels[i][j-3] + 
				img->pixels[i-1][j-3] + img->pixels[i+1][j-3] + img->pixels[i][j+3] + 
				img->pixels[i-1][j+3] + img->pixels[i+1][j+3])/8; 

                g = (img->pixels[i-1][j+1] + img->pixels[i+1][j+1] + img->pixels[i][j-2] + 
				img->pixels[i-1][j-2] + img->pixels[i+1][j-2] + img->pixels[i][j+4] + 
				img->pixels[i-1][j+4] + img->pixels[i+1][j+4])/8; 

                b = (img->pixels[i-1][j+2] + img->pixels[i+1][j+2] + img->pixels[i][j-1] + 
				img->pixels[i-1][j-1] + img->pixels[i+1][j-1] + img->pixels[i][j+5] + 
				img->pixels[i-1][j+5] + img->pixels[i+1][j+5])/8; 
				
                fprintf(fp, "%d ", r);
                fprintf(fp, "%d ", g);
                fprintf(fp, "%d ", b);
            }
		}
		fprintf(fp, "\n");	// 생략가능
	}

	fclose(fp);
	
	return TRUE;

}
int fnGrayPPM(char* fileNm, PPMImage* img)
{
    FILE* fp;
    int mean;
	fp = fopen(fileNm, "w");
	if(fp == NULL){
		fprintf(stderr, "파일 생성에 실패하였습니다.\n");
		return FALSE;
	}

	fprintf(fp, "%c%c\n", 'P', '3');
	fprintf(fp, "%d %d\n" , img->width, img->height);
	fprintf(fp, "%d\n", 255);


	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width * 3; j+=3){
            mean = (img->pixels[i][j] + img->pixels[i][j+1] + img->pixels[i][j+2])/3;
			fprintf(fp, "%d ", mean);
			fprintf(fp, "%d ", mean);
			fprintf(fp, "%d ", mean);

		}

		fprintf(fp, "\n");	// 생략가능
	}

	fclose(fp);
	
	return TRUE;

}
int fnFlipPPM(char* fileNm, PPMImage* img)
{
    FILE* fp;

	fp = fopen(fileNm, "w");
	if(fp == NULL){
		fprintf(stderr, "파일 생성에 실패하였습니다.\n");
		return FALSE;
	}

	fprintf(fp, "%c%c\n", 'P', '3');
	fprintf(fp, "%d %d\n" , img->width, img->height);
	fprintf(fp, "%d\n", 255);

    for(int i=0; i<img->height; i++) {
        for(int j=img->width*3-3; j>=0; j-=3) {
            fprintf(fp, "%d ", img->pixels[i][j]);
			fprintf(fp, "%d ", img->pixels[i][j+1]);
			fprintf(fp, "%d ", img->pixels[i][j+2]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    return TRUE;
}
int fnWritePPM(char* fileNm, PPMImage* img)
{
	FILE* fp;

	fp = fopen(fileNm, "w");
	if(fp == NULL){
		fprintf(stderr, "파일 생성에 실패하였습니다.\n");
		return FALSE;
	}

	fprintf(fp, "%c%c\n", 'P', '3');
	fprintf(fp, "%d %d\n" , img->width, img->height);
	fprintf(fp, "%d\n", 255);


	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width * 3; j+=3){

			fprintf(fp, "%d ", img->pixels[i][j]);
			fprintf(fp, "%d ", img->pixels[i][j+1]);
			fprintf(fp, "%d ", img->pixels[i][j+2]);

		}

		fprintf(fp, "\n");	// 생략가능
	}

	fclose(fp);
	
	return TRUE;
}
int fnReadPPM(char* fileNm, PPMImage* img)
{
	FILE* fp;

	if(fileNm == NULL){
		fprintf(stderr, "fnReadPPM 호출 에러\n");
		return FALSE;
	}
	
	fp = fopen(fileNm, "rb");	// binary mode
	if(fp == NULL){
		fprintf(stderr, "파일을 열 수 없습니다 : %s\n", fileNm);
		return FALSE;
	}

	fscanf(fp, "%c%c\n", &img->M, &img->N);	// 매직넘버 읽기

	if(img->M != 'P' || img->N != '6'){
		fprintf(stderr, "PPM 이미지 포멧이 아닙니다 : %c%c\n", img->M, img->N);
		return FALSE;
	}

	fscanf(fp, "%d %d\n", &img->width, &img->height);	// 가로, 세로 읽기
	fscanf(fp, "%d\n"   , &img->max                );	// 최대명암도 값

	if(img->max != 255){
		fprintf(stderr, "올바른 이미지 포멧이 아닙니다.\n");
		return FALSE;
	}


	// <-- 메모리 할당
	img->pixels = (unsigned char**)calloc(img->height, sizeof(unsigned char*));

	for(int i=0; i<img->height; i++){
	   // 1개의 픽셀을 위해 R, G, B 3byte가 필요
	   img->pixels[i] = (unsigned char*)calloc(img->width * 3, sizeof(unsigned char));
	}
	// -->


	// <-- ppm 파일로부터 픽셀값을 읽어서 할당한 메모리에 load
	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width * 3; j++){
			fread(&img->pixels[i][j], sizeof(unsigned char), 1, fp);
		}
	}
	// -->


	fclose(fp);	// 더 이상 사용하지 않는 파일을 닫아 줌

	return TRUE;
}
void fnClosePPM(PPMImage* img)
{
	for(int i=0; i<img->height; i++){
		free(img->pixels[i]);
	}

	free(img->pixels);
}