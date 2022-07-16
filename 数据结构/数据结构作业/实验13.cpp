#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define int long long
using namespace std;
const int maxn=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

struct List{
	string name;
	int score,rank;
}stu[maxn],tmp[maxn];

int y,idx=0,id[maxn];
string op,x; 
map<string,int>mp;

bool cmp(List a,List b){
	return a.score>b.score; 
}

void merge_sort(int l,int r){
	if(l==r) return;
	int mid=l+r>>1;
	merge_sort(l,mid);
	merge_sort(mid+1,r);
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r){
		if(stu[i].score>stu[j].score) tmp[k++]=stu[i],i++;
		else tmp[k++]=stu[j],j++;
	}
	while(i<=mid) tmp[k++]=stu[i++];
	while(j<=r) tmp[k++]=stu[j++];
	for(int i=l;i<=r;i++){
		stu[i]=tmp[i];
		mp[stu[i].name]=i;
	}
}

signed main(){
	//ios::sync_with_stdio(0);
	//cin.tie(0);cout.tie(0); 
	cout<<"电话号码的查询 By2020101603 阮炜霖\n";
	cout<<"输入-insert x y:输入学生姓名和分数;-query:输出学生分数和名次;-end:结束程序\n"; 
	while(cin>>op){
		if(op=="-end") break;
		if(op=="-insert"){
			cin>>x>>y;
			if(mp[x]){
				cout<<"成绩已经存在，是否更改?y/n\n";
				char c[10];
				cin>>c;
				if(c[0]=='y') stu[mp[x]].score=y;
			}else{
				stu[++idx]=(List){x,y};
				mp[stu[idx].name]=idx;
			}
		}
		if(op=="-query"){
			merge_sort(1,idx);
			cout<<"姓名   成绩   名次\n"; 
			for(int i=1;i<=idx;i++){
				stu[i].rank=(stu[i].score==stu[i-1].score?stu[i-1].rank:i);
				cout<<stu[i].name<<"  "<<stu[i].score<<"   "<<stu[i].rank<<"\n";
			}
		}
		puts("");
	}
	cout<<"程序结束\n";
	return 0;
}
