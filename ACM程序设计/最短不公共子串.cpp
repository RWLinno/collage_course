//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

int lena,lenb,lst,sz,root,pre[N],ch[N][26],dp[N<<1],sum[N],mp[N<<1];
char A[N],B[N];
struct Tree{int len,fa,nxt[26];}T[N<<1]; //状态结点 

inline void SAM_extend(int c){  //在SAM中添加字符c 
    int np=++sz;
    T[np].len=T[lst].len+1;
    int x=lst;
    lst=np;
    while(x&&!T[x].nxt[c]) T[x].nxt[c]=np,x=T[x].fa;
    if(!x) T[np].fa=root;
	else{
        int y=T[x].nxt[c];
        if(T[y].len==T[x].len+1) T[np].fa=y;
		else{
            int nq=++sz;
            T[nq]=T[y];
            T[nq].len=T[x].len+1;
            T[nq].fa=T[y].fa;
			T[y].fa=T[np].fa=nq;
            while(x&&T[x].nxt[c]==y) T[x].nxt[c]=nq,x=T[x].fa;
        }
    }
}
void SAM_init(){   
    lst=sz=root=1;
    for(int i=1;i<=lenb;i++) SAM_extend(B[i]-'a');
    for(int i=1;i<=lenb;i++){
        int c=B[i]-'a';
        for(int j=i-1;j>=pre[c];j--) ch[j][c]=i;
        pre[c]=i;
    }
    for(int i=1;i<=sz;i++) sum[T[i].len]++;
    for(int i=1;i<=lenb;i++) sum[i]+=sum[i-1];
    for(int i=1;i<=sz;i++) mp[sum[T[i].len]--]=i;
}

inline int trans(int x,int c,int y){
    if(!y)return T[x].nxt[c];
    else return ch[x][c];
}

void Solve(int f1,int f2){
    memset(dp,inf,sizeof(dp));
    dp[f2^1]=0;
    int ans=inf;
    for(int i=1;i<=lena;i++){
        int c=A[i]-'a';
        for(int z=(f2?lenb:sz);z>=(f2^1);z--){
            int x=f2?z:mp[z];
            int y=trans(x,c,f2);
            if(!y) ans=min(ans,dp[x]+1);
			else{
                dp[y]=min(dp[y],dp[x]+1);
				if(!f1&&x!=(f2^1)) dp[x]=inf;
            }
        }
    }
    if(ans>=inf) puts("-1");
    else printf("%d\n",ans);
}        

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
    scanf("%s%s",A+1,B+1);
	lena=strlen(A+1);lenb=strlen(B+1);
    SAM_init();
    Solve(0,0);
	Solve(0,1);
	Solve(1,0);
	Solve(1,1);
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;	return 0;
}
