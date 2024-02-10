#ifndef PERSONMERGEAUX_H
#define PERSONMERGEAUX_H
struct person
{
	int id;
	char *name;
	int age;
	int height;
	int weight;
};
typedef struct person person;
void mergeAux(person A[], int s1, int e1, person B[], int s2, int e2, person C[], int s3, int e3);
#endif