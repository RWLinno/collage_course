#include<bits/stdc++.h>
#define ERROR (cout<<"溢出"<<endl),0;
using namespace std;

typedef struct Link{
	int id,sc;
	struct Link *nxt;
}node;

node * Init(){
	int x,y;
	node * p =(node*)malloc(sizeof(node));
	node * tmp=p;
	for(int i=1;i<=3;i++){
		node *a=(node*)malloc(sizeof(node));
		cin>>x>>y;
		a->id=x;
		a->sc=y;
		a->nxt=NULL;
		tmp->nxt=a;
		tmp=tmp->nxt;
	}
	return p;
}

node * Insert(node * p,int idd,int scc,int pos){
	node * tmp=p;
	for(int i=1;i<pos;i++){
		if(tmp==NULL){
			cout<<"无效操作！！\n";
			return p;
		}
		tmp=tmp->nxt;
	}
	node *s=(node*)malloc(sizeof(node));
	s->id=idd;
	s->sc=scc;
	s->nxt=tmp->nxt;
	tmp->nxt=s;
	return p;
}

node * Del(node *p,int pos){
	node *tmp=p;
	for(int i=1;i<pos;i++){
		tmp=tmp->nxt;
	}
	node *del=tmp->nxt;
	tmp->nxt=tmp->nxt->nxt;
	free(del); //释放节点防止内存泄露 
	return p;
}

node *Modify(node *p,int idd,int scc){
	node *tmp=p;
	while(tmp->nxt){
		tmp=tmp->nxt;
		if(tmp->id==idd){
			tmp->sc=scc;
			return p;
		}
	}
	ERROR;
} 

void print(node *p){
	node *tmp=p;
	cout<<"学号           成绩：\n"; 
	while(tmp->nxt){
		tmp=tmp->nxt;
		cout<<(tmp->id)<<"   "<<(tmp->sc)<<"\n";
	}
}

signed main(){
//	freopen("输入数据.cpp","r",stdin);
	cout<<"输入前三名的学号和成绩\n"; 
	node *L=Init();
	cout<<"链表初始化完成\n";  
	print(L);
	string str;
	int idd,scc,pos;
	while(cin>>str){ //不断输入指令 
		if(str=="end") break; //结束程序 
		if(str=="insert"){
			cin>>idd>>scc>>pos;
			L=Insert(L,idd,scc,pos);//在链表pos位置上插入一个学生 
			cout<<"成功插入学号"<<idd<<",分数"<<scc<<endl; 
		}
		if(str=="delete"){
			cin>>pos;
			L=Del(L,pos); //删除操作 
			cout<<"成功删除"<<idd<<"及其成绩"<<endl;	
		}
		if(str=="modify"){
			cin>>idd>>scc;
			L=Modify(L,idd,scc); //修改操作 
			cout<<"成功修改"<<idd<<"的分数变为"<<scc<<endl;
		}
		if(str=="print"){ 
			print(L); //输出当前链表 
			cout<<"Finish 输出"<<endl;
		}
	}
	return 0;
}
