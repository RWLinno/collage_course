//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=207;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}
struct node{
	int l,r;
}s[N];

bool cmp(node A,node B){
	return A.r<B.r;
}

int n;

void Solve(){
	for(int i=1;i<=n;++i){
		cin>>s[i].l>>s[i].r;
	}
	sort(s+1,s+1+n,cmp);
	int now=0,ans=0;
	for(int i=1;i<=n;++i){
		if(s[i].l>=now) ++ans,now=s[i].r;
	}
	cout<<ans<<"\n";
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
//	cin>>T;
//	clock_t start,finish;
//	start=clock();
	while(cin>>n){
		if(!n) break;
		Solve();
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;	return 0;
}

