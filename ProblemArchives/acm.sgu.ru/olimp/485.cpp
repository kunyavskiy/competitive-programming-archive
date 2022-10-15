#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back   
using namespace std;

const int MAXN=110000;

typedef int point[2];
typedef int rect[4];

point pts[MAXN];

struct Tcomp{
	int pt;
	int coord;	
	Tcomp(){};
	bool operator()(int a){
		if (pts[a][coord] != pts[pt][coord])
			return pts[a][coord] < pts[pt][coord];
		return pts[a][coord^1] < pts[pt][coord^1];
	}	
	bool operator()(int a,int b){
		if (pts[a][coord] != pts[b][coord])
			return pts[a][coord] < pts[b][coord];
		return pts[a][coord^1] < pts[b][coord^1];
	}
};

bool icmp(int a,int b){
	if (pts[a][0] != pts[b][0])
		return pts[a][0] < pts[b][0];
	return pts[a][1] < pts[b][1];	
}

bool ieql(int a,int b){
	return (pts[a][0] == pts[b][0]) && (pts[a][1] == pts[b][1]);
}


struct _node;
typedef _node* node;

struct _node{
	int lx,rx,ly,ry;
	node l,r;
	Tcomp comp;
	int val;
};

_node mem[4*MAXN];
int memptr;

node Null;

int id[MAXN];

int min(int a,int b){
	return (a<b)?a:b;
}

int max(int a,int b){
	return (a>b)?a:b;
}

node new_node(){
	return &mem[memptr++];
}


node build(int* L,int* R,bool type){
	if (L==R)
		return Null;	
	node res=new_node();
	if (L+1==R){
		res->lx=res->rx=pts[*L][0];
		res->ly=res->ry=pts[*L][1];
		res->comp.coord=type;
		res->comp.pt=*L;
		res->val=-1;
		res->l=res->r=Null;
		return res;
	}
	res->comp.coord=type;
	nth_element(L,L+(R-L)/2,R,res->comp);
	res->comp.pt=*(L+(R-L)/2);
	res->lx=res->rx=pts[*L][0];
	res->ly=res->ry=pts[*L][1];
	int* tmp=L+(R-L)/2;
	res->l=build(L,tmp,type^1);
	res->r=build(tmp,R,type^1);
	res->val=-1;
	res->lx=min(res->l->lx,res->r->lx);
	res->ly=min(res->l->ly,res->r->ly);
	res->rx=max(res->l->rx,res->r->rx);
	res->ry=max(res->l->ry,res->r->ry);
	return res;
}

node root;

rect win[MAXN];
int curid;
int ans[2*MAXN];


int request(int num){
	node v=root;
	int res=-1;
	for (;v!=Null;){
		res=max(res,v->val);
		if (v->comp(num))
			v=v->l;
		else
			v=v->r;
	}
	if (res==-1)
		return -1;
	return ans[res];
}

vector<node> g[MAXN];

//int GENNODEITER;

void gennode(node v,int num){
//	++GENNODEITER;
	int* winnum=win[num];
	if ((winnum[0] <= v->lx  &&  v->rx <= winnum[2]) && (winnum[1] <= v->ly &&  v->ry <=winnum[3])){
		g[num].pb(v);
		return;
	}
	if (winnum[2] < v->lx)
		return;
	if (winnum[0] > v->rx)
		return;
	if (winnum[3] < v->ly)
		return;
	if (winnum[1] > v->ry)
		return;
	gennode(v->l,num);
	gennode(v->r,num);
	return;
}

void update(int num){
	int v=ans[num];
	for (int i=0,sz=g[v].size();i<sz;i++)
		g[v][i]->val=num;
	return;
}


int n,k;


int main()
{                        
	Null=new _node;
	Null->l=Null->r=Null;
	Null->val=-1;
	Null->lx=Null->ly=(1<<30);
	Null->rx=Null->ry=-(1<<30);
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	scanf("%d",&n);
	
	
	for (int i=0;i<n;i++){
		scanf("%d %d %d %d",&win[i][1],&win[i][0],&win[i][3],&win[i][2]);
		if (win[i][0] > win[i][2])
			swap(win[i][0],win[i][2]);
		if (win[i][1] > win[i][3])
			swap(win[i][1],win[i][3]);
	}
	scanf("%d",&k);
	
	
	for (int i=0;i<k;i++){
		id[i]=i;
		scanf("%d %d",&pts[i][1],&pts[i][0]);
	}
	reverse(id,id+k);
	stable_sort(id,id+k,icmp);
	root=build(id,unique(id,id+k,ieql),0);
	curid=-1;
	
	
	for (int i=0;i<n;i++){		
		ans[i]=i;
		gennode(root,i);
		update(i);
	}
	

	for (int i=0;i<k;i++){
		int tmp=request(i);
		printf("%d ",tmp+1);
		if (tmp!=-1){
			curid=i;
			ans[i+n]=tmp;
			update(i+n);
		}
	}
	printf("\n");
    return 0;
}