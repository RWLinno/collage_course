#include<bits/stdc++.h>
#define debug(x) cout<<"x="<<x<<endl
#define int long long
#define N 5
using namespace std;

int push(int *stk,int top,int elem){ //进栈 
	stk[++top]=elem;
	return top;
} 

int pop(int *stk,int top){ //出栈 
	if(top==-1){
		printf("空栈");
		return -1;
	}
	printf("成功弹出栈顶元素:%d\n",stk[top--]);
	return top;
}

int enQueue(int *que,int front,int rear,int data){ //进入队列 
	if((rear+1)%N==front){
		printf("空间已满\n");
		return rear; 
	}
	que[rear%N]=data;
	rear++;
	return rear;
}

int deQueue(int *que,int front,int rear){ //出队 
	if(front==rear%N){
		printf("队列为空\n");
		return front;
	}
	printf("成功删除队首元素%d\n",que[front]);
	front=(front+1)%N;
	return front;
}

signed main(){
	int que[N],stk[N],val; //定义队列和栈类型 
	string str;
	int front=0,rear=0; //设置队头和队尾指针 
	int top=-1; //设置栈顶指针 
	while(cin>>str){
		if(str=="end") break; //结束程序 
		if(str=="enqueue"){ //入队 
			cin>>val;
			rear=enQueue(que,front,rear,val); //加入队列
			cout<<"成功插入"<<val<<"到队尾\n"; 
		}
		if(str=="dequeue"){ //出队 
			front=deQueue(que,front,rear);
		}
		if(str=="push"){
			cin>>val;
			top=push(stk,top,val);
			cout<<"成功插入"<<val<<"到栈顶\n"; 
		}
		if(str=="pop"){
			top=pop(stk,top); 
		}
	}
	return 0;
}

