//2.11
#include<bits/stdc++.h>
using namespace std;


int va[105],x,n;

void insert(int val){
	int idx=0;
	for(;idx<=n;idx++) if(va[idx]>=val) break;
	for(int i=n;i>=idx;i--) va[i]=va[i-1];
	va[idx]=val;
} 

signed main(){
	cin>>n;
	for(int i=0;i<n;i++) cin>>a[i]; //����n��Ԫ�ص�˳���
	sort(a,a+n); //��֤���ݵ�������
	insert(x); //��x���뵽�ʵ���λ�� 
	for(int i=0;i<=n;i++) cout<<a[i]<<" ";//������ 
	return 0;
}


