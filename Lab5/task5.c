#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "matrix.h"

void colAdd(int **M1, int ** M2, int **M3, int N){
	for (int j=0; j<N; j++)
		for(int i=0; i<N; i++)
			M3[i][j] = M2[i][j] + M1[i][j];
}

void rowAdd(int **M1, int ** M2, int **M3, int N){
	for (int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			M3[i][j] = M2[i][j] + M1[i][j];
}

int main(){
    int N;
    printf("Enter N: ");
    scanf("%d", &N);

	int **M1;
	M1 = (int **)malloc(N*sizeof(int *));
    for(int i=0;i<N;i++){
        M1[i] = (int *)malloc(N*sizeof(int));
    }
	matGen(M1,N);
	
	int **M2;
	M2 = (int **)malloc(N*sizeof(int *));
    for(int i=0;i<N;i++){
        M2[i] = (int *)malloc(N*sizeof(int));
    }
	matGen(M2,N);

	int **M3;
	M3 = malloc(N*sizeof(int *));
    for(int i=0;i<N;i++){
        M3[i] = (int*)malloc(N*sizeof(int));
    }

	struct timeval t1, t2;
	double time_taken;

	gettimeofday(&t1, NULL);
	
	colAdd(M1,M2,M3,N);
	
	gettimeofday(&t2, NULL);
	
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Column Addition took %f seconds to execute\n", time_taken);

	gettimeofday(&t1, NULL);
	
	rowAdd(M1,M2,M3,N);
	
	gettimeofday(&t2, NULL);
	
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Row Addition took %f seconds to execute\n", time_taken);

	return 0;
}