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

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "1360"

typedef long long ll;
typedef long double ld;


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
    ld x,y,e;
    cin >> x >> y >> e;
    e /= 1.01;

    ld t = 0;
    ld temp = acos(y);

    for (; t += 2*M_PI;){
    	ld d = abs(x - sin(sqrt(t+temp)));
    	if (d < e){
			cout.precision(15);
			cout << fixed << t+temp << endl;
			return 0;
    	} 
    	d = abs(x - sin(sqrt(t-temp)));
    	if (d < e){
			cout.precision(15);
			cout << fixed << t-temp << endl;
			return 0;
    	} 
    }
    	

      
    TIMESTAMP(end);
    return 0;
}