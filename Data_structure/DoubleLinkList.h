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

//��ʼ��
void ListInitiate(DoubleLinkedList* slList) {
	(*slList).size = 0;
	(*slList).head = (Node*)malloc(sizeof(Node));
	(*slList).head->prior = (*slList).head;
	(*slList).head->next = (*slList).head;

}
int ListLength(DoubleLinkedList* slList) {
	return (*slList).size;
}

//������ĩβ�������
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
		printf("getԪ��λ������");
		return 0;
	}
	for (j = 0; j <= i; j++) {
		cNode = cNode->next;
	}

	*x = cNode->data;
	return 1;
}

//��ָ��λ�ò���Ԫ��
int ListInsert(DoubleLinkedList* slList, int i, DataType x) {
	int j;
	Node* cNode = slList->head;
	Node* newNode;
	if (i < 0 || i > slList->size) {
		printf("����Ԫ��λ������");
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

//��ָ��λ��ɾ��Ԫ��
int ListDelete(DoubleLinkedList* slList, int i, DataType* x) {
	int j;
	Node* cNode = slList->head;
	Node* deleteNode;
	while (i < 0 || i > slList->size) {
		printf("error!ɾ��Ԫ��λ������");
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
