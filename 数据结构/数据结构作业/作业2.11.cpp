//2.11
#include<bits/stdc++.h>
using namespace std;

int va[101],n,x,pos;

void insert(int val){
	int idx=0;
	for(;idx<n;idx++) if(va[idx]>=val) break;
	for(int i=n;i>idx;i--) va[i]=va[i-1];
	va[idx]=val;
}

signed main(){
	cin>>n;//˳���Ԫ�ظ���
	for(int i=0;i<n;i++) cin>>va[i]; //����˳����е�Ԫ��
	sort(va,va+n); //��֤��������
	cin>>x;
	insert(x); //��x���ʵ���λ�� 
	for(int i=0;i<=n;i++) cout<<va[i]; //���˳��� 
	return 0;
} 


