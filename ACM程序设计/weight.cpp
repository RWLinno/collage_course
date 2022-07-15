//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=5e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int n,m,sum=0,flag=0,a[N];
int ans[N];

vector<int>vis(N);

void dfs(int pos,int l,int r,int pre,int suf){
	if(flag) return;
	if(!vis[a[pos]-pre]&&!vis[a[pos]-suf]) return;
	if(l==r){  //取完n个了 
		ans[l]=a[2*n]-pre-suf; //这是最后一个数 
		if(ans[l]<1||ans[l]>500) return;
		for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
		flag=1;
		return;
	}
	if(vis[a[pos]-pre]){  //顺着来取 
		ans[l]=a[pos]-pre;
		dfs(pos+1,l+1,r,a[pos],suf);
	}
	if(vis[a[pos]-suf]){ //逆着来取 
		ans[r]=a[pos]-suf;
		dfs(pos+1,l,r-1,pre,a[pos]);
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=2*n;i++)	cin>>a[i];
	sort(a+1,a+1+2*n);
	cin>>m;
	for(int i=1,x;i<=m;i++){
		cin>>x;
		vis[x]=1;
	}
	dfs(1,1,n,0,0); 
	return 0;
}
