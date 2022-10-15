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
#define lf(x) (((x)<<1)+1)
#define rg(x) ((((x)+1)<<1))
#define par(x) (((x)-1)>>1)
using namespace std;


#ifdef ONLINE_JUDGE
	const int maxn=100000;	
	const int maxlst=1<<20;
#else
	const int maxlst=1<<3;
	const int maxn=10;
#endif

	
const int maxsz=maxlst*2;
const int inf=1<<30;


int tree[maxsz];
int ans[maxn];
int val[maxn];
int lst,sz;


void update(int v,int d){
	v+=lst-1;
	tree[v]=d;
	for (;v;v=par(v))
		tree[par(v)]=max(tree[lf(par(v))],tree[rg(par(v))]);
}

int rmq(int v,int l,int r,int L,int R){
	if (r<L || l>R)
		return -inf;
	if (L>R)
		return -inf;
	if (l>=L && r<=R)
		return tree[v];
	return max(rmq(lf(v),l,(l+r)/2,L,R),rmq(rg(v),(l+r)/2+1,r,L,R));
}

void init(){
	lst=maxlst;
	sz=2*lst-1;
	memset(tree,0,sizeof(tree));
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n;
  scanf("%d",&n);
  init();
  for (int i=0;i<n;i++)
  {
  	int a;
  	scanf("%d",&a);
  	int tmp=tree[a+lst-1];
  	tmp=max(tmp,rmq(0,0,lst-1,0,a-2));
  	tmp=max(tmp,rmq(0,0,lst-1,a+2,lst-1)); 	
  	tmp++;
  	ans[i]=tmp;
  	val[i]=a;
  	update(a,tmp);
  }
  
  vector<int> a;
  int size=tree[0];
  for (int i=n-1;i>=0;--i){
  	if (ans[i]==size && (a.size()==0 || abs(val[i]-a.back())!=1))
  	{
  		a.pb(val[i]);
  		size--;
  	}
  }
  
  reverse(a.begin(),a.end());
  
	size=a.size();	
	printf("%d\n",n-size);
	for (int i=0;i<size;i++)
		printf("%d ",a[i]);
  
  
  return 0;
}