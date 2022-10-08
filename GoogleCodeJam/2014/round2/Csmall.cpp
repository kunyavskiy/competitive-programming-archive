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

#define TASKNAME "C"
#define TASKMOD "small"

typedef long long ll;
typedef long double ld;

void PreCalc(){
}

const int MAXN = 550;

int cost[MAXN][MAXN];
int dist[MAXN][MAXN];


void solve(){
	int w, h, b;
	scanf("%d %d %d",&w,&h,&b);

	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			cost[i][j] = 1;

	for (int i = 0; i < b; i++){
		int x0, y0, x1, y1;
		scanf("%d %d %d %d",&x0,&y0,&x1,&y1);
		for (int i = x0; i <= x1; i++)
			for (int j = y0; j <= y1; j++)
				cost[i][j] = 0;
	}

	memset(dist, 1, sizeof(dist));

	deque<int> qx, qy;

	for (int i = 0; i < h; i++)
		if (cost[0][i] == 0)
			qx.pb(0), qy.pb(i), dist[0][i] = 0;

	for (int i = 0; i < h; i++)
		if (cost[0][i] == 1)
			qx.pb(0), qy.pb(i), dist[0][i] = 1;

	int ans = 1<<30;
	while (!qx.empty()){
		int x = qx.front(); qx.pop_front();
		int y = qy.front(); qy.pop_front();
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++){
				int nx = x + i;
				int ny = y + j;
				if (nx < 0 || ny < 0 || ny >= h) continue;
				if (nx >= w) {
					ans = min(ans, dist[x][y]);
					continue;
				}
				if (dist[nx][ny] <= dist[x][y] + cost[nx][ny]) continue;
				dist[nx][ny] = dist[x][y] + cost[nx][ny];
				if (cost[nx][ny] == 0) 
					qx.push_front(nx), qy.push_front(ny);
				else 
					qx.push_back(nx), qy.push_back(ny);
			}
	}
	printf("%d\n", ans);
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