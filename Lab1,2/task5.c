#include <stdio.h>
#define __NAME__ "task5.c"
int main()
{
	int num;
	char line[100];
	FILE *fptr;
	fptr = fopen(__NAME__, "r");
	if (fptr == NULL)
	{
	printf("Error opening file");
	}
	else
	{
		while(fgets(line,100,fptr))
		{
			printf("%s", line);
		}
		fclose(fptr);
		return 0;
	}
}