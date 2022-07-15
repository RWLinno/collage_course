//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
using namespace std;

int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}

const int xx[]={0,0,1,-1},yy[]={1,-1,0,0};
int n,m,t,sx,sy,dx,dy,flag;
int ex[15][15];
char mp[15][15];

inline int Abs(int x){return x<0?-x:x;}

inline void dfs(int x,int y,int lf){
	if(x==dx&&y==dy&&lf==0) flag=1;
	int dis=lf-Abs(dx-x)-Abs(dy-y);
	if(flag||dis<0||(dis&1)) return;
	for(int d=0;d<4;++d){
		int nx=x+xx[d],ny=y+yy[d];
		if(nx<1||ny<1||nx>n||ny>m||mp[nx][ny]=='X'||ex[nx][ny]) continue;
		ex[nx][ny]=1;
		dfs(nx,ny,lf-1);
		ex[nx][ny]=0;
	}
}

void Solve(){
	memset(ex,0,sizeof(ex));
	flag=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>mp[i][j];
			if(mp[i][j]=='S') sx=i,sy=j;
			if(mp[i][j]=='D') dx=i,dy=j;
		}
	}
	ex[sx][sy]=1;
	dfs(sx,sy,t);
	if(flag) cout<<"YES\n";
	else cout<<"NO\n";
}

signed main(){
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
//	int T=1;
//	cin>>T;
//	clock_t start,finish;
//	start=clock();
	while(cin>>n>>m>>t){
		if(!n&&!m&&!t) break;
		Solve();
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;
	return 0;
}

