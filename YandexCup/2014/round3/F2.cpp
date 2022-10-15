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

#define TASKNAME "F"

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

const int MAXN = 7001;

int g[MAXN];
int used[MAXN];


void encodec(char c) {
    c += 32;
    if (c >= '"') c++;
    if (c >= '?') c++;
    if (c >= '\\') c++;
    assert(c < 127);
    printf("%c", c);
}

void encode(int i){
//	eprintf("%d ", i);
    encodec(i / 90);
    encodec(i % 90);
}

int ptr;

bool win[MAXN][MAXN];

const string data = "";

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    vector<vector<int> > v(MAXN+1);

    int ver = 0;
      for (int L = 2; L < MAXN && L <= 2340; L++) {
          eprintf("%d\n", L);
          for (int i = 0; i < MAXN; i++){
              ++ver;
              for (int j = 0; j <= i - j - L; j++)
                  used[g[j] ^ g[i - j - L]] = ver;
              g[i] = 0;
              for (int& j = g[i]; used[j] == ver; j++);
              if (i >= L && g[i] == 0) encode(i);
          }
//          printf("\n");
          printf("%c", char(127));
          fflush(stdout);
      }
  return 0;
}