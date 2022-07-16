#include<bits/stdc++.h>
#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量 
#define LISTINCREMENT 10 //线性表存储空间的分配增量 
#define ERROR (cout<<"溢出"<<endl),0
using namespace std;

struct List{
	int *elem,*newbase;
	int length;
	int listsize; 
	void initlist(){
		 elem=(int *)malloc(100*sizeof(int));
		 if(!elem) exit(OVERFLOW);
		 length=0;
		 listsize=LIST_INIT_SIZE;
	}
	int insert(int x,int pos){ //在pos后插入x元素 
		if(pos<1||pos>length+1) return ERROR;
		if(length>=listsize){
			newbase=(int *)realloc(elem,(listsize+LISTINCREMENT)*sizeof(int));
			if(!newbase) exit(OVERFLOW);
			elem=newbase;
			listsize+=LISTINCREMENT;
		}
		int q = pos-1;
		for(int p = length-1;p>=q;--p) elem[p+1]=elem[p];
		elem[q]=x;
		++length;
	}
	int del(int pos){ //删除pos位置的元素 
		if((pos<1)||(pos>length)) return ERROR;
		int p=pos;
		int q=length-1;
		for(int q=p;q<=length-1;q++) elem[q]=elem[q+1];
		--length; 
	}
};

int a[]={532,12,64,32,51,37,32,616,735,111};

signed main(){
	List L;
	L.initlist(); //建立链表
	for(int i=1;i<=8;i++) L.insert(a[i],i);
	for(int i=1;i<L.length;i++){
		cout<<L.elem[i]<<" ";
	} 
	cout<<"线性表构建完成"<<endl;
	L.insert(a[9],4); //在第4个位置上插入a[6] 
	for(int i=1;i<L.length;i++){
		cout<<L.elem[i]<<" ";
	} 
	cout<<"插入完成"<<endl;
	L.del(3); //删除第三个位置的数 
		for(int i=1;i<L.length;i++){
		cout<<L.elem[i]<<" ";
	} 
	cout<<"删除完成"<<endl;
	return 0;
} 
