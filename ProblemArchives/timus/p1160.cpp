//#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "1160"

typedef long long ll;
typedef long double ld;


int p[1100];

int get(int v){
	if (p[v] == v) return v;
	return p[v] = get(p[v]); 
}

bool join(int a,int b){
	a = get(a);
	b = get(b);
	p[a] = b;
	return a != b;
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

    int n,m;
    scanf("%d %d",&n,&m); 
    for (int i = 0; i < n; i++)
    	p[i] = i;

    vector<pair<int, pair<int,int> > > v(m);
    for (int i = 0; i < m; i++) {
    	scanf("%d %d %d",&v[i].second.first, &v[i].second.second, &v[i].first);
    	v[i].second.first--;
    	v[i].second.second--;
    }

    sort(v.begin(), v.end());
    vector<int> ans;

    for (int i = 0; i < m; i++)
    	if (join(v[i].second.first, v[i].second.second))
    		ans.pb(i);

	printf("%d\n%d\n",v[ans.back()].first, ans.size());
	for (int i = 0; i < (int)ans.size(); i++)
		printf("%d %d\n", v[ans[i]].second.first+1, v[ans[i]].second.second+1);
      
    TIMESTAMP(end);
    return 0;
}