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

#define TASKNAME "1744"

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

int cnt[100][100];


void add(int i, int j, int k){
  	printf("%d %d %d\n", i+1, j+1, k+1);
  	assert(i != k && j != k);
  	assert(cnt[i][j]++ <= 3);
  	assert(cnt[i][k]++ <= 3);
  	assert(cnt[j][k]++ <= 3);
	assert(cnt[j][i]++ <= 3);
	assert(cnt[k][i]++ <= 3);
	assert(cnt[k][j]++ <= 3);
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  int n;
  scanf("%d",&n);
  printf("%d\n", n * (n - 1) / 2 - (n % 2 == 0));
  for (int i = 1; i < n; i++)
  	for (int j = i+1; j < n; j++){
  		int k = (i + j) % n;
  		add(i, j, k);
  	}

  for (int i = 1; i < n; i++)
  	for (int j = i+1; j < n; j++)
  		while (cnt[i][j] < 3)
	  		add(0, i, j);

  int bad = 0;
  for (int i = 0; i < n; i++)
  	for (int j = i+1; j < n; j++)
  		bad += 3-cnt[i][j];

  if (n % 2 == 0) assert(bad == 3);
  else assert(bad == 0);
      
  return 0;
}