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
#include <iterator>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))

#define dbg(s) copy(s.begin(),s.end(),ostream_iterator<int>(cerr," "));cerr<<endl

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

typedef multiset<int>::iterator siter;


int g[1100][1100];
int g2[1100][1100];
multiset<int> todel[1100];
multiset<int> toadd[1100];
int n,m;

set<int> tochange;

void delone(int a,int b){
	g2[a][b]--;
	todel[a].erase(todel[a].find(b));	
}

void deledge(int a,int b){
	delone(a,b);
	delone(b,a);
}

void addone(int a,int b){
	if (g2[a][b] < g[a][b]){
		g2[a][b]++;
		toadd[a].erase(toadd[a].find(b));
	}
	else {
		g2[a][b]++;
		todel[a].insert(b);
	}
}

void addedge(int a,int b){
	addone(a,b);
	addone(b,a);
}

void norm(int a){
	if (toadd[a].size() == 0)
		tochange.erase(a);
	else
		tochange.insert(a);
}

void dochange(int a,int b,int c,int d){
	printf("%d %d %d %d %d %d %d %d\n",a+1,b+1,c+1,d+1,a+1,c+1,b+1,d+1);
	deledge(a,b);
	deledge(c,d);
	addedge(a,c);
	addedge(b,d);
	norm(a);
	norm(b);
	norm(c);
	norm(d);
}

int getnot(const multiset<int>& s,int b){
	if (*s.begin() != b)
		return *s.begin();
	if (s.upper_bound(b) != s.end())
		return *s.upper_bound(b);
	return -1;
}


void dosmth(){
	int v = *tochange.begin();
	int u = *toadd[v].begin();
	int t = *todel[v].begin();
	int q = getnot(todel[u],t);
	if (q != -1)
		dochange(v,t,u,q);
	else {
		int s = *toadd[t].begin();
		int r = *todel[s].begin();
		if (r == v)
			dochange(s,v,t,u);
		else
			dochange(s,r,t,v);			
	}
}

int main()
{
//    freopen("gosha.in","r",stdin);
//    freopen("gosha.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i=0;i<m;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		--a,--b;
		g[a][b]++;
		g[b][a]++;
	}
	for (int i=0;i<m;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		--a,--b;
		g2[a][b]++;
		g2[b][a]++;
	}
	
	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			for (int k=g[i][j];k<g2[i][j];++k)
				todel[i].insert(j);
			for (int k=g2[i][j];k<g[i][j];++k)
				toadd[i].insert(j);
		}
	}
		
	for (int i=0;i<n;i++){
		if (todel[i].size() != toadd[i].size()){
			printf("-1\n");
			return 0;
		}		
		if (toadd[i].size() != 0)
			tochange.insert(i);
	}

	for (;!tochange.empty();)
		dosmth();	
		
	return 0;
}