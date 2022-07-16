//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 2147483647
//#define int long long
using namespace std;
const int N=1e5+7;

int read(){  //快读优化 
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int n,m,a[N];

namespace Treap{ //Treap平衡树 
	struct balanced{
		int w,sz,num,fix,ch[2];
		//分别为节点的值，子树大小，值的个数，平衡因子和儿子编号 
	};
	int tot;
	balanced tree[N*20];
	int newnode(int w){ //新建节点 
		++tot;
		tree[tot].w=w;
		tree[tot].fix=rand();
		tree[tot].num=1;
		tree[tot].ch[0]=tree[tot].ch[1]=0;
		tree[tot].sz=1;
		return tot;
	}
	void pushup(int p){ //维护节点的子树大小 
		tree[p].sz=tree[tree[p].ch[0]].sz+tree[tree[p].ch[1]].sz+tree[p].num;
	}
	void rotate(int &p,int d){ //旋转操作 
		int y=tree[p].ch[d];
		tree[p].ch[d]=tree[y].ch[d^1];
		tree[y].ch[d^1]=p;
		pushup(p);
		pushup(y);
		p=y;
	}
	void insert(int &p, int w){ //插入节点 
		if (!p) p=newnode(w);
		else if(tree[p].w==w) ++tree[p].num;
		else{
			if(tree[p].w>w){
				insert(tree[p].ch[0],w);
				if(tree[tree[p].ch[0]].fix>tree[p].fix) rotate(p, 0);
			}else{
				insert(tree[p].ch[1],w);
				if(tree[tree[p].ch[1]].fix>tree[p].fix) rotate(p, 1);
			}
		}
		pushup(p);
	}
	void remove(int &p, int w){  //删除节点 
		if(tree[p].w>w) remove(tree[p].ch[0], w);
		else if(tree[p].w<w) remove(tree[p].ch[1], w);
		else{
			if(tree[p].num>1) --tree[p].num;
			else{
				if(!tree[p].ch[0]&&!tree[p].ch[1]) p=0;
				else if(!tree[p].ch[0]){
					rotate(p,1);
					remove(tree[p].ch[0],w);
				}
				else if(!tree[p].ch[1]){
					rotate(p,0);
					remove(tree[p].ch[1],w);
				}else{
					if(tree[tree[p].ch[0]].fix>tree[tree[p].ch[1]].fix){
						rotate(p,0);
						remove(tree[p].ch[1],w);
					}else{
						rotate(p,1);
						remove(tree[p].ch[0],w);
					}
				}
			}
		}
		if (p) pushup(p);
	}
	int queryrank(int p,int k){ //询问平衡树上k值的最高排名 
		if(!p) return 0;
		if(tree[p].w>k) return queryrank(tree[p].ch[0],k);
		else if(tree[p].w==k) return tree[tree[p].ch[0]].sz;
		else return tree[tree[p].ch[0]].sz + tree[p].num + queryrank(tree[p].ch[1], k);
	}
	int querynum(int p,int k){ //询问平衡树上排名为k的值 
		if(tree[tree[p].ch[0]].sz+1==k) return tree[p].w;
		else if(tree[tree[p].ch[0]].sz+1<k)	return querynum(tree[p].ch[1], k - 1 - tree[tree[p].ch[0]].sz);
		else return querynum(tree[p].ch[0],k);
	}
	int querypre(int p,int k){ //询问平衡树上k值的排名 
		if(!p)  return -inf;
		if(tree[p].w>=k) return querypre(tree[p].ch[0],k);
		else return max(tree[p].w,querypre(tree[p].ch[1],k));
	}
	int querysuf(int p,int k){ //询问平衡树上k的前驱 
		if(!p) return inf;
		if(tree[p].w<=k) return querysuf(tree[p].ch[1],k);
		else return min(tree[p].w,querysuf(tree[p].ch[0],k));
	}
};

namespace SEG{
	struct segment{
		int l,r,root;
	};
	segment tree[N*8];
	void build(int p,int l,int r){ 
		tree[p].l=l;
		tree[p].r=r;
		for(int i=l;i<r+1;++i) Treap::insert(tree[p].root,a[i]);//对每个区间建平衡树 
		if(l!=r){
			int mid=(l+r)/2;
			build(p*2,l,mid); //左区间建树 
			build(p*2+1,mid+1,r); //右区间建树 
		}
	}
	void modify(int p, int x, int y){ //线段树单点修改 
		Treap::remove(tree[p].root,a[x]); //删除原数并新增 
		Treap::insert(tree[p].root,y);
		if (tree[p].l==tree[p].r) return;
		int mid=(tree[p].l+tree[p].r)/2;
		if(x>mid) modify(p*2+1,x,y); //修改右区间 
		else modify(p*2,x,y); //修改左区间 
	}
	int queryrank(int p,int l,int r,int k){ 
		if(tree[p].l>r||tree[p].r<l) return 0;
		if(tree[p].l>=l&&tree[p].r<=r) return Treap::queryrank(tree[p].root,k);
		else return queryrank(p*2,l,r,k)+queryrank(p*2+1,l,r,k);
	}
	int querynum(int u,int v,int k){ 
		int l=0,r=1e8;
		while (l<r){
			int mid=(l+r+1)/2;
			if(queryrank(1,u,v,mid)<k) l=mid;
			else r=mid-1;
		}
		return r;
	}
	int querypre(int p,int l,int r,int k){  //对每个区间查询前驱并求最大值 
		if(tree[p].l>r||tree[p].r<l) return -inf;
		if(tree[p].l>=l&&tree[p].r<=r) return Treap::querypre(tree[p].root,k);
		else return max(querypre(p*2,l,r,k),querypre(p*2+1,l,r,k));
	}
	int querysuf(int p, int l, int r, int k){ //对每个区间查询后继并求最小值 
		if(tree[p].l>r||tree[p].r<l) return inf;
		if(tree[p].l>=l&&tree[p].r<=r) return Treap::querysuf(tree[p].root,k);
		else return min(querysuf(p*2,l,r,k), querysuf(p*2+1,l,r,k));
	}
}

signed main(){
	cout<<"线段树套平衡树  By:2020101603 rwl \n";
	cout<<"输入玩家个数和操作个数 \n";
	n=read();m=read();
	cout<<"输入每个玩家的分数 \n";
	for (int i=1;i<n+1;++i) a[i]=read();
	SEG::build(1,1,n); //建线段树 
	for (int i=0;i<m;++i){
		cout<<"请输入操作类型\n";
		int opt=read();
		if(opt==3){
			int x=read(),y=read();
			printf("将玩家%d的分数修改为%d\n",x,y); 
			SEG::modify(1,x,y); //修改某一位置上的值 
			a[x]=y;
		}else{
			int l=read(),r=read(),k=read();
			if(opt==1) printf("%d在区间[%d,%d]内的排名为 %d\n",k,l,r,SEG::queryrank(1,l,r,k)+1); //查询k在区间内的排名 
			else if(opt==2) printf("区间[%d,%d]内的第%d大的数为 %d\n",l,r,k,SEG::querynum(l,r,k)); //查询区间内排名为k的值 
			else if(opt==4) printf("%d在区间[%d,%d]的前驱为%d\n",k,l,r,SEG::querypre(1,l,r,k)); //查询k在区间内的前驱 
			else printf("%d在区间[%d,%d]内的后继为%d\n",k,l,r,SEG::querysuf(1,l,r,k)); //查询k在区间内的后继 
		}
	}
	cout<<"程序结束\n"; 
	return 0;
}

