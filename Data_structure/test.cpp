#include <stdio.h>
#define Maxsize 100
typedef int DataType;
#include "Seqlist.h"

int main()
{
	Seqlist L;
	int i;
	int x = 99;
	InitiateList(&L);
	//printf("size = %d", ListLength(L));

	for (i = 0; i < 10; i++) {
		InsertList(&L, i, i + 1);
	}

	InsertList(&L, 3, x);
	for (i = 0; i < ListLength(L); i++)
	{
		ListGet(L, i, &x);
		printf("%d ", x);
	}
	printf("---------------------");
	printf("---------------------");
	DeleteList(&L, x);
	for (i = 0; i < ListLength(L); i++)
	{
		ListGet(L, i, &x);
		printf("%d ", x);
	}

	return 0;
}
