//线性表的操作 
#include<bits/stdc++.h>
using namespace std;

typedef struct node{
	int data;
	struct node *nxt;
}Lnode,*List;

void CreateList(List &L,int n){
	L=(List)malloc(sizeof(node));
	L->nxt=Null;
	for(int i=n;i>0;i--){
		p=(List)malloc(sizeof(node));
		scanf("%d",&p->data);
		p->nxt=L->nxt;
		L->nxt=p;
	}
}

int ListLength(){

}

signed main(){
	return 0;
}
