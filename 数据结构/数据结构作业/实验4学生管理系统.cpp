#include<bits/stdc++.h>
#define ERROR (cout<<"���"<<endl),0;
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
			cout<<"��Ч��������\n";
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
	free(del); //�ͷŽڵ��ֹ�ڴ�й¶ 
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
	cout<<"ѧ��           �ɼ���\n"; 
	while(tmp->nxt){
		tmp=tmp->nxt;
		cout<<(tmp->id)<<"   "<<(tmp->sc)<<"\n";
	}
}

signed main(){
//	freopen("��������.cpp","r",stdin);
	cout<<"����ǰ������ѧ�źͳɼ�\n"; 
	node *L=Init();
	cout<<"�����ʼ�����\n";  
	print(L);
	string str;
	int idd,scc,pos;
	while(cin>>str){ //��������ָ�� 
		if(str=="end") break; //�������� 
		if(str=="insert"){
			cin>>idd>>scc>>pos;
			L=Insert(L,idd,scc,pos);//������posλ���ϲ���һ��ѧ�� 
			cout<<"�ɹ�����ѧ��"<<idd<<",����"<<scc<<endl; 
		}
		if(str=="delete"){
			cin>>pos;
			L=Del(L,pos); //ɾ������ 
			cout<<"�ɹ�ɾ��"<<idd<<"����ɼ�"<<endl;	
		}
		if(str=="modify"){
			cin>>idd>>scc;
			L=Modify(L,idd,scc); //�޸Ĳ��� 
			cout<<"�ɹ��޸�"<<idd<<"�ķ�����Ϊ"<<scc<<endl;
		}
		if(str=="print"){ 
			print(L); //�����ǰ���� 
			cout<<"Finish ���"<<endl;
		}
	}
	return 0;
}
