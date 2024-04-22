#include <stdio.h>
#include <sys/time.h>

struct timeval t1, t2;
double time_taken;

int fibonacciIter(int n){
	if(n==0||n==1)return n;
	int t = n-1;
	int a = 0;
	int b = 1;
	while(t--){
		int c = a+b;
		a = b;
		b = c;
	}
	return b;
}

int fibonacciRec(int n){
	if(n==0||n==1)return n;
	else return (fibonacciRec(n-2) + fibonacciRec(n-1));
}

int main(){
	int n;
	printf("Enter Number\n");
	scanf("%d",&n);

	gettimeofday(&t1, NULL);
	printf("%d\n",fibonacciIter(n));
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("fibonacciIter took %f seconds to execute\n", time_taken);

	gettimeofday(&t1, NULL);
	printf("%d\n",fibonacciRec(n));
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("fibonacciRec took %f seconds to execute\n", time_taken);

}