#include <stdio.h>							
#include <stdlib.h>							
#include <malloc.h>							
typedef int DataType;
#include "DoubleLinkList.h"	

int main(void) {
	printf("-------双向链表合理版--------\n");
	int i = 0;
	DataType data;
	DoubleLinkedList slList;
	ListInitiate(&slList);
	/*
	slList.size = 0;
	slList.head = (Node*)malloc(sizeof(Node));
	slList.head->data = 999;
	printf("%d \n ", slList.size);
	printf("%d \n ", slList.head->data);
	*/
	ListAdd(&slList, 1);
	ListAdd(&slList, 2);
	ListAdd(&slList, 3);
	ListAdd(&slList, 4);
	printf("size = %d    \n", slList.size);
	printf("---------------------------------\n");
	for (i = 0; i < ListLength(&slList); i++) {
		ListGet(&slList, i, &data);
		printf("%d = %d    \n", i, data);
	}
	ListInsert(&slList, 4, 5);
	printf("---------------------------------\n");
	for (i = 0; i < ListLength(&slList); i++) {
		ListGet(&slList, i, &data);
		printf("%d = %d    \n", i, data);
	}
	ListInsert(&slList, 2, 88);
	printf("---------------------------------\n");
	for (i = 0; i < ListLength(&slList); i++) {
		ListGet(&slList, i, &data);
		printf("%d = %d    \n", i, data);
	}

	printf("-----删除下标为3的元素----------------------------\n");
	ListDelete(&slList, 3, &data);
	for (i = 0; i < ListLength(&slList); i++) {
		ListGet(&slList, i, &data);
		printf("%d = %d    \n", i, data);
	}
	return 0;
}