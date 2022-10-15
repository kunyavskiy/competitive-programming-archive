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

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "1704"

#ifdef LOCAL
static struct __timestamper {
    string what;
    __timestamper(const char* what) : what(what){};
    __timestamper(const string& what) : what(what){};
	~__timestamper(){
        TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef double ld;

int n, t;

vector<vector<ld> > v;

#ifndef LOCAL
const ld M_PI = acos(-1.0);
#endif

ld getzero(){
	ld b = 0;
	for (int i = 0; i < (int)v.size(); i++){
		b += v[i][0];
	}
	return b / n;
}

ld getamp(){
	ld a, b;
	a = 0, b = 0;
	for (int i = 7; i < (int)v.size(); i += 8){
		for (int k = 0; k < t; k++) {
			ld tmp = sin(4*k*M_PI/t);
			a += tmp * tmp;
			b -= 2*tmp*v[i][k];
		}
	}
	return -b / (2*a);
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    scanf("%d %d",&n,&t);
    n /= t;

    v = vector< vector<ld> > (n, vector<ld>(t));

    for (int i = 0; i < n; i++)
    	for (int j = 0; j < t; j++) {
    		double temp;
    		scanf("%lf",&temp);
    		v[i][j] = temp;
    	}

    ld ZERO = getzero();
    ld AMP = getamp();

    for (int i = 0; i < n; i++)
    	for (int j = 0; j < t; j++) {
    		v[i][j] -= ZERO;
    		v[i][j] /= AMP;
    	}

    eprintf("ZERO : %.5lf\n", (double)ZERO);
    eprintf("AMP : %.5lf\n", (double)AMP);

   	char c = 0;

    for (int i = 0; i < n; i++){
    	ld err[2];
    	err[0] = err[1] = 0;
    	for (int j = 0; j < t; j++) {
    		err[0] += (sin(4*j*M_PI/t) - v[i][j]) * (sin(4*j*M_PI/t) - v[i][j]);
    		err[1] += (sin(2*j*M_PI/t) - v[i][j]) * (sin(2*j*M_PI/t) - v[i][j]);
    	}
    	if (err[1] < err[0])
    		c |= (1<<(i % 8));
        if (i % 8 == 7){
        	printf("%c", c);
        	c = 0;
        }
    }

      
    return 0;
}