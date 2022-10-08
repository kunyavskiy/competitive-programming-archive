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

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "B"

#ifdef LOCAL
static struct __timestamper {
    string what;
    __timestamper(const char* what) : what(what){};
    __timestamper(const string& what) : what(what){};
	~__timestamper(){
        TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;


char buf[510000];

const int MOD = 1000000007;



int solve(string s, int d) {

	int ans = 0;
	if (d == 0) return s == buf;
	for (int i = 0; i < (int)s.size(); i++) {
		string t = s;
		for (int j = i; j < (int)s.size(); j++){
			t[j] = 'B';
			ans += solve(t, d-1);
		}
	}
	for (int i = 0; i < (int)s.size(); i++) {
		string t = s;
		for (int j = i; j < (int)s.size(); j++){
			t[j] = 'O';
			ans += solve(t, d-1);
		}
	}
	return ans;
} 

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    int t;
    scanf("%d",&t);
    for (int it = 0; it < t; it++) {
    	scanf("%s",buf);
    	printf("%d\n", (solve(string(strlen(buf), 'O'), 4) % MOD)); 
  }

      
  return 0;
}