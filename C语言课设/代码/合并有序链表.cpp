#include<iostream>
using namespace std;

//���嵥����,�ο��̲�P30
typedef struct LNode
{
	int data;
	struct LNode *next;
}LNode,*LinkList;

void MergeList_L(LinkList &LA,LinkList &LB); //��������

//������ĳ�ʼ�����ο��̲�P32
void InitList_L(LinkList &L)
{
	L=new LNode;
	L->next=NULL;
}

//β�巨�����������ο��̲�P37--P38
void CreateList_L(LinkList L,int n)
{
	int i;
	LinkList p,r;
	r=L;
	//cout<<"����������ñ�ĸ���Ԫ�أ�";
	for(i=0;i<n;i++)
	{
		p=new LNode;
		cin>>p->data;
		p->next=NULL;
		r->next=p;
		r=p;
	}
}

//��������������еĸ���Ԫ�أ����Ÿ�����
void output(LinkList L)
{
	int i=0;
	LNode *p;
	p=L->next;
	while(p)
	{
		if(i)
			cout<<",";
		cout<<p->data;
		p=p->next;
		i=1;
	}
}

//���MergeList_L()�����Ķ��壬�����ײ���ǰ��ġ�����������
/**********************   begin   *********************/
void MergeList_L(LinkList &LA,LinkList &LB){
/*	LinkList pa=LA->next,pb=LB->next,pc=LA;
	
	while(pa&&pb){
	if(pa->data<=pb->data){
		pc->next=pa;
		pc=pa;
		pa=pa->next;
	}
	else{
		pc->next=pb;
		pc=pb;
		pb=pb->next;
	}
}
	pc->next=pa?pa:pb;
	delete LB; 
	 
}*/ 
			//û�п����������ʱ��ɾȥ�����
	LinkList pa = LA->next;
	LinkList pb = LB->next;
	LinkList pc = LA;
	while (pa && pb)
	{
		if (pa->data < pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else if (pb->data < pa->data)
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
		else
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
			LinkList p = pb;
			pb = pb->next;
			delete p;
		}
	}
	if (pa)
	{
		pc->next = pa;
	}
	else
	{
		pc->next = pb;
	}
	delete LB;
}
/**********************    end    *********************/

int main(void)
{
	LinkList La,Lb,Lc;
	int num_a,num_b;

	//cout<<"������ǵݼ�������La�ĸ���num_a��";
	cin>>num_a;
	InitList_L(La);			//La��Ĵ���
	CreateList_L(La,num_a);	//������������La����������

	//cout<<"������ǵݼ�������Lb�ĸ���num_b��";
	cin>>num_b;
	InitList_L(Lb);			//Lb��Ĵ���
	CreateList_L(Lb,num_b);	//������������La����������

	MergeList_L(La,Lb);	//��������La��Lb �ϲ���La��

	//cout<<"�ǵݼ�������La��Lb�ϲ����Ԫ������Ϊ��\n";
	output(La);             //����ϲ���ĵ�����La
	cout<<endl;
	return 0;
}

