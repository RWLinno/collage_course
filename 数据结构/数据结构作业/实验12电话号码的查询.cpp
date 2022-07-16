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
	cout<<"电话号码的查询 By2020101603 阮炜霖\n";
	cout<<"输入-insert x y:记录x的电话号码为y;-query x:查找x的电话号码并输出;-end:结束程序\n"; 
	while(cin>>op){
		if(op=="-end") break;
		if(op=="-insert"){
			cin>>x>>y;
			if(fd(x,y)) cout<<"号码已经存在\n";
			else tel[x].push_back(y);
		}
		if(op=="-query"){
			cin>>x;
			if(tel[x].empty()) cout<<"没有该用户的电话\n";
			else for(int j=0;j<tel[x].size();j++){
				cout<<"电话"<<j+1<<":"<<tel[x][j]<<"\n"; 
			}
		}
		puts("");
	}
	cout<<"程序结束\n";
	return 0;
}
