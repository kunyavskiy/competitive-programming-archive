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

#define TASKNAME "B"

#ifdef LOCAL
static struct __timestamper {
	~__timestamper(){
		TIMESTAMP(end);
	}
} __TIMESTAMPER;
#endif

typedef long long ll;
typedef long double ld;

int n;
int a[1000100];
int used[1000100];

void solve(){
  	scanf("%d",&n);
  	for (int i = 1; i <= n; i++)
		scanf("%d",&a[i]), used[i] = false;
	vector<int> v;
	int i;
	for (i = 1; !used[i]; i = a[i]){
	    v.pb(i);
	    used[i] = true;
	}
	reverse(v.begin(),v.end());
	while (v.back() != i) v.pop_back();
	printf("%d\n",v.size());
	for (int i = 0; i < (int)v.size(); i++)
		printf("%d%c", v[i]," \n"[i==(int)v.size()-1]);
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

    int t;
    scanf("%d",&t);
    while (t-->0)
    	solve();
  	
      
  return 0;
}