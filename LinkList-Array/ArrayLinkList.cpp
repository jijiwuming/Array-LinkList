#include <stdio.h>
#include <stdlib.h>
#define INIT_SIZE 100
#define ADD_SIZE 10
int INIT_NUM = -1;//���������Ƿ�ռ��
typedef int ElemType;
//��ʼ������ OK
void InitList(ElemType **p) {
	(*p) = (ElemType *)malloc(INIT_SIZE * sizeof(ElemType));
	for (int i = 0;i<INIT_SIZE; i++) {
		(*p)[i] = INIT_NUM;//���������Ƿ�ռ��
	}
	return;
}
//�������� OK
void DestroyList(ElemType **p) {
	free(*p);
	*p = NULL;
	return;
}
//������� OK
void ClearList(ElemType **p) {
	DestroyList(p);
	InitList(p);
	return;
}
//�Ƿ�Ϊ�� OK
int ListEmpty(ElemType* p) {
	return (p[0]==-1);
}
//��ȡ���鳤�� OK
int ListLength(ElemType* p) {
	int ALL=_msize(p) / sizeof(ElemType);
	ElemType i = 0;
	int find = 0;
	for (; i < ALL; i++)
	{
		if (p[i] == -1) {
			find = 1; break;
		}
	}
	if(find=1)return i;
	else return ALL;
}
//��ȡָ��Ԫ�� �ҵ�Ϊ1 δ�ҵ�Ϊ0 OK
int GetElem(ElemType* p,int i, ElemType* e) {
	if (i<1 || i>ListLength(p))return 0;
	else {
		*e = p[i - 1];
		return 1;
	}
}
//�ȽϺ��� OK
int compare(ElemType e1, ElemType e2) {
	if (e1 == e2)return 1;
	else return 0;
}
//��λָ��Ԫ�� OK
int LocateElem(ElemType *p, ElemType e, int (*compare)(ElemType e1, ElemType e2)) {
	int i = 0;
	for (;i<ListLength(p); i++) {
		if ((*compare)(p[i], e)) { return i+1; }
	}
	return 0;
}
//��ȡǰһ��Ԫ�� �ҵ�Ϊ1 δ�ҵ�Ϊ0 OK
int PriorElem(ElemType *p, ElemType cur_e, ElemType *pre_e) {
	int i = 0;
	for (; i<ListLength(p); i++) {
		if (p[i] == cur_e&&i>0) { *pre_e = p[i - 1]; return 1; }
		if (p[i] == cur_e&&i == 0)break;
	}
	return 0;
}
//��ȡ��һ��Ԫ�� �ҵ�Ϊ1 δ�ҵ�Ϊ0 OK
int NextElem(ElemType *p, ElemType cur_e, ElemType *next_e) {
	int i = 0;
	for (; i<ListLength(p); i++) {
		if (p[i] == cur_e&&i<(ListLength(p)-1)) { *next_e = p[i + 1]; return 1; }
		if (p[i] == cur_e&&i==(ListLength(p) - 1))break;
	}
	return 0;
}
//����Ԫ�� ����Ϊ1 δ����Ϊ0 OK
int ListInsert(ElemType **p, int i, ElemType e) {
	int ALL = _msize(*p) / sizeof(ElemType);
	int Length = ListLength(*p);
	if (i<1 || i>(Length+1))return 0;
	if (Length >= ALL) {
		ElemType *p2 = (ElemType *)malloc((ALL + ADD_SIZE) * sizeof(ElemType));
		for (int j = 0;j<ALL;j++) {
			p2[j]=(*p)[j];
		}
			DestroyList(p);
			(*p) = p2;
		for (int i = ALL; i<(ALL + ADD_SIZE); i++) {
			(*p)[i] = INIT_NUM;//���������Ƿ�ռ��
		}
	}
	for (; Length > (i - 1); Length--) {
		(*p)[Length] = (*p)[Length - 1];
	}
	(*p)[i - 1] = e;
	return 1;
}
//ɾ���ڵ� �ɹ�Ϊ1 ʧ��Ϊ0 OK
int ListDelete(ElemType *p, int i, ElemType *e) {
	int Length = ListLength(p);
	if (i<1 || i>Length)return 0;
	int j=(i-1);
	(*e)=p[i - 1];
	for (;j<(Length-1);j++) {
		p[j] = p[j + 1];
	}
	p[Length - 1] = INIT_NUM;
	return 1;
}
//���ʺ��� OK
int visit(ElemType *p) {
	if (sizeof(p) == sizeof(ElemType))return 1;
	else return 0;
	/*return 0;*/
}
//�Ƿ�ɷ��� OK
int ListTraverse(ElemType *p,int(*visit)(ElemType *p)) {
	int i = 0;
	int Length = ListLength(p);
	for (;i<Length; i++) {
		if (!visit(&p[i]))return 0;
	}
	return 1;
}
//�鲢���� OK
void MergeList(ElemType *La, ElemType* Lb, ElemType **Lc) {
	InitList(Lc);
	int i = 1, j = 1, k = 0, La_Len = ListLength(La), Lb_Len = ListLength(Lb);
	
	ElemType *ai = (ElemType *)malloc(sizeof(ElemType));
	ElemType *bj = (ElemType *)malloc(sizeof(ElemType));
	while ((i <= La_Len) && (j <= Lb_Len)) {
		//La��Lb�ǿ�
		GetElem(La, i, ai); GetElem(Lb, j, bj);
		if (*ai <= *bj) { ListInsert(Lc, ++k, *ai); ++i; }
		else { ListInsert(Lc, ++k, *bj); ++j; }
	}
	while (i <= La_Len) {
		GetElem(La, i++, ai); ListInsert(Lc, ++k, *ai);
	}
	while (j <= Lb_Len) {
		GetElem(Lb, j++, bj); ListInsert(Lc, ++k, *bj);
	}
	free(ai);
	free(bj);
	return;
}
//���� OK
void Add(ElemType **p, ElemType e) {
	ListInsert(p, ListLength(*p)+1, e);
	return;
}
//������� Ok
void GetAllList(ElemType *p) {
	for (int i=0;i<ListLength(p);i++)
	{
		printf("%d ", p[i]);
	}
	printf("\n");
	return;
}
int main() {
	ElemType *LA =NULL;
	ElemType *LB =NULL;
	ElemType *LC=NULL;
	//��ʼ������
	InitList(&LA);
	InitList(&LB);

	LA[0] = 3; LA[1] = 5;
	LA[2] = 8;LA[3] = 11;

	LB[0] = 2;LB[1] = 6;LB[2] = 8;LB[3] = 9;
	LB[4] = 11;LB[5] = 15;LB[6] = 20;

	MergeList(LA, LB, &LC);
	printf("�鲢��");
	GetAllList(LC);
	//����
	printf("���Ӻ�");
	Add(&LC, 30);
	GetAllList(LC);
	//ɾ��
	ElemType e = -1;
	ListDelete(LC, ListLength(LC), &e);
	printf("ɾ����");
	GetAllList(LC);
	//����
		//1.ͨ������
		int i = 2;
		GetElem(LC, i, &e);
		printf("1.���ҵڶ�λ��%d\n",e);
		//2.ͨ��ֵ���ҵ�һ��������
		int index=LocateElem(LC, e, compare);
		GetElem(LC, index, &e);
		printf("2.���ҵڶ�λ��%d\n", e);
	//�޸�
		int j = 1;
		ListDelete(LC, j, &e);
		ListInsert(&LC, j, 1024);
		printf("�޸�1λ��");
		GetAllList(LC);
	//LocateElem( p, e, compare);
	system("pause");
}