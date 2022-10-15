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
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
#define filename "pcb"
using namespace std;

typedef pair<int,int> pii;

pii otr[100100];

bool cmpsec(const pii& a,const pii &b){
	return a.second<b.second;
}

struct item{
	int v,pl;
};

item tree[1<<19];
int ls,sz;

void init(int n){
	ls=1;
	for (;ls<n;ls*=2);
	sz=ls*2+1;
	for (int i=0;i<sz;i++)
			tree[i].v=tree[i].pl=0;
}

int find_val(int val){
	int t=1;
	for (;t<ls;){
		val-=tree[t].pl;
		if (tree[2*t].v<=val)
			t=2*t;
		else
			t=2*t+1;
	}
	return t-ls+1;
}

void upd(int v,int l,int r,int L,int R){
	if (r<L || l>R)
		return;
	if (l>=L && r<=R)
		{
			tree[v].pl++;
			tree[v].v++;
			return;
		}
	upd(2*v,l,(l+r)/2,L,R);
	upd(2*v+1,(l+r)/2+1,r,L,R);
	tree[v].v=min(tree[2*v].v,tree[2*v+1].v)+tree[v].pl;
	return;
}

int get(int v){
	v=v+ls-1;
	int ans=0;
	for (;v;v/=2)
		ans+=tree[v].pl;
	return ans;
}


int main()
{
  freopen(filename".in","r",stdin);
  freopen(filename".out","w",stdout);
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d %d",&otr[i].first,&otr[i].second);
	sort(otr,otr+n,cmpsec);
	for (int i=0;i<n;i++)
		otr[i].second=i+1;
	sort(otr,otr+n);
	init(n+1);
	for (int i=0;i<n;i++)
		{
			int v=otr[i].second;
			int tmp=get(v+1);
			int l=find_val(tmp);
			upd(1,1,ls,l,v);
		}
	cout<<get(1)<<endl;  
  return 0;
}