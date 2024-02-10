#ifndef CRIMINALMERGEAUX_H
#define CRIMINALMERGEAUX_H
struct criminal
{
	char *name;
	int age;
	int id;
	float criminality;
};
typedef struct criminal criminal;
void mergeAux(criminal A[], int s1, int e1, criminal B[], int s2, int e2, criminal C[], int s3, int e3);
#endif