#include<bits/stdc++.h>
#define int long long
#define fr first
#define sc second
#define REP(u) for(int i=head[u],v=e[i].v;i;i=e[i].nxt,v=e[i].v) 
#define REQ(u) for(int i=Head[u],v=E[i].v;i;i=E[i].nxt,v=E[i].v)
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define inf 0x7f7f7f7f
using namespace std;
typedef pair<int,int> p;
const int maxn=2e5+7;
const int N=300300,LG=18,M=600600;

int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

struct edge{
	int nxt,v;
}e[M],E[M];

int n,m,t,u,v,ti,fl,Fl,tp,rt;
int a[N],bo[N],df[N],sz[N],dep[N],tn[N],up[N];
int f[N][LG+2],s[N],Head[N],head[N],ans[N],A[N];
p g[N]; 

void add(int u,int v){e[++fl]=(edge){head[u],v};head[u]=fl;}
void Add(int u,int v){E[++Fl]=(edge){Head[u],v};Head[u]=fl;}

void dfs0(int u){
	df[u]=++ti;
	sz[u]=1;
	REP(u) if(v!=f[u][0]) f[v][0]=u,dep[v]=dep[u]+1,dfs0(v),sz[u]+=sz[v]; 
}//原树上dp

void dfs1(int u){
	if(bo[u]==1) g[u]=p(0,u);
	else g[u]=p(inf,0);
	REQ(u) dfs1(v),g[u]=min(g[u],p(g[v].fr+dep[v]-dep[u],g[v].sc));
} 

void dfs2(int u,int D,int x){
	if(p(D,x)<g[u]) g[u]=p(D,x);
	else D=g[u].fr,x=g[u].sc;
	REQ(u) dfs2(v,D+dep[v]-dep[u],x);
}//以上是第一阶段dp，求出最近点

void dfs3(int u){
	tn[u]=g[u].sc;
	ans[tn[u]]+=sz[u];
	REQ(u){
		int x=v;
		ROF(j,LG,0) if(f[x][j]&&dep[f[x][j]]>dep[u]) x=f[x][j];
		ans[tn[u]]-=sz[up[v]=x];
		dfs3(v);
	}
} 

void dfs4(int u){
	REQ(u){
		int x=up[v],y=v,H;
		if(tn[u]==tn[v]) ans[tn[u]]+=sz[x]-sz[v];
		else{
			H=dep[tn[v]]+dep[u]-g[u].fr;
			H=H&1?H+1>>1:(tn[v]<tn[u]?H>>1:(H>>1)+1);
			ROF(j,LG,0) if(f[y][j]&&dep[f[y][j]]>=H) y=f[y][j];
			ans[tn[v]]+=sz[y]-sz[v];
			ans[tn[u]]+=sz[x]-sz[y];
		}dfs4(v);
	}
}//第二阶段的计算

void dfs5(int u){up[u]=tn[u]=0;REQ(u) dfs5(v);Head[u]=0;} 

int lca(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	ROF(j,LG,0) if(dep[f[u][j]]>=dep[v]&&f[u][j]) u=f[u][j];
	if(u==v) return u;
	ROF(j,LG,0) if(f[u][j]!=f[v][j]&&f[u][j]) u=f[u][j],v=f[v][j];
	return f[u][0];
}

bool cmp(int x,int y){
	return df[x]<df[y];
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	cin>>n;
	FOR(i,1,n-1){
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs0(1);
	FOR(j,1,LG)	FOR(i,1,n) f[i][j]=f[f[i][j-1]][j-1];
	cin>>t;
	while(t--){
		cin>>m;
		FOR(i,1,m) cin>>a[i],A[i]=a[i],bo[a[i]]=1;
		sort(a+1,a+1+m,cmp);
		s[tp=1]=a[1];
		FOR(i,2,m){
			int x=a[i],y=lca(x,s[tp]);
			while(tp>1&&dep[y]<=dep[s[tp-1]]){
				Add(s[tp-1],s[tp]),tp--;
			}
			if(s[tp]!=y) Add(y,s[tp]),s[tp]=y;
			s[++tp]=x;
		}//五行建虚树
		while(tp>1) Add(s[tp-1],s[tp]),tp--;
		rt=s[1];
		dfs1(rt);
		dfs2(rt,g[rt].fr,g[rt].sc);
		dfs3(rt);
		dfs4(rt);
		ans[tn[rt]]+=sz[1]-sz[rt];
		FOR(i,1,m) printf("%d ",ans[A[i]]);
		printf("\n");
		dfs5(rt);
		FOR(i,1,m) bo[a[i]]=ans[a[i]]=0,Fl=0; 
	}
	return 0;
}

