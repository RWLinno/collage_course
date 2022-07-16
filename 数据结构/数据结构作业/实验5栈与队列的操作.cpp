#include<bits/stdc++.h>
#define debug(x) cout<<"x="<<x<<endl
#define int long long
#define N 5
using namespace std;

int push(int *stk,int top,int elem){ //��ջ 
	stk[++top]=elem;
	return top;
} 

int pop(int *stk,int top){ //��ջ 
	if(top==-1){
		printf("��ջ");
		return -1;
	}
	printf("�ɹ�����ջ��Ԫ��:%d\n",stk[top--]);
	return top;
}

int enQueue(int *que,int front,int rear,int data){ //������� 
	if((rear+1)%N==front){
		printf("�ռ�����\n");
		return rear; 
	}
	que[rear%N]=data;
	rear++;
	return rear;
}

int deQueue(int *que,int front,int rear){ //���� 
	if(front==rear%N){
		printf("����Ϊ��\n");
		return front;
	}
	printf("�ɹ�ɾ������Ԫ��%d\n",que[front]);
	front=(front+1)%N;
	return front;
}

signed main(){
	int que[N],stk[N],val; //������к�ջ���� 
	string str;
	int front=0,rear=0; //���ö�ͷ�Ͷ�βָ�� 
	int top=-1; //����ջ��ָ�� 
	while(cin>>str){
		if(str=="end") break; //�������� 
		if(str=="enqueue"){ //��� 
			cin>>val;
			rear=enQueue(que,front,rear,val); //�������
			cout<<"�ɹ�����"<<val<<"����β\n"; 
		}
		if(str=="dequeue"){ //���� 
			front=deQueue(que,front,rear);
		}
		if(str=="push"){
			cin>>val;
			top=push(stk,top,val);
			cout<<"�ɹ�����"<<val<<"��ջ��\n"; 
		}
		if(str=="pop"){
			top=pop(stk,top); 
		}
	}
	return 0;
}

