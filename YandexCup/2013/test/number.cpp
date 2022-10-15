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

#define TASKNAME "number"

typedef long long ll;
typedef long double ld;


int main(){
   freopen(TASKNAME".in","r",stdin);
   freopen(TASKNAME".out","w",stdout);

   char s[100];
   while (gets(s)){

     int ans = 10000;

     for (int i = 0; i < 256; i++)
     	if (__builtin_popcount(i) == 4){
     		int val = 0;
     		for (int j = 0; j < 8; j++)
     			if (i & (1<<j))
     				val = 10 * val + s[j] - '0';
     		ans = min(ans,val);
     	}

      printf("%d\n",ans);
      #ifndef LOCAL
         break;
      #endif	
    }
      
    TIMESTAMP(end);
    return 0;
}