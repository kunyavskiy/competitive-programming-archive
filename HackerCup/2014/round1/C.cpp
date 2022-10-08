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

#define TASKNAME "c"

typedef long long ll;
typedef long double ld;

void PreCalc(){
}

char x[510][510];
int d[2][510][510];
int d2[510][510];

void solve(){
	int n, m;
	scanf("%d %d ",&n,&m);
	for (int i = 0; i < n; i++){
		scanf(" %s", x[i]);
		assert((int)strlen(x[i]) == m);
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		   d[0][i][j] = d[1][i][j] = d2[i][j] = -1e9;
    d[0][0][0] = 1;
    d[1][0][0] = 1;
    for (int i = 0; i < n; i++)
    	for (int j = 0; j < m; j++){
             if (x[i][j] == '#') {
                d[0][i][j] = d[1][i][j] = -1e9;
                continue;
             }
             int nd = max(d[0][i][j], d[1][i][j]);
             if (i != n-1)
                d[0][i+1][j] = max(d[0][i+1][j], nd+1);
             if (j != m-1)
                d[1][i][j+1] = max(d[1][i][j+1], nd+1);
       }

/*    for (int i = 0; i < n; i++)
    	for (int j = 0; j < m; j++)
    		eprintf("%d%c", d[0][i][j], " \n"[j==m-1]);
    for (int i = 0; i < n; i++)
    	for (int j = 0; j < m; j++)
    		eprintf("%d%c", d[1][i][j], " \n"[j==m-1]);*/


    int ans = 0;

    for (int i = 0; i < n; i++)
    	for (int j = 0; j < m; j++){
          for (int k = i-1; k >= 0; k--){
             if (x[k][j] == '#')
                break;
             ans = max(ans, d[1][i][j] + (i - k));
             if (j != m-1)
                d2[k][j+1] = max(d2[k][j+1], d[1][i][j] + (i - k) + 1);
          }
          for (int k = j-1; k >= 0; k--){
             if (x[i][k] == '#')
                break;
             ans = max(ans, d[0][i][j] + (j - k));
             if (i != n-1)
                d2[i+1][k] = max(d2[i+1][k], d[0][i][j] + (j - k) + 1);
          }
       }

/*    eprintf("\n");
    for (int i = 0; i < n; i++)
    	for (int j = 0; j < m; j++)
    		eprintf("%d%c", d2[i][j], " \n"[j==m-1]);*/


    for (int i = 0; i < n; i++)
    	for (int j = 0; j < m; j++){
             if (x[i][j] == '#') {
                d2[i][j] = -1e9;
                continue;
             }
             int nd = d2[i][j];
             if (i != n-1)
                d2[i+1][j] = max(d2[i+1][j], nd+1);
             if (j != m-1)
                d2[i][j+1] = max(d2[i][j+1], nd+1);
       }
/*    eprintf("\n");
    for (int i = 0; i < n; i++)
    	for (int j = 0; j < m; j++)
    		eprintf("%d%c", d2[i][j], " \n"[j==m-1]);*/


    for (int i = 0; i < n; i++)
    	for (int j = 0; j < m; j++)
    		ans = max(ans, d2[i][j]);
    for (int i = 0; i < n; i++)
    	for (int j = 0; j < m; j++)
    		ans = max(ans, d[0][i][j]);
    for (int i = 0; i < n; i++)
    	for (int j = 0; j < m; j++)
    		ans = max(ans, d[1][i][j]);

    printf("%d\n", ans);
}


int main(){
  freopen(TASKNAME".in","r",stdin);
  freopen(TASKNAME".out","w",stdout);
	
  PreCalc();	
  TIMESTAMP(PreCalc);

  int testNum;

  {
     char buf[1000];
     gets(buf);
     sscanf(buf,"%d",&testNum);
  }

  for (int testId = 1; testId <= testNum; testId++){
  	printf("Case #%d: ",testId);
  	solve();                        
  	if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
	  	TIMESTAMPf("Test %d solved",testId);
  }
      
  TIMESTAMP(end);
  return 0;
}