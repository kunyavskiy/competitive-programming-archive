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
//#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define lf(x) (((x)<<1)+1)
#define rg(x) (((x)+1)<<1)
#define par(x) (((x)-1)>>1)

using namespace std;

typedef long long int64;
typedef long double ld;

const int maxn=110000;
const int maxlst=1<<17;
const int maxsz=maxlst*2+100;
const int64 inf=1LL<<60LL;

int64 tmin[maxsz][2];
int64 tupd[maxsz][2];
int lst,sz;
int n;

void init(){
	memset(tmin,0,sizeof(tmin));
	memset(tupd,0,sizeof(tupd));
	lst=2;
	for (;lst<n;lst*=2);
	sz=lst*2;	
}

void update(int v,int t){
	if (rg(v)<sz)
		tmin[v][t]=min(tmin[lf(v)][t],tmin[rg(v)][t])+tupd[v][t];
}

void push(int v,int t){
	if (rg(v)<sz){
		tupd[lf(v)][t]+=tupd[v][t];
		tupd[rg(v)][t]+=tupd[v][t];
		tmin[lf(v)][t]+=tupd[v][t];
		tmin[rg(v)][t]+=tupd[v][t];
		update(v,t);
	}
	else
	{
		update(v,t);
		tupd[v][t]=0;
	}
}

void pushall(int v,int t){
	if(v)
		pushall(par(v),t);
	push(v,t);
}

void setval(int pos,int64 val,int t){
	pos=pos+lst-1;
	pushall(pos,t);	
	tmin[pos][t]=val;
	for (;pos;pos=par(pos))
		update(pos,t);
	update(0,t);
}

pair<int,int> findmin(){
	int v=0;
	int t=0;
	if (tmin[0][0]>tmin[0][1])
		t=1;
	for (;rg(v)<sz;){
		push(v,t);
		if (tmin[lf(v)][t]<tmin[rg(v)][t])
			v=lf(v);
		else
			v=rg(v);
	}
	return mp(v-lst+1,t);
}

void upd(int v,int l,int r,int L,int R,int64 delt,int t){
	push(v,t);
	if (r<L || l>R)
		return;
	if (L<=l && r<=R){
		tupd[v][t]+=delt;
		tmin[v][t]+=delt;
		return;
	}
	upd(lf(v),l,(l+r)/2,L,R,delt,t);
	upd(rg(v),(l+r)/2,r,L,R,delt,t);
}

int per[maxn];
int after[maxn];
int before[maxn];
bool used[maxn];
int cost[maxn];



void del(int v){
	used[v]=false;
	upd(0,0,lst-1,0,v-1,-per[maxn],0);
	upd(0,0,lst-1,v+1,n-1,-per[maxn],1);
	setval(v,inf,0);
	setval(v,inf,1);
}




int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	scanf("%d",&n);
  	init();
	for (int i=0;i<n;i++)
		scanf("%d %d %d %d",&cost[i],&per[i],&before[i],&after[i]);
	int64 tmp=0;
	for (int i=0;i<n;i++){
		used[i]=1;
		setval(i,tmp-before[i],1);
		tmp+=per[i];
	}
	tmp=0;
	for (int i=n-1;i>=0;i--){
		cerr<<tmp-after[i]<<endl;
		setval(i,tmp-after[i],0);
		tmp+=per[i];
	}
	for (;;){
		pair<int,int> tmp=findmin();
		cerr<<tmin[tmp.first+lst-1][tmp.second]<<" "<<tmp.first<<" "<<tmp.second<<endl;
		if (tmin[tmp.first+lst-1][tmp.second]>=0)
			break;
		del(tmp.first);
	}
	int cnt=0;
	for (int i=0;i<n;i++)
		cnt+=used[i];
	printf("%d\n",cnt);
	for (int i=0;i<n;i++)
		if (used[i])
			printf("%d ",i+1);
	printf("\n");
    return 0;
}