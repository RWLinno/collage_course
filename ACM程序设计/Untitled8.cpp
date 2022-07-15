//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
using namespace std;
const int N=207;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}

string s[N];
int n,LEN;

void Solve(){
	cin>>n;
	for(int i=1;i<=n;++i) cin>>s[i];
	s[n+1]=s[1];LEN=s[1].length();
	reverse(s[n+1].begin(),s[n+1].end());
	int ans=0;
	for(int len=n;len>=1;--len){
		for(int st=0;st<LEN;++st){
			string s1=s[1].substr(st,len),s2=s[n+1].substr(st,len);
			for(int j=2;j<=n;++j){
				if(s[j].find(s1)!=s[j].npos){
					ans=len;break;
				}else if(s[j].find(s2)!=s[j].npos){
					ans=len;break;
				}
			}
			if(ans) break;
		}
		if(ans) break;
	}
	cout<<ans<<"\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
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
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;
	return 0;
}

