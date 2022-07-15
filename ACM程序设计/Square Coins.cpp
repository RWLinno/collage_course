//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=1007;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}

int a[N],b[N],n;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
//	cin>>T;
//	clock_t start,finish;
//	start=clock();
	for(int i=0;i<=300;++i) a[i]=b[i]=0;
	a[0]=1;
	for(int i=1;i<=17;++i){  //一共有17种金币 
		for(int j=0;j<=300;j+=i*i){ //b的每一项系数 
			for(int k=0;k<=300;++k){ //a的每一项系数 
				b[k+j]+=a[k];
			}
		}	
		for(int k=0;k<=300;++k){
			a[k]=b[k];
			b[k]=0;
		}
	}
	while(cin>>n){
		if(!n) break;
		else cout<<a[n]<<"\n";
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;	return 0;
}

