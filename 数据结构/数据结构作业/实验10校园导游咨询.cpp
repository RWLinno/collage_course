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
{"����","A01","���ǿ�ʼ�ľ��㡣"},
{"ʵ��¥","B02","ѧ����ʵ��ĵط���"},
{"ͼ���","C03","ѧ������ѧϰ��ʥ�ء�"},
{"ԣ����","D04","ԣ����4¥��ţ��yyds��"},
{"t11����","E05","�ߴ�������Խ���ƽ̨���������ֳ�����"}
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
	printf("У԰������ѯ By 2020101603 �����\n");
	printf("��5���㣬1�ŵ�Ϊ���ţ�������·������\n");
	scanf("%d",&m);
	printf("����ÿ���ߵ���㡢�յ��Լ�Ȩֵ\n");	
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
	}	
	printf("����-info n,��þ���n����Ϣ;����-path n,����n�����е��·���Լ�����;����-end 0��������\n");
	int i;
	string str;
	while(cin>>str>>i){
		if(str=="-end") break;
		if(str=="-info"){
			if(i<1||i>5){cout<<"���벻�Ϸ�!\n";}
			else{
				cout<<"������:"<<ss[i].name<<"\n";
				cout<<"���:"<<ss[i].id<<"\n";
				cout<<"���:"<<ss[i].info<<"\n";
			}
		}
		if(str=="-path"){	
			sta=i;
			dij(i);
			for(int j=1;j<=5;j++){
				printf("%d�ŵ�����·��Ϊ%d,·��Ϊ:\n",j,dir[j]);
				print_path(j);
			}
		}
	}
	printf("�������\n"); 
	return 0;
}
