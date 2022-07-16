#include <bits/stdc++.h>
#define int long long
#define N 2007
using namespace std;

typedef struct Huffmantr{
	char ch;
	int val;
	int fa,lc,rc;
}Huffmantr;

typedef struct CodeNode
{
int ch;
char bits[N];
}CodeNode;

int n; 

void SelectMin(Huffmantr tr[], int len, int * pos1, int* pos2){
	int min=255;
	int i, j;
	*pos1=0;
	*pos2=0;
	for(i=0; i<len; i++){
		if(tr[i].fa==-1)
		if(min>tr[i].val){
			min=tr[i].val;
			*pos1=i;
		}
	}
	min=255;	
	for(j=0; j<len; j++){
		if(j==*pos1) continue;
		if(tr[j].fa==-1)
		if(min>tr[j].val){
			min=tr[j].val;
			*pos2=j;
		}
	}
}

void CreateHuffmantr(Huffmantr tr[], int n){
	int m=2*n;
	int i;
	for(i=n;i<m-1;i++){
		int pos1, pos2;
		Huffmantr node;
		SelectMin(tr,i,&pos1,&pos2);
		node.val=tr[pos1].val+tr[pos2].val;
		tr[pos1].fa=i;
		tr[pos2].fa=i;
		node.lc=pos1;
		node.rc=pos2;
		node.fa=-1;
		tr[i]=node;
	}
}

void HuffmanEncoding(Huffmantr tr[]){
	int c, p,ans=0;
	int start;
	char cd[N];
	cd[n]='\0';
	cout<<"×Ö·û£¬È¨Öµ¼°¹þ·òÂü±àÂë:";
	for(int i=0;i<n;i++){
		putchar('\n');
		cout<<tr[i].ch<<" "<<tr[i].val;
		putchar(':');
		start=n;
		c=i;
		while((p=tr[c].fa)!=-1){
			if(tr[p].lc==c){
				cd[--start]='0';
			}else{
				cd[--start]='1';
			}
			c=p;
		//	ans+=tr[i].val;
		}
		printf(&cd[start]);
	}
//	cout<<ans<<"\n";
}

signed main(){
	cout<<"¹þ·òÂü±àÂëÆ÷ By 2020101603 Èîì¿ÁØ\n";
	cout<<"ÊäÈë×Ö·ûÊýÁ¿\n";
	Huffmantr tr[N];
	cin>>n;
	for(int i=0;i<n;i++){
		tr[i].lc=-1;
		tr[i].rc=-1;
		tr[i].fa=-1;
	}
	printf("ÊäÈë¹þ·òÂüÊ÷½áµãµÄ×Ö·ûºÍÈ¨Öµ: \n");
	for(int i=0;i<n;i++){
		cin>>tr[i].ch>>tr[i].val; 
	}
	CreateHuffmantr(tr, n);
	for(int j=0;j<2*n-1;j++) printf("tr[%d]=%d \n", j, tr[j].val);
	HuffmanEncoding(tr);
	cout<<"³ÌÐò½áÊø\n";
	return 0;
}
