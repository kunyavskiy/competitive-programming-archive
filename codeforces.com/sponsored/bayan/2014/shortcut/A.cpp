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


char s[1000];

bool digit(string s) {
	for (int i = 0; i < (int)s.size(); i++)
		if (isdigit(s[i])) return 1;
	return 0;
}

bool smalllat(string s) {
	for (int i = 0; i < (int)s.size(); i++)
		if ('a' <= s[i] && s[i] <= 'z') return 1;
	return 0;
}

bool biglat(string s) {
	for (int i = 0; i < (int)s.size(); i++)
		if ('A' <= s[i] && s[i] <= 'Z') return 1;
	return 0;
}

bool nonalnum(string s) {
	for (int i = 0; i < (int)s.size(); i++)
		if (!isdigit(s[i]) && !isalpha(s[i])) return 1;
	return 0;
}

bool diff(string s) {
	vector<char> c;
	for (int i = 0; i < (int)s.size(); i++)
		c.pb(s[i]);
	sort(c.begin(), c.end());
	return unique(c.begin(), c.end()) == c.end();
}




void solve(){
	scanf("%s", s);
	int res = 0;
	res += digit(s);
	res += smalllat(s) || biglat(s);
	res += nonalnum(s);
	res += strlen(s) >= 6;
	res += strlen(s) >  10;
	res += smalllat(s) && biglat(s);
	res += diff(s);
	if (res < 4)
		printf("weak\n");
	else if (res < 6)
		printf("normal\n");
	else
		printf("strong\n");
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif
	
   int tst;
   scanf("%d",&tst);
   for (int i = 1; i <= tst; i++) {
   	  printf("Case #%d:\n", i);
   	  solve();
   }	
      
  return 0;
}