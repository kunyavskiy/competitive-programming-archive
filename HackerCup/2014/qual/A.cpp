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

#define TASKNAME "A"

typedef long long ll;
typedef long double ld;

void PreCalc(){
}

char s[25][25];

int getsum(int sz, int x,int y){
	int sum = 0;
	for (int i = 0; i < sz; i++)
		for (int j = 0; j < sz; j++)
			sum += (s[x + i][y + j] == '#');
    return sum;
}

void solve(){
    int n;
    scanf("%d",&n);
    int total = 0;
    for (int i = 0; i < n; i++)
       for (int j = 0; j < n; j++){
       	  scanf(" %c", &s[i][j]);
       	  total += (s[i][j] == '#');
       }

    for (int i = 1; i <= n; i++)
       if (i * i == total){
       	  for (int j = 0; j + i <= n; j++)
       	  	for (int k = 0; k + i <= n; k++){
       	  		int sum = getsum(i,j,k);
       	  		if (sum == total){
       	  			printf("YES\n");
       	  			return;
       	  		}
       	  	}
       }

    printf("NO\n");  
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