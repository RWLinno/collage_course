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
	cout<<"By 2020101603 �����\n";
	cout<<"����ڵ�������\n";
	cin>>n;
	Createtr(n);
	cout<<"����ÿ���ڵ�����ҽڵ���"<<endl; 
	for(int i=1;i<=n;i++){
		cin>>u>>v;
		tr[i]->ls=tr[u];
		tr[i]->rs=tr[v];
	}
	cout<<"����ָ�end-��������;change i-����i�ڵ����������;print i -���i�������Ӷ��ӱ��"<<endl;
	while(cin>>str){
		if(str=="end") break;
		if(str=="change"){
			cin>>x;
			swap(tr[x]->ls,tr[x]->rs);
		}
		if(str=="print"){
			cin>>x;
			printf("���Ҷ��ӷֱ�Ϊ��%d %d\n",tr[x]->ls->id,tr[x]->rs->id);
		}
	} 
	cout<<"�������"<<endl;
	return 0;
}

