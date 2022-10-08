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
#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXV=1000100;
const int MAXPRIME=80000;
const int MAXN=110;

bool eused[MAXV];
int cnt;
vector<int> primes;

void erotosfen(){
    eused[0]=eused[1]=false;
    for (int i=2;i<MAXV;i++){
        if (eused[i]) continue;
        primes.pb(i);
        if (i*1LL*i < MAXV){
            for (int j=i;i*j<MAXV;j++)
                eused[i*j]=true;
        }
    }
}



struct _edge{
	int to,p,nod,nok;
	_edge(int to,int p,int nok,int nod):to(to),p(p),nod(nod),nok(nok){
	};
	_edge(){};
};

bool operator<(const _edge& a,const _edge& b){
	return a.p < b.p;
}

vector<_edge> g[MAXN];
typedef vector<_edge>::iterator edge;

int used[MAXN];
int val[MAXN];
int ans[MAXN];
int diter;
int n,m;


bool dfs(int p,int v,int st){
	if (used[v]==diter){
		if (val[v]==st)
			return true;
		return false;
	}
	used[v]=diter;
	val[v]=st;
	edge start=lower_bound(g[v].begin(),g[v].end(),_edge(0,p,0,0));
	edge en=upper_bound(g[v].begin(),g[v].end(),_edge(0,p,0,0));
	for (;start!=en;++start){
		if (st!=start->nod && st!=start->nok)
			return false;
		if (!dfs(p,start->to,start->nod+start->nok-st))
			return false;
	}
	return true;
}

void solve(int p,int v){
	edge tmp=lower_bound(g[v].begin(),g[v].end(),_edge(0,p,0,0));
	if (tmp==g[v].end() || tmp->p != p){
		val[v]=0;		
		return;
	}
	++diter;
	if (dfs(p,v,tmp->nod))
		return;
	++diter;
	if (dfs(p,v,tmp->nok))
		return;
	printf("NO\n");
	exit(0);
}



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	erotosfen();
	scanf("%d %d",&n,&m);
	for (int i=0;i<m;i++){
		int a,b,nok,nod;
		scanf("%d %d %d %d",&a,&b,&nod,&nok);
		--a,--b;
		
		if (nok % nod!=0){	
			printf("NO\n");
			return 0;
		}
		for (int J=0;J<primes.size();J++){
			int j=primes[J];
			int kst=0,dst=0;
			for (;nod%j==0;dst++)
				nod/=j;
			for (;nok%j==0;kst++)
				nok/=j;
			g[a].pb(_edge(b,j,kst,dst));
			g[b].pb(_edge(a,j,kst,dst));
		}		
	}
	
	
	for (int i=0;i<n;i++){
		sort(g[i].begin(),g[i].end());
		ans[i]=1;
	}
	
	for (int i=0;i<primes.size();i++){
		memset(val,-1,sizeof(val));
		for (int j=0;j<n;j++){
			if (val[j]==-1)
				solve(primes[i],j);
		}
		
		for (int j=0;j<n;j++)
			for (int k=0;k<val[j];k++)
				ans[j]*=primes[i];
	}
	
	printf("YES\n");
	for (int i=0;i<n;i++)
		printf("%d ",ans[i]);
	printf("\n");
    return 0;
}