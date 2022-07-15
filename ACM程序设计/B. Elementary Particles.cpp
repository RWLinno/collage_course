//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int t,n,ans;

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	cin>>t;
	while(t--){
		cin>>n;
		ans=-1;
		vector<pair<int,int> >v;
		for(int i=0;i<n;i++){
			int num;
			cin>>num;
			v.push_back(make_pair(num,i));
		}
		sort(v.begin(),v.end());
		for(int i=0;i<n-1;i++){
			if(v[i].first==v[i+1].first){
				ans=max(ans,n-v[i+1].second+v[i].second);
			}
		}
		cout<<ans<<"\n";
	} 
	return 0;
}
