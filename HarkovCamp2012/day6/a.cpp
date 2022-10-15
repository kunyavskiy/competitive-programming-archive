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

#define taskname "a"

const int inf = 1000000000;
const ld eps = 1e-9;

multiset <int> S;
int res;

int main(){
  int n, i;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d", &n);
  for (i=0; i<n; i++)
    S.insert(1);
  while (S.size()>1)
  {
    int a=(*S.begin());
    S.erase(S.begin());
    int b=(*S.begin());
    S.erase(S.begin());
    //cerr<<a<<" "<<b<<endl;
    S.insert(a+b), res+=min(a,b);
  }
  printf("%d\n", res);
  return 0;
}

