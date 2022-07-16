#include<bits/stdc++.h>
#define get(x) (x==ch[fa[x]][1])
using namespace std;
const int maxn=1e6+5;
typedef long long ll;

int fa[maxn],sz[maxn],val[maxn],cnt[maxn];
int ch[maxn][2],rt,tot;
int n,opt,x,tim1,tim2,a[maxn];

void maintain(int x){
	sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+cnt[x];
}

void clear(int x){
	ch[x][0]=ch[x][1]=sz[x]=val[x]=cnt[x]=fa[x]=0;
}

void rotate(int x){
	int y=fa[x],z=fa[y],chk=get(x);
	ch[y][chk]=ch[x][chk^1];
	if(ch[x][chk^1]) fa[ch[x][chk^1]]=y;
	ch[x][chk^1]=y;
	fa[y]=x;
	fa[x]=z;
	if(z) ch[z][y==ch[z][1]]=x;
	maintain(y);
}

void splay(int x){
	for(int f=fa[x];f=fa[x],f;rotate(x))
		if(fa[f]) rotate(get(x)==get(f)?f:x);
	rt=x;
}

void insert(int k){
	if(!rt){
		val[++tot]=k;
		cnt[tot]++;
		rt=tot;
		sz[tot]=1;
		return;
	}
	int cur=rt,f=0;
	while(1){
		if(val[cur]==k){
			cnt[cur]++;
			maintain(cur);
			maintain(f);
			splay(cur);
			break;
		}
		f=cur;
		cur=ch[cur][val[cur]<k];
		if(!cur){
			val[++tot]=k;
			cnt[tot]++;
			fa[tot]=f;
			ch[f][val[f]<k]=tot;
			maintain(tot);
			maintain(f);
			splay(tot);
			break;
		}
	}
}

int get_rank(int k){
	int res=0,cur=rt;
	while(1){
		tim1++;
		if(tim1>10000000){
			return 0;
		}
		if(k<val[cur]){
			cur=ch[cur][0];
		}else{
			res+=sz[ch[cur][0]];
			if(k==val[cur]){
				splay(cur);
				return res+1;
			}
			res+=cnt[cur];
			cur=ch[cur][1];
		}
	}
}

int kth(int k){
	int cur=rt;
	while(1){
	//	tim1++;
		if(ch[cur][0]&&k<=sz[ch[cur][0]])
			cur=ch[cur][0];
		else{
			k-=cnt[cur]+sz[ch[cur][0]];
			if(k<=0){
				splay(cur);
				return val[cur];
			}
			cur=ch[cur][1];
		}
	}
}

int get_pre(){
	int cur=ch[rt][0];
	while(ch[cur][1]) cur=ch[cur][1];
	splay(cur);
	return cur;
}

int get_nxt(){
	int cur=ch[rt][1];
	while(ch[cur][0]) cur=ch[cur][0];
	splay(cur);
	return cur;
}

void del(int k){
	get_rank(k);
	if(cnt[rt]>1){
		cnt[rt]--;
		maintain(rt);
		return;
	}	
	if(!ch[rt][0]&&!ch[rt][1]){
		clear(rt);
		rt=0;
		return;
	}
	if(!ch[rt][0]){
		int cur=rt;
		rt=ch[rt][1];
		fa[rt]=0;
		clear(cur);
		return;
	}
	if(!ch[rt][1]){
		int cur=rt;
		rt=ch[rt][0];
		fa[rt]=0;
		clear(cur);
		return;
	}
	int cur=rt,x=get_pre();
	fa[ch[cur][1]]=x;
	ch[x][1]=ch[cur][1];
	clear(cur);
	maintain(rt);
}

int main(){
	cout<<"顺序与折半查找 By2020101603 阮炜霖\n";
	cout<<"输入整数序列的元素个数\n"; 
	scanf("%d",&n);
	cout<<"输入"<<n<<"个整数\n";
	for(int i=1;i<=n;i++){
		cin>>a[i]; //这是输入的数组
		insert(a[i]); //在Splay平衡树中新建节点 
	}
	cout<<"接下来查找x在序列中的位置，请输入x,x=-1时程序结束\n";
	while(cin>>x){
		tim1=tim2=0;
		if(x==-1) break;
		int rk=get_rank(x);
		if(rk) printf("%d在数中的位置为%d\n",x,rk);
		else printf("不存在这个数\n");
		if(tim1<=10000000) for(int i=1;i<=n;i++){
			tim2++;
			if(a[i]==x) break;
		}
		cout<<"顺序查找的查找次数为:"<<tim2<<",折半查找的查找次数为:"<<tim1<<"\n";
	} 
	cout<<"程序结束\n";
	return 0;
}
