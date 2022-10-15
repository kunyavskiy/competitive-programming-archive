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

#define TASKNAME "ARRGAME2"

#ifdef LOCAL
static struct __timestamper {
	~__timestamper(){
        TIMESTAMP(end);
	}
} __TIMESTAMPER;
#endif

typedef long long ll;
typedef long double ld;


void solve(){
	int n;
	scanf("%d",&n);
	vector<int> a(n);
	vector<int> b(n);
	for (int i = 0; i < n; i++)
		scanf("%d",&a[i]);
	for (int i = 0; i < n; i++)
		scanf("%d",&b[i]);
	sort(a.begin(), a.end()); reverse(a.begin(), a.end());
	sort(b.begin(), b.end()), reverse(b.begin(), b.end());
	ll ans = 0;
	while (a.back() == 1) a.pop_back();
	while (b.back() == 1) b.pop_back(), ans += a.size();

	int c12 = upper_bound(a.begin(),a.end(),2, greater<int>()) - lower_bound(a.begin(),a.end(),2, greater<int>());
	int c13 = upper_bound(a.begin(),a.end(),3, greater<int>()) - lower_bound(a.begin(),a.end(),3, greater<int>());
	int c22 = upper_bound(b.begin(),b.end(),2, greater<int>()) - lower_bound(b.begin(),b.end(),2, greater<int>());
	int c23 = upper_bound(b.begin(),b.end(),3, greater<int>()) - lower_bound(b.begin(),b.end(),3, greater<int>());
	int c24 = upper_bound(b.begin(),b.end(),4, greater<int>()) - lower_bound(b.begin(),b.end(),4, greater<int>());

	ans -= c12 * 1LL* c23;
	ans += c13 * 1LL* c22;
	ans -= c12 * 1LL * c24;


	while (a.size() && b.size()){
		if (b.back() <= a.back())
			b.pop_back();
		else
			a.pop_back(), ans += b.size();
	}

	printf("%.9lf\n", (double)ans / n);
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