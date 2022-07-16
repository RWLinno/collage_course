#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#define N 2

using namespace std;

struct X{
	int card,tim;
}s[10005];

X stk1[N],stk2[N<<2];
int top1=-1,top2=-1; //����ջ��ָ�� 


typedef struct QNode{
	X data;
	struct QNode * nxt;
}QNode;

QNode *queue,*front,*rear;

QNode * initQueue(){
	QNode * que=(QNode*)malloc(sizeof(QNode));
	que->nxt=NULL;
	return que;
}

QNode * enqueue(QNode *rear,X data){
	QNode *enElem=(QNode*)malloc(sizeof(QNode));
	enElem->data=data;
	enElem->nxt=NULL;
	rear->nxt=enElem;
	rear=enElem;
	return rear;
}

void push1(X data){ //��ջ 
	if(top1==N){
		printf("ͣ��������\n");
		return;
	}
	top1++;
	stk1[top1].card=data.card;
	stk1[top1].tim=data.tim;
	printf("ͣ���ɹ�\n"); 
} 

void dequeue(QNode *front,QNode *rear){
	QNode *p=NULL;
	if(front->nxt==NULL){
		printf("����Ϊ��\n");
		return;
	}
	p=front->nxt;
	push1(p->data); //��������ͣ������ 
	printf("����%d\n",p->data.card);
	front->nxt=p->nxt;
	if(rear==p){
		rear=front;
	}
	free(p);
}

void push2(X data){ //��ջ 
	if(top2==N){
		printf("��ʱͣ��������\n");
		return;
	}
	top2++;
	stk2[top2].card=data.card;
	stk2[top2].tim=data.tim;
}

void pop1(){ //��ջ 
	if(top1<=0){
		printf("ͣ�������޳�\n");
		return;
	}
	printf("�ɹ�����ջ��Ԫ��:%d\n",stk1[top1].card);
	top1--; 
}

void pop2(){ //��ջ 
	if(top2<=0){
		printf("��ʱͣ�������޳�\n");
		return;
	}
	printf("�ɹ�����ջ��Ԫ��:%d\n",stk2[top2].card);
	top2--; 
}

signed main(){
	char op;
	int idx=1;
	queue=front=rear=initQueue();
	puts("By Linno(2020101603)_2021/9/28\n");
	while(1){
		scanf("(%c,%d,%d)",&op,&s[idx].card,&s[idx].tim);
		getchar(); 
		if(op=='E') break; //��������
		if(op=='A'){
			if(top1==N) rear=enqueue(rear,s[idx]); //�Ŷ� 
			else push1(s[idx]); //ͣ���ɹ�
		}
		if(op=='D'){
			while(top1!=0){ //ֱ�����г����������� 
				push2(stk1[top1]);
				pop1();
			}
			int time=s[idx].tim-stk2[top2].tim;
			double fee=time*5.0;
			printf("����ͣ��ʱ��Ϊ%d,����Ϊ%.2lf\n",time,fee);
			pop2();//��������ĳ���ʻ��
			while(top2!=0){ //����ʱͣ�ŵĳ�������ʻ��ͣ���� 
				push1(stk2[top2]);
				pop2();
			}
			dequeue(front,rear);
		}
		idx++;
	}
	cout<<"�������\n";
	return 0;
}

