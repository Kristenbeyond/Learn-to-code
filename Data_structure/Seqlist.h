typedef struct {
	DataType list[Maxsize];
	int size;
}Seqlist;

void InitiateList(Seqlist* L) {
	L->size = 0;
}

int ListLength(Seqlist L) {
	return L.size;
}

int InsertList(Seqlist* L, int i, DataType x) {
	if (i < 0 || i > L->size) {
		printf("参数i不合法！");
		return 0;
	} else if (L->size >= Maxsize) {
		printf("顺序表已满，无法插入！");
		return 0;
	} else {
		int j;
		for (j = L->size; j > i; j--) {
			L->list[j] = L->list[j - 1];
		}
		L->list[i] = x;
		L->size ++;
		return 1;
	}
}

int DeleteList(Seqlist* L, DataType x) {
	int i, j;
	for (i = 0; i < L->size; i++)
		if (L->list[i] == x) break;
	if (i == L->size) return 0;
	else {
		for (j = i; j < L->size - 1; j++)
		{
			L->list[j] = L->list[j + 1];
		}
		L->size--;
		return 1;
	}
}

int ListGet(Seqlist L, int i, DataType* x) {
	if (i < 0 || i > L.size - 1) {
		printf("参数不合法！");
		return 0;
	}
	else {
		*x = L.list[i];
		return 1;
	}
}