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
	Triplet(int a,int b,int c):x(a),y(b),z(c){}//��Ԫ��Ĺ��� 
	int mx(){return max(max(x,y),z);}
	int mi(){return min(min(x,y),z);}
};

signed main(){
	cout<<"������Ԫ�����������"<<endl;
	int a=rd(),b=rd(),c=rd();
	Triplet tri(a,b,c);//��Ԫ��Ķ�ȡ 
	cout<<tri.x<<" "<<tri.y<<" "<<tri.z<<"\n"; 
	cout<<"��Ԫ�����ֵΪ"<<tri.mx()<<"\n";//�����ֵ
	cout<<"��Ԫ����СֵΪ"<<tri.mi()<<"\n";//����Сֵ 
	return 0;
} 
