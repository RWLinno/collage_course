//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
//#define inf 0x3f3f3f3f
#define int long long
//#define int __int128
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}

inline int fpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a;
		a=a*a;
		while(res>1000000000) res/=10;
		while(a>1000000000) a/=10;
		b>>=1ll;
	}
	return res;
}

void Solve(){
	double n,m;
	cin>>n;
	m=n*log10(n);
	m-=(int)m;
	cout<<(int)pow(10,m)<<"\n";
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
	T=read();
//	clock_t start,finish;
//	start=clock();
	while(T--){
		Solve();
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;	return 0;
}

