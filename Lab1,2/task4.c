#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int n;
	printf("Enter size of the array: ");
	scanf("%d", &n);

	char** arr = calloc(n, sizeof(char *)); // Creating enough space for 'n' strings.
	if (arr == NULL)
	{
	printf("Unable to allocate memory\n");
	return -1;
	}

	printf("Enter the Strings: ");

	for (int i = 0; i < n; i++)
	{
	char * str = calloc(100, sizeof(char));
	scanf("%s", str);
	arr[i]=str;
	}

	printf("\nGiven array of Strings: ");

	for (int i = 0; i < n; i++)
	printf("%s\n", arr[i]);

	printf("\n");

	while(1)
	{
		printf("\n(1) Add a string to the end of the array,\n(2) Add a string to the beginning of the array,\n(3) Delete the element at provided index of the array,\n(4) Display the length of the array,\n(5) Display all the elements of the array in sequence\n(6) Exit Menu\n");
	
		int menu;
		scanf("%d",&menu);
		if(menu==6)break;
		switch(menu){
		case 1:
			arr = realloc(arr, (n + 1) * sizeof(char *));
			n+=1;
			char * str1 = calloc(100, sizeof(char));
			printf("\nEnter New String");
			scanf("%s", str1);
			arr[n-1]=str1;
			break;
		case 2:
			arr = realloc(arr, (n + 1) * sizeof(char *));
			n+=1;
			char * str2 = calloc(100, sizeof(char));
			printf("\nEnter New String");
			scanf("%s", str2);
			for(int i=0;i<n-1;i++){
				arr[i+1]=arr[i];
			}	
			arr[0]=str2;
			break;
		case 3:
			int index;
			printf("\nIndex: ");
			scanf("%d",&index);
			if(index<n)
			{
				for(int i=index;i<n;i++)
				arr[i]=arr[i+1];
				free(arr[n-1]);
				n-=1;
			}
			else printf("\nIndex Out Of Bounds");
			break;
		case 4:
			printf("%lu", sizeof(arr)/sizeof(str2));
			break;
		case 5: 
			for(int i=0;i<n;i++)
				printf("%s\n",arr[i]);
			break;
		}
	}
	return 0;
}