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
int top1=-1,top2=-1; //设置栈顶指针 


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

void push1(X data){ //进栈 
	if(top1==N){
		printf("停车场已满\n");
		return;
	}
	top1++;
	stk1[top1].card=data.card;
	stk1[top1].tim=data.tim;
	printf("停车成功\n"); 
} 

void dequeue(QNode *front,QNode *rear){
	QNode *p=NULL;
	if(front->nxt==NULL){
		printf("队列为空\n");
		return;
	}
	p=front->nxt;
	push1(p->data); //将它放在停车场内 
	printf("弹出%d\n",p->data.card);
	front->nxt=p->nxt;
	if(rear==p){
		rear=front;
	}
	free(p);
}

void push2(X data){ //进栈 
	if(top2==N){
		printf("临时停车场已满\n");
		return;
	}
	top2++;
	stk2[top2].card=data.card;
	stk2[top2].tim=data.tim;
}

void pop1(){ //出栈 
	if(top1<=0){
		printf("停车场内无车\n");
		return;
	}
	printf("成功弹出栈顶元素:%d\n",stk1[top1].card);
	top1--; 
}

void pop2(){ //出栈 
	if(top2<=0){
		printf("临时停车场内无车\n");
		return;
	}
	printf("成功弹出栈顶元素:%d\n",stk2[top2].card);
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
		if(op=='E') break; //结束程序
		if(op=='A'){
			if(top1==N) rear=enqueue(rear,s[idx]); //排队 
			else push1(s[idx]); //停车成功
		}
		if(op=='D'){
			while(top1!=0){ //直到所有车辆都被弹出 
				push2(stk1[top1]);
				pop1();
			}
			int time=s[idx].tim-stk2[top2].tim;
			double fee=time*5.0;
			printf("汽车停留时间为%d,费用为%.2lf\n",time,fee);
			pop2();//将最里面的车辆驶出
			while(top2!=0){ //将临时停放的车辆重新驶入停车场 
				push1(stk2[top2]);
				pop2();
			}
			dequeue(front,rear);
		}
		idx++;
	}
	cout<<"程序结束\n";
	return 0;
}

