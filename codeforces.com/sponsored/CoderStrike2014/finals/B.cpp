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

const int MAXN = 110000;

int now[MAXN];
bool ans[MAXN];
int evs[MAXN];

int only;

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif
      int n,m;
      while (scanf("%d%d",&n,&m) == 2){
      	 memset(now, 0, sizeof(now[0])*n);
      	 memset(ans, 0, sizeof(ans[0])*n);
         for (int i = 0; i < m; i++){
             char c; int a;
             scanf(" %c %d", &c, &a);
             --a;
             evs[i] = a;
             if (now[a] == 0) 
                 now[a] = (c == '-') ? 1 : -1;          
         }

         int cnt = 0;
         for (int i = 0; i < n; i++)
             cnt += now[i] == 1;

         for (int i = 0; i < n; i++)
             ans[i] = (now[i] != -1 || !cnt);

         only = -2;

         for (int i = 0; i < m; i++){
             if (cnt == 0) {
                 if (only == -2 || only == evs[i])
                     only = evs[i];
                 else
                     only = -1;
             }
             cnt -= now[evs[i]];
             now[evs[i]] *= -1;
             if (now[evs[i]] == -1)
                 ans[evs[i]] &= !cnt;
         }

         for (int i = 0; i < n; i++)
             ans[i] &= (now[i] == 0) || (only == i) || (only == -2);

         int res = 0;
         for (int i = 0; i < n; i++)
             res += ans[i];
         printf("%d\n", res);
         for (int i = 0; i < n; i++)
             if (ans[i])
                 printf("%d ", i+1);
         printf("\n");      
    }
    return 0;
}