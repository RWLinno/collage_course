#include<bits/stdc++.h>
#define M(x,y) make_pair(x,y)
using namespace std;
const int N=105;

int tot=0,head[N],vis[N],pre[N];
int n,m,sta,u,v,w;
long long dir[N];
struct Edge{
	int to,next,dis;
}edge[N<<1];

struct Plots{
	string name;
	string id;
	string info;
}; 

Plots ss[6]={
{"","",""},
{"大门","A01","这是开始的景点。"},
{"实验楼","B02","学生做实验的地方。"},
{"图书馆","C03","学生安静学习的圣地。"},
{"裕华堂","D04","裕华堂4楼的牛排yyds！"},
{"t11宿舍","E05","暨大最大男性交友平台，击剑娱乐场所。"}
}; 

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
	for(int i=1;i<=N;i++) pre[i]=i;
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
	while(j!=sta){
		printf("%d<-",j);
		j=pre[j];
	}
	printf("%d\n",j);
}

int main(){
	printf("校园导游咨询 By 2020101603 阮炜霖\n");
	printf("共5个点，1号点为大门，请输入路径数量\n");
	scanf("%d",&m);
	printf("输入每条边的起点、终点以及权值\n");	
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
	}	
	printf("输入-info n,获得景点n的信息;输入-path n,查找n到所有点的路径以及长度;输入-end 0结束程序\n");
	int i;
	string str;
	while(cin>>str>>i){
		if(str=="-end") break;
		if(str=="-info"){
			if(i<1||i>5){cout<<"输入不合法!\n";}
			else{
				cout<<"景点名:"<<ss[i].name<<"\n";
				cout<<"编号:"<<ss[i].id<<"\n";
				cout<<"简介:"<<ss[i].info<<"\n";
			}
		}
		if(str=="-path"){	
			sta=i;
			dij(i);
			for(int j=1;j<=5;j++){
				printf("%d号点的最短路径为%d,路径为:\n",j,dir[j]);
				print_path(j);
			}
		}
	}
	printf("程序结束\n"); 
	return 0;
}
