//阮炜霖 作业3.19 
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define int long long
using namespace std;
const int maxn=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}


signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	string str; 
	cin>>str;
	stack<char>stk;
	for(int i=0;i<str.length();i++){
		if(stk.empty()) stk.push(str[i]);
		else{
			if(str[i]==')'&&stk.top()=='(') stk.pop();
			else if(str[i]==']'&&stk.top()=='[') stk.pop();
			else if(str[i]=='}'&&stk.top()=='{') stk.pop();
			else stk.push(str[i]);
		} 
	}
	if(stk.empty()) cout<<"配对正确\n";
	else cout<<"配对错误\n";
	return 0;
}

