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

#define TASKNAME "1103"

typedef long long ll;
typedef long double ld;

struct point{
	int x,y;
	point(){}
	point(int x,int y):x(x),y(y){
	}
	bool operator<(const point& r) const{
		if (y != r.y) return y < r.y;
		return x < r.x;
	}
};

point operator-(const point& a,const point& b){
	return point(a.x - b.x, a.y - b.y);
}

ll scal(const point& a,const point& b){
	return a.x * 1LL * b.x + a.y * 1LL * b.y;
}

ll vect(const point& a,const point& b){
	return a.x * 1LL * b.y - a.y * 1LL * b.x;
}


point p[5100];
int n;

bool cmp(const point& a,const point& b){
	return atan2(vect(a - p[0], a - p[1]), scal(a - p[0], a - p[1])) < atan2(vect(b - p[0], b - p[1]), scal(b - p[0], b - p[1])) - (1e-9);
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	scanf("%d",&n);
  	for (int i = 0; i < n; i++){
  		scanf("%d%d",&p[i].x,&p[i].y);
  	}

  	sort(p,p+n);

  	for (int j = 1; j < n; j++){
  		bool ok = true;
  		swap(p[j], p[1]);
  		for (int i = 2; i < n && ok; i++)
  			if (vect(p[i] - p[0], p[1] - p[0]) < 0)
  				ok = false;
  	    if (ok) break;
  	}

  	printf("%d %d\n%d %d\n",p[0].x,p[0].y, p[1].x,p[1].y);
  	nth_element(p+2,p+(n-3)/2+2,p+n,cmp); 
	printf("%d %d\n",p[(n-3)/2+2].x,p[(n-3)/2+2].y);
    TIMESTAMP(end);
    return 0;
}