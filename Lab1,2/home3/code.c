#include <stdio.h>
#define __NAME__ "LOTR.txt"

int main()
{
	int num;
	char line[1024];
	FILE *fptr;
	fptr = fopen(__NAME__, "r");
	if (fptr == NULL)
	{
	printf("Error opening file");
	}
	else
	{
        int count = 0; 
		while(fgets(line,1024,fptr))
		{
			for(int i=0;i<1024;i++){
                if(line[i]=='h'||line[i]=='H'){
                    if(line[i+1]=='o'||line[i+1]=='O'){
                        if(line[i+2]=='b'||line[i+2]=='B'){
                            if(line[i+3]=='b'||line[i+3]=='B'){
                                if(line[i+4]=='i'||line[i+4]=='I'){
                                    if(line[i+5]=='t'||line[i+5]=='T')count++;
                                }
                            }
                        }
                    }
                }
            }
		}
        printf("%d",count);
		fclose(fptr);
		return 0;
	}
}