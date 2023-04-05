#include <iostream>
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

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

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

int n;
unsigned int t;

map<int, int> d;

#define MOD 1000000007

int dfs(unsigned int x) {
  if (x == t) {
    return 1;
  }
  if (d.find(x) == d.end()) {
    int s = 0;
    if ((x & 3) == 0) {
      s += dfs(x | 1);
    }
    for (int i = 0; i + 2 < n; i++) {
      if (((x >> i) & 7) == 1) {
        s += dfs(x - (1u << i) + (1u << (i + 1)));
        if (s >= MOD) {
          s -= MOD;
        }
      }
    }
    d[x] = s;
    return d[x];
  } else {
    return d[x];
  }
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  d[3]=1;
  d[4]=1;
  d[5]=2;
  d[6]=5;
  d[7]=33;
  d[8]=319;
  d[9]=9666;
  d[10]=484101;
  d[11]=86126251;
  d[12]=921102616;
  d[13]=690667755;
  d[14]=277772735;
  d[15]=168927647;
  d[16]=863966777;
  d[17]=656710249;
  d[18]=529211723;
  d[19]=952552517;
  d[20]=226276192;
  d[21]=197949884;
  d[22]=305182080;
  d[23]=473057943;
  d[24]=9119576;
  d[25]=607610013;
  d[26]=800401364;
  d[27]=125881901;
  d[28]=404394074;
  d[29]=47341655;
  d[30]=126866039;
  d[31]=937077929;
  d[32]=680342212;
  scanf("%d", &n);
  cout << d[n];
//
//  for (n = 3; n <= 32; n++) {
//    t = 0;
//    for (int i = 0; i < n; i++) {
//      t <<= 1;
//      if (i % 2 == 1) {
//        t |= 1;
//      }
//    }
//    d.clear();
//    cout << "d[" << n << "]=" << dfs(0) << ";\n";
//  }
//
  return 0;
}
