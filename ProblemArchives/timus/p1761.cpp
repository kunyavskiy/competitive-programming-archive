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

#define TASKNAME "1761"

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


string convert(int x){
	string tmp = "";
	do {
		tmp = char('0' + x % 2) + tmp;
	} while (x /= 2);
	return tmp;
}

int convert(string s){
	int res = 0;
	for (int i = 0; i < (int)s.size(); i++)	
		res = 2*res + s[i] - '0';
	return res;
}

string res;

vector<int> palins;
int maxv;

void addc(char c){
	res += c;
	vector<int> npalins;
	npalins.pb(0);
	npalins.pb(1);
	for (int i = 0; i < (int)palins.size(); i++){
		if (res[res.size() - palins[i] - 2] == res[res.size()-1])
			npalins.pb(palins[i]+2);
	}
	maxv = max(maxv, npalins.back());
	palins = npalins;
}

char buf[1100000];

void solve(int n){

    for (int i = 1; i <= n; i++){
    	string tmp = convert(i);
    	for (int i = 0; i < (int)tmp.size(); i++)
    		addc(tmp[i]);
    }
    printf("%d\n", maxv);
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    
    palins.pb(0);
    gets(buf);
    if (strlen(buf) <= 5) {
    	solve(convert(buf));
    	return 0;
    }

    int len = strlen(buf);
    int cnt = len - 6;
    bool any = false;
    
    for (int i = 1; buf[i+3]; i++)
    	if (buf[i] == '1')
    		any = true;
    if (buf[len - 3] == '1' && buf[len-2] == '1' && buf[len-1] == '1')
    	any = true;

    cnt += any;

    printf("%d\n", 13 + 3*cnt);
      
    return 0;
}