#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x; i<=y; ++i)
using namespace std;
const int N=55;
int n,m,a[N],ans;
bitset <N> mp[N],bit[N];
struct D {
	D() { x=f=0,G(),H(); }
	bitset <N> vis;
	int x,f,g,h;
	bool check() {
		bitset <N> tmp=(vis|mp[x])&bit[x];
		return tmp==vis;
	}
	void getans() {
		rep(i,x+1,n) {
			bitset <N> tmp=(vis|mp[i])&bit[x];
			if(tmp!=vis) f+=a[i],vis[i]=1;
			++x;
		}
		G(),H();
	}
	void G() {
		g=0;
		rep(i,x+1,n) {
			bitset <N> tmp=(vis|mp[i])&bit[x];
			if(tmp!=vis) g+=a[i];
		}
	}
	void H() {
		h=f;
		rep(i,x+1,n) {
			bitset <N> tmp=(vis|mp[i]);
			if(tmp!=vis) h+=a[i],vis[i]=1;
		}
		vis&=bit[x];
	}
} ;
priority_queue <D> q;
bool operator < (const D &x,const D &y) {
	return x.f+x.g>y.f+y.g;
}
int getint() {
	char ch;
	while(!isdigit(ch=getchar()));
	int x=ch-48;
	while(isdigit(ch=getchar())) x=x*10+ch-48;
	return x;
}
int main() {
	n=getint(),m=getint();
	rep(i,1,n) a[i]=getint();
	rep(i,1,n) rep(j,1,i) bit[i][j]=1;
	rep(i,1,m) {
		int u=getint(),v=getint();
		mp[u][v]=mp[v][u]=1;
	}
	D x;
	q.push(x),ans=x.h;
	while(!q.empty()) {
		x=q.top(),q.pop();
		if(x.f+x.g==x.h) break;
		int p=x.x+1;
		++x.x,x.G(),x.H();
		if(x.f+x.g<=ans && x.check()) {
			ans=min(ans,x.h);
			q.push(x);
		}
		x.vis[p]=1,x.f+=a[p],x.G(),x.H();
		if(x.f+x.g<=ans) {
			ans=min(ans,x.h);
			q.push(x);
		}
	}
	printf("%d\n",x.h);
	x.getans();
	rep(i,1,n) putchar('0'+x.vis[i]);
	puts("");
	return 0;
}
