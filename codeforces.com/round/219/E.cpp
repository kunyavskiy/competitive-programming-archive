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

#define TASKNAME "E"

#ifdef LOCAL
static struct __timestamper {
    string what;
    __timestamper(const char* what) : what(what){};
    __timestamper(const string& what) : what(what){};
	~__timestamper(){
        TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#endif

typedef long long ll;
typedef long double ld;

struct Rat {
	int num, denum;
	Rat():num(0),denum(1){
	}
	Rat(int _num, int _denum) {
		num = _num;
		denum = _denum;
		if (denum < 0) num *= -1, denum *= -1;
		int g = __gcd(num, denum);
		if (g){
    		num /= g;
    		denum /= g;
    	}
	}
	Rat(int x){
		num = x;
		denum = 1;
	}
	bool operator==(const Rat& r) const{
		return num == r.num && denum == r.denum;
	}
	// not really less, just any order
	bool operator<(const Rat& r) const{
		if (num != r.num) return num < r.num;
		return denum < r.denum;
	}
};

Rat operator+(Rat a, Rat b){
	return Rat(a.num * b.denum + b.num * a.denum, a.denum * b.denum);
}

Rat operator-(Rat a, Rat b){
	return Rat(a.num * b.denum + b.num * a.denum, a.denum * b.denum);
}

Rat operator*(Rat a, Rat b){
	return Rat(a.num * b.num, a.denum * b.denum);
}

Rat operator~(Rat a){
	return Rat(a.denum, a.num);
}

Rat operator/(Rat a, Rat b){
	return a * ~b;
}

struct point {
	Rat x, y;
	point(){
	}
	point(Rat x, Rat y):x(x), y(y){
	}
	bool operator==(const point& a) const{
		return x == a.x && y == a.y;
	}
	bool operator<(const point& a) const{
		if (!(x == a.x)) return x < a.x;
		return y < a.y;
	}
};

point operator+(const point& a, const point& b){
	return point(a.x + b.x, a.y + b.y);
}

point operator-(const point& a, const point& b){
	return point(a.x - b.x, a.y - b.y);
}


point operator/(const point& a, Rat b){
	return point(a.x / b, a.y / b);
}


point operator~(const point& a){
	return point(a.x / (a.x * a.x + a.y * a.y), a.y / (a.x * a.x + a.y * a.y));
}


point load(){
	int a,b,c,d;
	scanf("%d %d %d %d",&a,&b,&c,&d);
//	#warning no inverse
	return ~point(Rat(a, b), Rat(c, d));
}


point inp[1100];
pair<point,Rat> pt[1100100];

const int MOD = 1000000007;

int pow(int a,int b){
	if (!b) return 1;
	if (b & 1) return (pow(a, b-1) * 1LL * a) % MOD;
	int temp = pow(a, b/2);
	return (temp * 1LL * temp) % MOD;
}




int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	int n;
  	scanf("%d",&n);
  	for (int i = 0; i < n; i++)
  		inp[i] = load();
  	int ptr = 0;
  	for (int i = 0; i < n; i++)	
  	    for (int j = i+1; j < n; j++){
  	    	pt[ptr++] = mp((inp[i] + inp[j]) / 2, (inp[j] - inp[i]).x / (inp[j] - inp[i]).y);
  	    }	

  	stable_sort(pt, pt+ptr);

  	int ans = 0;

  	for (int i = 0; i < ptr;){
  		int j = i;
  		for (; j < ptr && pt[i].first == pt[j].first; j++);
  		ans = (ans + pow(2, j - i) - 1) % MOD;
  		i = j;
  	}

  	for (int i = 0; i < ptr;){
  		int j = i;
  		for (; j < ptr && pt[i] == pt[j]; j++);
  		ans = (ans - pow(2, j - i) + 1) % MOD;
  		i = j;
  	}


  	printf("%d\n", (ans - ptr + MOD)% MOD);
      
    return 0;
}