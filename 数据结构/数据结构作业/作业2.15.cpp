//2.15
#include<bits/stdc++.h>
using namespace std;

struct node{
	int data;
	node *nxt;
};

struct List{
	int length;
	node *head,*tail;
}A,B;//������������A,B 

signed main(){
	node ha=A->head; //�������ߵ�ͷ�ڵ� 
	node hb=B->head; 
	A.length=m; //������ĳ��� 
	B.length=n;
	A->tail->nxt=B->head;//��B����A��β��
	A.length+=B.length();//��������
	node hc=A->head; //�µ�ͷ�ڵ� 
	return 0;
} 


