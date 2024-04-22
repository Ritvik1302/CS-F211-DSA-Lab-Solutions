#include <stdio.h>
#include <sys/time.h>

struct timeval t1, t2;
double time_taken;

int lengthNTR(char *str)
{
	if (*str == '\0')
	{
		return 0;
	}
	else
	{
		return 1 + lengthNTR(str + 1);
	}
}
int lengthTR(char *str, int sum)
{
	if (*str == '\0')
	{
		return sum;
	}
	else
	{
		return lengthTR(str + 1, sum + 1);
	}
}
int lengthI(char *str)
{

	int sum = 0;
	char temp = str[0];
	while(temp!= '\0')
	{
		sum+=1;
	}
	return sum;
}

int main(){

	int n;
	printf("Enter Length\n");
	scanf("%d",&n);

	char s[n];
	for(int i=0;i<n-2;i++){
		s[i] = (char)(i%128);
	}
	s[n-1] = '\0';

	gettimeofday(&t1, NULL);
	lengthNTR(s);
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Non Tail Recursive Length took %f seconds to execute\n", time_taken);

	gettimeofday(&t1, NULL);
	lengthTR(s,0);
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Tail Recursive Length took %f seconds to execute\n", time_taken);

	gettimeofday(&t1, NULL);
	lengthI(s);
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Iterative Length took %f seconds to execute\n", time_taken);

}