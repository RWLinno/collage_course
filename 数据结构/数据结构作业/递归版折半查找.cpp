#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define int long long
using namespace std;
const int N=2e5+7;
int n,num,idx,a[N];

int binsearch(int a[],int key,int ql,int qr){
	int i=ql,j=qr;
	int mid=(ql+qr)>>1;
	if(i>j) return -1;
	if(key==a[mid]) return mid;
	else if(key>a[mid]) return binsearch(a,key,mid+1,j);
	else return binsearch(a,key,i,mid-1);
	return -1;
}
signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	cout<<"递归版折半查找 By 2020101603 rwl\n";
	cout<<"输入元素个数n(范围1e5)，然后依次输入n个整数\n";
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cout<<"请输入你要查找的数字（找到返回下标，否则返回-1）：\n";
	while(cin>>num){
		idx=binsearch(a,num,1,n);
		printf("num的下标是: %d\n",idx);
	}
	cout<<"程序结束\n";
	return 0;
}

