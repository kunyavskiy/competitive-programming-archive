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

#define TASKNAME "A"

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


string ans[6];


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif


    ans[0] = "+------------------------+";
    ans[1] = "|#.#.#.#.#.#.#.#.#.#.#.|D|)";
    ans[2] = "|#.#.#.#.#.#.#.#.#.#.#.|.|";
    ans[3] = "|#.......................|";
    ans[4] = "|#.#.#.#.#.#.#.#.#.#.#.|.|)";
    ans[5] = "+------------------------+";


    int n;
    scanf("%d",&n);
    for (int j = 0; n; j++)
    	for (int i = 0; i < 6 && n; i++)
    		if (ans[i][j] == '#')
    			ans[i][j] = 'O', n--;


    for (int i = 0; i < 6; i++)
    	printf("%s\n", ans[i].c_str());
      
  return 0;
}