//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

struct X{
	string a[4];
	int step;
}s,t;

int ans=1e7;
int xx[]={1,0,-1,0},yy[]={0,1,0,-1};
queue<X>q;
map<string,int>vis;

string get(X x){
	string s="";
	for(int i=0;i<4;i++) s+=x.a[i];
	return s;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	for(int i=0;i<4;i++){
		cin>>s.a[i];
		s.step=1;
	}
	for(int i=0;i<4;i++){
		cin>>t.a[i];	
	}
//	cout<<get(s)<<"\n";
	q.push(s);
	while(!q.empty()){
		X fro=q.front();
		q.pop();
		if(vis[get(fro)]) continue;
		vis[get(fro)]=fro.step;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				if(fro.a[i][j]!=t.a[i][j]){
					for(int d=0;d<4;d++){
						int nx=i+xx[d],ny=j+yy[d];
						if(nx>=0&&nx<4&&ny>=0&&ny<4){
							swap(fro.a[i][j],fro.a[nx][ny]);
							fro.step++;
							q.push(fro);
							swap(fro.a[i][j],fro.a[nx][ny]);
							fro.step--;
						}
					}
				}
			}
		}
	}
	cout<<vis[get(t)]-1<<"\n";
	return 0;
}
