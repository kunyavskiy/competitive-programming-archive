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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "taxi"

typedef long long ll;
typedef long double ld;

ll d,m;
ll x[510000];
int n;


int main(){
  freopen(TASKNAME".in","r",stdin);
  freopen(TASKNAME".out","w",stdout);

  scanf(LLD" "LLD" %d",&m,&d,&n);
  for (int i = 0; i < n; i++)
  	scanf(LLD,&x[i]);

  sort(x,x+n);
  reverse(x,x+n);


  int best = n+1;
  for (int i = 0; i < n; i++) {
  	if (x[i] >= d + m){
  		best = 1;
  		break;
  	}
  	if (x[i+1] >= m-d) continue;
  	int cnt = 1;
  	ll curpos = 0;
  	for (int j = 0; j < n; j++){
  		if (i == j) continue;
  		if (x[j] <= d - curpos){
  			cnt = n+1;
  			break;
  		}
  		curpos += x[j] - (d - curpos);
  		if (curpos < m)
	  		cnt++;
//  		eprintf(LLD" to "LLD"\n", x[j],curpos);
  		if (m - curpos + d - curpos <= x[i]){
//  			eprintf("Done by "LLD". \n",x[i]);
  			best = min(best, cnt);
  			break;
  		}     
  	}
  	break;
  }

  if (best > n) best = 0;
  printf("%d\n",best);
      
  TIMESTAMP(end);
  return 0;
}