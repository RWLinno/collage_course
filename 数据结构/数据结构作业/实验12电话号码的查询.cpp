#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
typedef long long ll;

map<string,vector<string> >tel;

string op,x,y;

bool fd(string a,string b){
	for(int j=0;j<tel[a].size();j++){
		if(tel[a][j]==b) return true;
	}
	return false;
}

int main(){
	cout<<"�绰����Ĳ�ѯ By2020101603 �����\n";
	cout<<"����-insert x y:��¼x�ĵ绰����Ϊy;-query x:����x�ĵ绰���벢���;-end:��������\n"; 
	while(cin>>op){
		if(op=="-end") break;
		if(op=="-insert"){
			cin>>x>>y;
			if(fd(x,y)) cout<<"�����Ѿ�����\n";
			else tel[x].push_back(y);
		}
		if(op=="-query"){
			cin>>x;
			if(tel[x].empty()) cout<<"û�и��û��ĵ绰\n";
			else for(int j=0;j<tel[x].size();j++){
				cout<<"�绰"<<j+1<<":"<<tel[x][j]<<"\n"; 
			}
		}
		puts("");
	}
	cout<<"�������\n";
	return 0;
}
