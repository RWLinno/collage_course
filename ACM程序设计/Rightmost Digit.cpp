//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
#define lb (x&(-x))
#define ls (p<<1)
#define rs (p<<1|1)
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}

int mp[20],lst[20];

void Solve(){
	int idx=0,n,tmp=1,r,ans=1;
	memset(mp,0,sizeof(mp));
	memset(lst,0,sizeof(lst));
	cin>>n;
	while(1){
		tmp=tmp*n%10; 
		mp[++idx]=tmp;
		if(lst[tmp]){
			r=idx-lst[tmp]; //一个周期的长度 
			r=(n-1)%r+1;    //剩余多少次变化 
			break;
		}else lst[tmp]=idx;
	}
	for(int i=1;i<=r;++i){
		ans=ans*n%10;
	}
	cout<<ans<<"\n";
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
	cin>>T;
//	clock_t start,finish;
//	start=clock();
	while(T--){
		Solve();
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;	return 0;
}

