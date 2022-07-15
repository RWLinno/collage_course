//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

int f[55][5][5],n;

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
//	cin>>T;
//	clock_t start,finish;
//	start=clock();
	f[1][0][0]=f[1][1][1]=f[1][2][2]=1;
	for(int i=2;i<=55;++i){
		f[i][0][0]=f[i-1][0][1]+f[i-1][0][2];
		f[i][0][1]=f[i-1][0][0]+f[i-1][0][2];
		f[i][0][2]=f[i-1][0][0]+f[i-1][0][1];
		f[i][1][0]=f[i-1][1][1]+f[i-1][1][2];
		f[i][1][1]=f[i-1][1][0]+f[i-1][1][2];
		f[i][1][2]=f[i-1][1][0]+f[i-1][1][1];
		f[i][2][0]=f[i-1][2][1]+f[i-1][2][2];
		f[i][2][1]=f[i-1][2][0]+f[i-1][2][2];
		f[i][2][2]=f[i-1][2][0]+f[i-1][2][1];
	}
	while(cin>>n){
		if(n==0) cout<<1<<"\n";
		else if(n==1) cout<<3<<"\n";
		else{
			int ans=f[n][0][1]+f[n][0][2]+f[n][1][0]+f[n][1][2]+f[n][2][0]+f[n][2][1];
			cout<<ans<<"\n";
		}
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;	return 0;
}

