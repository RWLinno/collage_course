//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<cstring>
#include<algorithm>
#include<iostream>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}

string S,T;
char stk[3005];
int n,m,top=0,dp[3005][3005];
pair<int,int>pre[3005][3005];

void Solve(){
	cin>>S>>T;
	n=S.length(),m=T.length();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(dp[i-1][j]>dp[i][j-1]) dp[i][j]=dp[i-1][j],pre[i][j]=make_pair(i-1,j);
			else dp[i][j]=dp[i][j-1],pre[i][j]=make_pair(i,j-1);
			if(S[i-1]==T[j-1]){
				if(dp[i-1][j-1]+1>dp[i][j]){
					dp[i][j]=dp[i-1][j-1]+1;
					pre[i][j]=make_pair(i-1,j-1);
				}
			}
		}
	}
	int p1=n,p2=m;
	while(1){
		if(!p1&&!p2) break;
		int x=pre[p1][p2].first,y=pre[p1][p2].second;
		p1=x,p2=y;
		if(S[x]==T[y]) stk[++top]=S[x];
	}
	for(int i=top;i>=1;--i) cout<<stk[i];
	//cout<<dp[n][m]<<"\n";
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

