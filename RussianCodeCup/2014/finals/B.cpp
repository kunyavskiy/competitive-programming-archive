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

long long mpow(int a, int b) {
	if (!b) return 1;
	if (b & 1) return (mpow(a, b-1) * 1LL * a) % MOD;
	return mpow((a * 1LL * a) % MOD, b / 2);
}

int ans[510000];

long long solve(){
    if (buf[0] == 'O') {
    	for (int j = 0; buf[j]; j++)
    		buf[j] = 'O' + 'B' - buf[j];
    }
    int cnto, cntb;
    cnto = 0;
    cntb = 1;
   	for (int i = 1; buf[i]; i++)
   		if (buf[i] == 'O' && buf[i-1] != 'O')
   			cnto++;
   	for (int i = 1; buf[i]; i++)
   		if (buf[i] == 'B' && buf[i-1] != 'B')
   			cntb++;
   	if (cnto == 0) 
   		return 1;
    int l = strlen(buf);
    if (buf[l-1] == 'B')
    	return ans[cnto-1];
    if (cntb == 1) 
    	return l + 2;
    int cntLB = 0;
   	for (int i = 0; buf[i]; i++)
   		if (buf[i] == 'O') {
   			cntLB = i;
   			break;
   		}
	int cntRO = 0;
   	for (int i = l-1; i >= 0; i--)
   		if (buf[i] == 'B') {
   			cntRO = l - i - 1;
   			break;
   		}
//    if (cntb >= 3) {
//    	return (l - cntLB + 1) * mpow(3, cnto-1) + (l - cntRO + 1) * mpow(3, cnto-1);
//    }
    return (l - cntLB + 1) * ans[cnto-2] + (cntRO + 1) * (ans[cnto-1] - ans[cnto-2] + MOD) +
           (l - cntRO + 1) * ans[cnto-2] + (cntLB + 1) * (ans[cnto-1] - ans[cnto-2] + MOD);
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
    	printf("%d\n", (int)(solve() % MOD)); 
  }

      
  return 0;
}