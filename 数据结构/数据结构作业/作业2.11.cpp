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
	cin>>n;//顺序表元素个数
	for(int i=0;i<n;i++) cin>>va[i]; //输入顺序表中的元素
	sort(va,va+n); //保证递增有序
	cin>>x;
	insert(x); //将x插适当的位置 
	for(int i=0;i<=n;i++) cout<<va[i]; //输出顺序表 
	return 0;
} 


