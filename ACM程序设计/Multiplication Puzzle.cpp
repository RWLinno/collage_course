//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<cstring>
#include<algorithm>
#include<iostream>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=207;
const int mod=1e9+7;

int n,a[N],dp[N][N];

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}
void Solve(){
	cin>>n;
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i) dp[i][i+1]=dp[i-1][i]=0,dp[i-1][i+1]=a[i]*a[i-1]*a[i+1];
	for(int len=4;len<=n;++len){ //枚举长度 
		for(int st=1;st+len-1<=n;++st){ //枚举起点 
			int ed=st+len-1;  //得到区间终点 
			for(int k=st;k<=ed;++k){  //中间点可以是st~ed中的数 
				dp[st][ed]=min(dp[st][ed],dp[st][k]+dp[k][ed]+a[k]*a[st]*a[ed]);
				//cout<<st<<" "<<ed<<" "<<dp[st][ed]<<"!!\n";
			}
		}
	}
	cout<<dp[1][n]<<"\n"; 
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
	while(T--){
		Solve();
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;	return 0;
}

