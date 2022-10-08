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

void PreCalc(){
}

int a[110][110];
bool used[110][110];
int n,m;

void solve(){
	scanf("%d %d",&n,&m);
	for (int i = 0;i < n; i++)	
		for (int j = 0; j < m; j++)
			scanf("%d",&a[i][j]), used[i][j] = 0;

	while (true){
		bool any = false;
		for (int i = 0; i < n; i++){
			int curh = -1;
			for (int j = 0; j < m; j++)
				if (!used[i][j])
					curh = a[i][j];

			for (int j = 0; j < m; j++)
				if (!((used[i][j] && a[i][j] <= curh) || (!used[i][j] && a[i][j] == curh)))
					curh = -1;

			if (curh != -1){
				any = true;
				for (int j = 0; j < m; j++)
					used[i][j] = true;
			}   
		}

		for (int j = 0; j < m; j++){
			int curh = -1;
			for (int i = 0; i < n; i++)
				if (!used[i][j])
					curh = a[i][j];

			for (int i = 0; i < n; i++)
				if (!((used[i][j] && a[i][j] <= curh) || (!used[i][j] && a[i][j] == curh)))
					curh = -1;

			if (curh != -1){
				any = true;
				for (int i = 0; i < n; i++)
					used[i][j] = true;
			}   
		}
		if (!any) break;
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (!used[i][j]){
				printf("NO\n");
				return;
			}
	printf("YES\n");
}


int main(){
  freopen(TASKNAME"-"TASKMOD".in","r",stdin);
  freopen(TASKNAME"-"TASKMOD".out","w",stdout);
	
  PreCalc();	

  char buf[1000];
  int testNum;
  gets(buf);
  sscanf(buf,"%d",&testNum);

  for (int testId = 1; testId <= testNum; testId++){
  	printf("Case #%d: ",testId);
  	solve();
  	if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
	  	eprintf("Test %d\n",testId);
  }
      
  TIMESTAMP(end);
  return 0;
}