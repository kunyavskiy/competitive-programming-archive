#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <deque>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define timestamp(str) eprintf("[ "str" ] time=%.4lf\n", clock() / double(CLOCKS_PER_SEC))
#else
#define eprintf(...)
#define timestamp(str)
#endif
#define sz(x) (int)((x).size())

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;

#define TASKNAME ""

const long long linf = 1e18;
const int inf = 1e9;
const double eps = 1e-9;
#define INF inf
#define EPS eps

int a[510];
int b[510];
int n;

vector<int> ans;

void change(int x){
	ans.pb(x);
	int id = b[x];
	int t = (id + x) % n;
	swap(a[id],a[t]);
	b[a[id]] = id;
	b[a[t]] = t;
	#ifdef LOCAL
	for (int i = 0; i < n; i++){
		assert(b[a[i]] == i);
//		eprintf("%d ", a[i]);
	}		
//	eprintf("\n");
	#endif
}


int main() {
/*  #ifdef DEBUG
  freopen(TASKNAME ".in", "r", stdin);
  freopen(TASKNAME ".out", "w", stdout);
  #else
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  #endif*/
                 
  scanf("%d",&n);
  for (int i = 0; i < n; i++){
  	scanf("%d",&a[i]);
  	b[a[i]] = i;
  }

  for (int i = 1; i <= n; i++){
//  	cerr <<"!!!!"<<i << endl;
  	int t = i;
  	while (a[t-1] != t) {
  		while (b[t] > t-1)
  			change(t);
  		t = b[t]+1;
  	}
  	while (a[i-1] != i)
  		change(a[n-1]);
  	for (int j = 0; j < i; j++)
  		assert(a[j] == j+1);
  }


  printf("%d\n",ans.size());
  for (int i = 0; i < (int)ans.size(); i++)
  	printf("%d\n",ans[i]);
  	



  timestamp("end");
  return 0;
}
