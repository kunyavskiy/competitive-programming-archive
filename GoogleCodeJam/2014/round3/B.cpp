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

#define TASKNAME "B"
#define TASKMOD "large"

typedef long long ll;
typedef long double ld;

const int inf = 1e9;

void PreCalc(){
}

const int MAXN = 110;
const int MAXMOVES = MAXN * 100;

int dp[MAXMOVES];
int ndp[MAXMOVES];

void solve(){
    for (int i = 0; i < MAXMOVES; i++)
        dp[i] = -inf;
    dp[1] = 0;

    int p, q;
    int n;
    scanf("%d%d%d",&p,&q,&n);
    for (int i = 0; i < n; i++) {
        for (int i = 0; i < MAXMOVES; i++)
            ndp[i] = -inf;

        int h, g;
        scanf("%d%d",&h,&g);

        {
            int tm = (h + q  - 1) / q ;
            for (int i = 0; i + tm < MAXMOVES; i++)
                ndp[i + tm] = max(ndp[i + tm], dp[i]);
        }

        {
        	int tm = (h + p - 1) / p;
        	for (int i = tm; i < MAXMOVES; i++)
        		ndp[i - tm] = max(ndp[i - tm], dp[i] + g);
        }

        {
           int tm = 0;
  //         eprintf("h = %d;", h);
           while ((h-1) % q + 1 > p && h >= 0) h -= p, tm--;
           if (h > q) {
           	  tm += (h + q - 1) / q - 2;
//           	  eprintf("%d\n", tm);
           	  for (int i = 0; i < MAXMOVES; i++)
           	  	if (0 <= i + tm && i + tm < MAXMOVES)
           	  		ndp[i + tm] = max(ndp[i + tm], dp[i] + g);
           } 
        } 
        memcpy(dp, ndp, sizeof(dp));
    }
    printf("%d\n", *max_element(dp, dp + MAXMOVES));
}


int main(){
  freopen(TASKNAME"-"TASKMOD".in","r",stdin);
  freopen(TASKNAME"-"TASKMOD".out","w",stdout);
    
  PreCalc();
  TIMESTAMP(PreCalc);    

  char buf[1000];
  int testNum;
  gets(buf);
  sscanf(buf,"%d",&testNum);

  for (int testId = 1; testId <= testNum; testId++){
      if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
          TIMESTAMPf("Test %d",testId);
      printf("Case #%d: ",testId);
      solve();                        
  }
      
  TIMESTAMP(end);
  return 0;
}