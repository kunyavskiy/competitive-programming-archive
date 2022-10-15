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

#define TASKNAME "2010"

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


int king(int n, int x, int y){
	int cnt = 0;
    for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++)
        	if ((dx || dy) && 1 <= x+dx && x+dx <= n && 1 <= y+dy && y+dy <= n) 
        		cnt++;
    return cnt;        	
}

int knight(int n, int x, int y){
	int cnt = 0;
    for (int dx = -2; dx <= 2; dx++)
        for (int dy = -2; dy <= 2; dy++)
        	if (abs(dx) + abs(dy) == 3 && 1 <= x+dx && x+dx <= n && 1 <= y+dy && y+dy <= n) 
        		cnt++;
    return cnt;        	
}
int bishop(int n, int x, int y){
	return max(0,min(n, x+y-1) - max(1, x+y - n) + 1) + (n - abs(x - y)) - 2;
}

int rock(int n, int, int){
	return 2*n - 2;
}

int queen(int n, int x, int y){
	return rock(n, x, y) + bishop(n, x, y);
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif
  int n, x, y;
  scanf("%d %d %d",&n,&x,&y);
  printf("King: %d\n", king(n, x, y));
  printf("Knight: %d\n", knight(n, x, y));
  printf("Bishop: %d\n", bishop(n, x, y));
  printf("Rook: %d\n", rock(n, x, y));
  printf("Queen: %d\n", queen(n, x, y));

      
  return 0;
}