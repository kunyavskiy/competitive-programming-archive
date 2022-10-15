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
#define y1 y1_nmfdgfh

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

#define taskname "e"

const int inf = 1000000000;
const ld eps = 1e-9;

int x1[20],x2[20],y1[20],y2[20];
int n;

ll s(int mask){
	int lx,rx,ly,ry;
	lx = ly = -inf;
	rx = ry = inf;
	for (int i = 0; i < n; i++)
		if (mask & (1<<i)){
			lx = max(lx,x1[i]);
			ly = max(ly,y1[i]);
			rx = min(rx,x2[i]);
			ry = min(ry,y2[i]);
		}

	return max(rx-lx,0) * 1LL * max(ry-ly, 0);			
}
                                            
int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  scanf("%d",&n);
  for (int i = 0; i < n; i++){
  	scanf("%d %d %d %d",&x1[i],&y1[i],&x2[i],&y2[i]);
  	if (x1[i] > x2[i])
  		swap(x1[i],x2[i]);
  	if (y1[i] > y2[i])
  		swap(y1[i],y2[i]);
  }

  ll ans = 0;

  for (int i = 1; i < (1<<n); i++){
  	 int cnt = __builtin_popcount(i);
  	 if (cnt & 1)
  	 	ans = ans + s(i);
  	 else
  	 	ans = ans - s(i);
  }

  cout << abs(ans) << endl;

  return 0;
}

