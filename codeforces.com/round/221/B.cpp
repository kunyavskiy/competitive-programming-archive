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

#define TASKNAME "B"

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

char s[5100][5100];

int next[5100];
int cnt[5100];


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
    gets(s[0]);
    int n,m;
    sscanf(s[0],"%d %d",&n,&m);
    for (int i = 0; i < n; i++)
    	gets(s[i]);

    int ans = 0;

    for (int j = m - 1; j >= 0; j--){
    	memset(cnt, 0, sizeof(cnt));
    	for (int i = 0; i < n; i++){
    		if (s[i][j] == '0')
    			next[i] = 0;
    		else
    			next[i]++;
    		cnt[next[i]]++;
    	}
    	int sum = 0;
    	for (int j = m; j >= 0; j--){
    		sum += cnt[j];
    		ans = max(ans, sum * j);
    	}
    }

    printf("%d\n", ans);      
    return 0;
}