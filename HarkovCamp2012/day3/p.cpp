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

#define taskname "p"

const int inf = 1000000000;
const ld eps = 1e-9;

const int maxn = 5001;

int p[maxn];

vector <int> r;

int first[maxn];

int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);



  for (int n = 1; n <= 200; n++)
  {
    int up = (int)(2.0 * n * n + 4.0 * n * (sqrt((double)n))) - 1;

    int last = -1;

    for (int i = 0; i * (i + 1) / 2 <= up; i++)
        last = i;

    int dlast = last;

    assert(last != -1);

    for (int i = 0; i < n; i++)
    {
      p[i] = last * (last + 1) / 2;
      last--;
      assert(last >= 1);
    }

    cerr<<n<<endl;
    r.clear();

    for (int i = 0; i < n; i++)
      printf ("%d ", p[i]);
    puts("");

    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        r.pb(p[i] + p[j]);

    sort(r.begin(), r.end());
    for (int i = 0; i < sz(r) - 1; i++)
    {
      if (r[i] == r[i + 1])
      {
        printf ("FAIL! %d %d\n", n, r[i]);
        exit(0);
      }
    }



  }

  return 0;
}

