#include<bits/stdc++.h>
#define ing long long
using namespace std;

int rd(){
	int res=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=f*-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*f;
}

struct Triplet{
	int x,y,z;
	Triplet(int a,int b,int c):x(a),y(b),z(c){}//三元组的构造 
	int mx(){return max(max(x,y),z);}
	int mi(){return min(min(x,y),z);}
};

signed main(){
	cout<<"读入三元组的三个整数"<<endl;
	int a=rd(),b=rd(),c=rd();
	Triplet tri(a,b,c);//三元组的读取 
	cout<<tri.x<<" "<<tri.y<<" "<<tri.z<<"\n"; 
	cout<<"三元组最大值为"<<tri.mx()<<"\n";//求最大值
	cout<<"三元组最小值为"<<tri.mi()<<"\n";//求最小值 
	return 0;
} 
