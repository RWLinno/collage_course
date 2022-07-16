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
	for(int i=0;i<n;i++) cin>>a[i]; //给出n个元素的顺序表
	sort(a,a+n); //保证数据递增有序
	insert(x); //将x插入到适当的位置 
	for(int i=0;i<=n;i++) cout<<a[i]<<" ";//输出结果 
	return 0;
}


