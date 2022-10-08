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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "C"

typedef long long ll;
typedef long double ld;

const int MAXN = 1100000;

int n,l,t;
int a[2*MAXN];


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  scanf("%d %d %d",&n,&l,&t);
  for (int i = 0; i < n; i++){
  	 scanf("%d",&a[i]);
  	 a[i+n] = a[i]+l;
  }

  t *= 2;
  double ans = n* 0.25 * (n-1) * (t / l);
  t %= l;

//  for (int it = 0; it < 2; it++){
    int ptr = 0;
    for (int i = 0; i < n; i++){
  		while (a[ptr] - a[i] <= t) ptr++;
  		ans += (ptr - i - 1) * 0.25;
  		eprintf("%d %d\n",i,ptr);
    }
/*    for (int i = 0; i < n; i++)
    	a[i] = (l - a[i]);
    reverse(a,a+n);
    for (int i = 0; i < n; i++)
    	a[i+n] = a[i] + l;
    eprintf("!!!%d %d\n",a[0],a[1]);
  }*/

  printf("%.2lf\n",ans);
      
  TIMESTAMP(end);
  return 0;
}