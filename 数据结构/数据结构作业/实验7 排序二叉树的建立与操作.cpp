#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define int long long
using namespace std;
const int maxn=2e5+7;
const int mod=1e9+7;

typedef struct _tr tr;
struct _tr{
	int id;
	tr *ls,*rs;
}*tr[maxn];

string str;

void Createtr(int N){
	for(int i=1;i<=N;i++){
		tr[i]=new _tr;
		tr[i]->id=i;
		tr[i]->ls=NULL;
		tr[i]->rs=NULL;
	}
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	int n,u,v,x;
	cout<<"By 2020101603 阮炜霖\n";
	cout<<"输入节点数量：\n";
	cin>>n;
	Createtr(n);
	cout<<"输入每个节点的左右节点编号"<<endl; 
	for(int i=1;i<=n;i++){
		cin>>u>>v;
		tr[i]->ls=tr[u];
		tr[i]->rs=tr[v];
	}
	cout<<"输入指令：end-结束程序;change i-交换i节点的左右子树;print i -输出i的左右子儿子编号"<<endl;
	while(cin>>str){
		if(str=="end") break;
		if(str=="change"){
			cin>>x;
			swap(tr[x]->ls,tr[x]->rs);
		}
		if(str=="print"){
			cin>>x;
			printf("左右儿子分别为：%d %d\n",tr[x]->ls->id,tr[x]->rs->id);
		}
	} 
	cout<<"程序结束"<<endl;
	return 0;
}

