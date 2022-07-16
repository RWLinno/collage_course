#include<bits/stdc++.h>
#define M(x,y) make_pair(x,y)
using namespace std;
const int N=100005;

int tot=0,head[N],vis[N],pre[N];
int n,m,s,u,v,w;
long long dir[N];
struct Edge{
	int to,next,dis;
}edge[N<<1];

void addedge(int u,int v,int w){
	edge[++tot].next=head[u]; 
	edge[tot].to=v;
	edge[tot].dis=w;
	head[u]=tot;
}

struct node{
	int dis;int pos;
	bool operator <(const node &x)const{
		return x.dis<dis;
	}
};

void dij(int s){
	memset(vis,0,sizeof(vis));
	memset(dir,127/3,sizeof(dir));
	dir[s]=0;
	vis[s]=0;
	priority_queue<node>q;
	q.push(node{0,s});
	while(!q.empty()){
		int x=q.top().pos;
		q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=head[x];i;i=edge[i].next){
			int to=edge[i].to;
			if(dir[to]>dir[x]+edge[i].dis){
				dir[to]=dir[x]+edge[i].dis;
				pre[to]=x;
				if(!vis[to]){
					q.push(node{dir[to],to});
				}
			}
		}
	}
}

void print_path(int ed){
	int j=ed;
	while(j!=s){
		printf("%d<-",j);
		j=pre[j];
	}
	printf("%d\n",j);
}

int main(){
	printf("Dijkstra堆优化求单源最短路径 By 2020101603 阮炜霖\n");
	printf("输入点的数量，有向边数量以及源点v0编号\n");
	scanf("%d%d%d",&n,&m,&s);
	printf("输入每条边的起点、终点以及权值\n");	
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
	}
	dij(s);
	for(int i=1;i<=n;i++){
		printf("%d号点v0的最短路径为%d,路径为:",i,dir[i]);
		print_path(i);
	}
	printf("程序结束\n"); 
	return 0;
}
