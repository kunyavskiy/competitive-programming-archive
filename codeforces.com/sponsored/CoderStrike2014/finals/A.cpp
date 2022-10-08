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

#define TASKNAME "A"

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


char bad[255];
char s[110000];
char t[110000];


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	memset(bad, 1, sizeof(bad));
  	bad['A'] = 0;
  	bad['H'] = 0;
  	bad['I'] = 0;
  	bad['M'] = 0;
  	bad['O'] = 0;
  	bad['T'] = 0;
  	bad['U'] = 0;
  	bad['V'] = 0;
  	bad['W'] = 0;
  	bad['X'] = 0;
  	bad['Y'] = 0;

  	gets(s);
  	for (int i = 0; s[i]; i++) {
  		if (bad[(unsigned char)s[i]]) {
  			printf("NO\n");
  			return 0;
  		}
  		t[i] = s[i];
  	}
  	reverse(t, t + strlen(s));

  	if (strcmp(s, t))
  		printf("NO\n");
  	else	
	  	printf("YES\n");
    return 0;
}