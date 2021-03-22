#pragma once
#include <stdio.h>
#include <malloc.h>
typedef struct Node {
	DataType data;
	struct Node* prior;//previous
	struct Node* next;
};
typedef struct DoubleLinkedList {
	struct Node* head;
	int size;
};

//初始化
void ListInitiate(DoubleLinkedList* slList) {
	(*slList).size = 0;
	(*slList).head = (Node*)malloc(sizeof(Node));
	(*slList).head->prior = (*slList).head;
	(*slList).head->next = (*slList).head;

}
int ListLength(DoubleLinkedList* slList) {
	return (*slList).size;
}

//向链表末尾添加数据
int ListAdd(DoubleLinkedList* slList, DataType x) {
	Node* cNode = slList->head;
	Node* newNode;

	while (cNode->next != slList->head) {
		cNode = cNode->next;
	}
	newNode = (Node*)malloc(sizeof(Node));
	newNode->data = x;
	newNode->next = slList->head;
	cNode->next = newNode;                  //test
	newNode->prior = cNode;                 //test
	(slList->size)++;
	return 1;
}

int ListGet(DoubleLinkedList* slList, int i, DataType* x) {
	int j;   //
	Node* cNode = slList->head;
	if (i<0 || i >slList->size) {
		printf("get元素位置有误！");
		return 0;
	}
	for (j = 0; j <= i; j++) {
		cNode = cNode->next;
	}

	*x = cNode->data;
	return 1;
}

//在指定位置插入元素
int ListInsert(DoubleLinkedList* slList, int i, DataType x) {
	int j;
	Node* cNode = slList->head;
	Node* newNode;
	if (i < 0 || i > slList->size) {
		printf("插入元素位置有误！");
		return 0;
	}
	for (j = 0; j < i; j++) {
		cNode = cNode->next;
	}
	newNode = (Node*)malloc(sizeof(Node));
	newNode->data = x;
	newNode->next = cNode->next;
	newNode->prior = cNode;
	cNode->next = newNode;
	(slList->size)++;
	return 1;
}

//在指定位置删除元素
int ListDelete(DoubleLinkedList* slList, int i, DataType* x) {
	int j;
	Node* cNode = slList->head;
	Node* deleteNode;
	while (i < 0 || i > slList->size) {
		printf("error!删除元素位置有误！");
		return 0;
	}
	for (j = 0; j < i; j++) {
		cNode = cNode->next;
	}
	deleteNode = cNode->next;
	*x = deleteNode->data;
	cNode->next = cNode->next->next;
	cNode->next->prior = cNode;
	free(deleteNode);
	(slList->size)--;
	return 1;
}

void Destroy(DoubleLinkedList* slList) {
	Node* p, * p1;
	p = (*slList).head;
	(*slList).size = 0;
	while (p != NULL) {
		p1 = p;
		p = p->next;
		free(p1);
	}
	(*slList).head = NULL;
}
