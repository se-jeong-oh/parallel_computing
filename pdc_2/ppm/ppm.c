#include <stdio.h>
#include <stdlib.h>

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
/*
TODO
1) filp image horizontally (mirroring)
2) gray scale -> taking average of red, green, blue
3) smooth image -> mean of eight neighbors
*/
int main(int argc, char** argv)
{
	PPMImage img;
	
	if(argc != 2){
		fprintf(stderr, "[Usage] : %s <filename>\n", argv[0]);
		exit(1);
	}


	if(fnReadPPM(argv[1], &img) != TRUE){
		exit(1);
	}

	if(fnWritePPM("./result/1.ppm", &img) == TRUE){
		printf("파일 저장완료!\n");
	}

    if(fnFlipPPM("./result/flip1.ppm", &img) == TRUE){
        printf("flip 파일 저장 완료!\n");
    }

	fnClosePPM(&img);

	return 0;
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
            fprintf(fp, "%d ", img->pixels[i][j+2]);
			fprintf(fp, "%d ", img->pixels[i][j+1]);
			fprintf(fp, "%d ", img->pixels[i][j]);
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