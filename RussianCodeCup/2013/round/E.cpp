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

#define TASKNAME "E"

typedef long long ll;
typedef long double ld;

const int MAXN = 160;

struct point{
	int x,y;
	point(){};
	point(int x,int y):x(x),y(y){}
};

point p[MAXN];

point operator-(const point& a,const point& b){
	return point(a.x - b.x, a.y - b.y);
}

double vp(const point& a,const point& b){
	return a.x * 1.0 * b.y - a.y * 1LL * b.x;
}

double sp(const point& a,const point& b){
	return a.x * 1.0 * b.x + a.y * 1LL * b.y;
}

double angle(const point& a, const point& b, const point& c){
	return abs(atan2(vp(b-a,c-b),sp(b-a,c-b)));
}


double ang[MAXN][MAXN][MAXN];
double d[MAXN][MAXN];


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	int n;
  	scanf("%d",&n);
  	for (int i = 0; i < n; i++)
  		scanf("%d %d",&p[i].x,&p[i].y);

  	for (int i = 0; i < n; i++)
	  	for (int j = 0; j < n; j++)
  			for (int k = i; k < n; k++)	
  				ang[i][j][k] = ang[k][j][i] = angle(p[i],p[j],p[k]);


	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			d[i][j] = 1e100;

	set<pair<double,int> > s;
	for (int i = 1; i < n; i++){
		d[0][i] = 0;
		s.insert(mp(0.0, i));
	}

	while (!s.empty()){
		int v = s.begin()->second;
		int b = v % 155;
		int a = v/155;
		if (b == 0){       
			printf("%.10lf\n",s.begin()->first*180.0/M_PI);
			TIMESTAMP(end);
			return 0;
		}
		s.erase(s.begin());
		for (int i = 0; i < n; i++)
			if (i != b && max(d[a][b], ang[a][b][i]) < d[b][i] - (1e-9)){
				s.erase(mp(d[b][i],b*155+i));
				d[b][i] = max(d[a][b], ang[a][b][i]);
				s.insert(mp(d[b][i],b*155+i));
			}
	}
  		

	assert(false);
      
    TIMESTAMP(end);
    return 0;
}