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
}A,B;//定义两个链表A,B 

signed main(){
	node ha=A->head; //定义两者的头节点 
	node hb=B->head; 
	A.length=m; //两链表的长度 
	B.length=n;
	A->tail->nxt=B->head;//将B接在A的尾部
	A.length+=B.length();//长度增加
	node hc=A->head; //新的头节点 
	return 0;
} 


