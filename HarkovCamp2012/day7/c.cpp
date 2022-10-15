#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "c"

const int inf = 1000000000;
const ld eps = 1e-9;

int main(){
  long double w, v;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  cin>>w>>v;
  printf("%.12lf\n", (double)(w+v+sqrt(((ld)2.0)*w*v)));
  return 0;
}

