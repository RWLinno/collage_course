//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}

string S,T;
int n,m,dp[1005][1005];
signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
//	cin>>T;
//	clock_t start,finish;
//	start=clock();
	while(cin>>S>>T){
		memset(dp,0,sizeof(dp));
		n=S.length(),m=T.length();
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				dp[i][j]=max(dp[i-1][j],dp[i][j-1]); 
				if(S[i-1]==T[j-1]){
					dp[i][j]=max(dp[i][j],dp[i-1][j-1]+1);
				}
			}
		}
		cout<<dp[n][m]<<"\n";
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;	return 0;
}

