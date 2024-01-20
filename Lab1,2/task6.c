#include <stdio.h>
#define __NAME1__ "test1.txt"
#define __NAME2__ "test2.txt"
int main()
{
	int num;
	char line[100];
	FILE *fptr1;
	FILE *fptr2;
	fptr1 = fopen(__NAME1__, "r");
	fptr2 = fopen(__NAME2__, "w");
	if (fptr1 == NULL || fptr2 == NULL)
	{
	printf("Error opening file");
	}
	else
	{
		while(fgets(line,100,fptr1))
		{
			fprintf(fptr2, "%s", line);
		}
		fclose(fptr1);
		fclose(fptr2);
		fptr1 = fopen(__NAME1__, "w+");
		fclose(fptr1);
	}
	return 0;
}