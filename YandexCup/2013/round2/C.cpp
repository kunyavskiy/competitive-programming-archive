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

#define TASKNAME "C"

typedef long long ll;
typedef long double ld;

const int MAXN = 2100;

pair<int,int> p[MAXN];
int n;

bool cmp(const pair<int,int>& a,const pair<int,int>& b){
	return a.first * 1LL * b.second - a.second * 1LL * b.first < 0;
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	scanf("%d",&n);
  	for (int i = 0; i < n; i++)
  		scanf("%d %d",&p[i].first,&p[i].second);

  	ld ans = 0;
  	ld coef = 3.0/(n * 1LL * (n-1) * 1LL * (n-2));

  	for (int i = 0; i < n; i++){
  		sort(p+i,p+n);
  		for (int j = i+1; j < n; j++)
  			p[j].first -= p[i].first, p[j].second -= p[i].second;
  		sort(p+i+1,p+n,cmp);

  		ld sx, sy;

  		sx = sy = 0;
  		for (int j = i+1; j < n; j++){
  			ans += (p[j].first * sy - p[j].second * sx) * coef;
  			sx += p[j].first;
  			sy += p[j].second;
  		}



  		for (int j = i+1; j < n; j++)
  			p[j].first += p[i].first, p[j].second += p[i].second;
	}

	printf("%.18lf\n",(double)ans);

      
    TIMESTAMP(end);
    return 0;
}