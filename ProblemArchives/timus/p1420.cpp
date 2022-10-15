//#include <iostream>
#include <complex>
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

#define TASKNAME "1420"

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
typedef long double ld;

#undef assert
#define assert(x) while(!(x))

complex<ll> a, b;

ll mabs (complex<ll> a)
{
  return a.real()*a.real()+a.imag()*a.imag();
}


struct Comparer {
bool operator()(const complex<ll>& a, const complex<ll>& b){
	if (a.real() != b.real()) return a.real() < b.real();
	return a.imag() < b.imag();
}
};

complex<ll> read() {
  int x, y;
  assert(scanf("%d%d", &x, &y) == 2);
  return complex<ll>(x,y);
}

complex<ll> operator % (complex<ll> a, complex<ll> b)
{
  complex<ll> tmp=a*conj(b);
  ll x=tmp.real();
  ll y=tmp.imag();
  ll d=mabs(b);
  a-=b*(x/d);
  a-=b*(y/d)*complex<ll>(0,1);
//  assert(mabs(a)<mabs(b));
  return a;
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
    while (!feof(stdin)) {
  #endif

    
    a = read();
    b = read();
    //assert(b != complex<ll>(0,0));

    if (b == complex<ll>(0,0)){
    	printf("0\n");
    	return 0;
    }

    a = a % b;

    set< complex<ll>, Comparer > s;

    for (int i = -5; i <= 5; i++)
    	for (int j = -5; j <= 5; j++) {
    		complex<ll> t = a + b * complex<ll>(i, j);
    		if (mabs(t) < mabs(b)) s.insert(t);
    	}

    printf("%d\n", s.size());

    #ifdef LOCAL
    }
    #endif
      
    return 0;
}