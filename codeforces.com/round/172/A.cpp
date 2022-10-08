#include <iostream>
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

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.", clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "A"

typedef long long ll;
typedef long double ld;


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  ld w,h,ang;
  int _ang;
  cin >> w >> h >> _ang;
  if (_ang > 90)
  	_ang = 180 - _ang;
  if (_ang == 0) {
  	printf("%.18lf\n",(double)(w*h));
  	return 0;
  }
  if (_ang == 90){
  	printf("%.18lf\n",double(min(w,h)*min(w,h)));
  	return 0;
  }                  
  ang = _ang;
  ang /= 180;
  ang *= M_PI;

  w /= 2, h /= 2;

  ld y1 = (1 - cos(ang))/sin(ang)*w;
  ld y2 = (-h + w*sin(ang))/cos(ang);



  double l1 = h - y1;
  double l2 = y2 + h;

  cerr << l1 <<" "<<l2 << endl;

  printf("%.18lf\n",double(4*w*h - l1*l1*tan(ang)-l2*l2/tan(ang)));
      
  TIMESTAMP(end);
  return 0;
}