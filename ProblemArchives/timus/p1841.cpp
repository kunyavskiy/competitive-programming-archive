#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


ld start = clock();

const int MAXN = 310000;

vector<int> g[MAXN];
vector<ll> l[MAXN];

int x[MAXN];
set<pair<int,pair<int,int> > > s;
int n;

const int inf = 1<<30;

vector<pair<int,int> > addnext;
vector<int> order;

ll d[MAXN];

inline int get(map<int,int>& a,vector<pair<int,int> >& v,int x){
	map<int,int>::iterator iter = a.find(x);
	if (iter != a.end())
		return iter->second;
	d[n] = 1LL<<62LL;
	a[x] = n++;
	v.pb(mp(x,n-1));
	return n-1;
}



int read(int start,int sx,int ex){
	vector<pair<int,int> > xs;
	int end = n++;
	xs.pb(mp(sx,start));
	xs.pb(mp(ex,end));
	vector<pair<int,pair<int,int> > > got(s.lower_bound(mp(min(sx,ex),mp(-inf,-inf))),
										  s.upper_bound(mp(max(sx,ex),mp( inf, inf))));

	map<int,int> num;
	num[sx] = start;
	num[ex] = end;
	d[end] = 1LL<<62LL;
	
	for (int i = 0;i < (int)got.size(); i++){		
		int next = get(num,xs,got[i].first);              
		int from = got[i].second.first;
		d[next] = min(d[next],d[from]+got[i].second.second);
		s.erase(got[i]);
	}

	int v,m;
	scanf("%d %d",&v,&m);

	for (int i = 0; i < (int)addnext.size(); i++){
		int a = addnext[i].first;
		int b = addnext[i].second;
		int next = get(num,xs,a);
		s.insert(mp(a,mp(next,b)));		
	}

	addnext.clear();

	for (int i = 0; i < m; i++){
		int a,b;
		scanf("%d %d",&a,&b);
		if (a != ex){
			int next = get(num,xs,a);
			s.insert(mp(a,mp(next,b)));		
		}
		else 
			addnext.pb(mp(a,b));		
	}	

	sort(xs.begin(),xs.end());

	if (ex < sx)
		reverse(xs.begin(),xs.end());

	for (int i = 0; i+1 < (int)xs.size(); i++)
		d[xs[i+1].second] = min(d[xs[i+1].second],d[xs[i].second] + abs(xs[i+1].first - xs[i].first)*1LL*v);
		                                                             
	return end;
}





int main(){

  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int m;
  scanf("%d",&m);
  for (int i = 0; i <= m; i++)
  	scanf("%d",&x[i]);

  n = 1;
  int last = 0;

  for (int i = 0; i < m; i++)
  	last = read(last,x[i],x[i+1]);
  cout << d[last] << endl;                          
  return 0;
}