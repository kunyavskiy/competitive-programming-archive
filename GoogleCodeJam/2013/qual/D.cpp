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

#define TASKNAME "D"
#define TASKMOD "small"

typedef long long ll;
typedef long double ld;

int k,n;
int dp[(1<<20)+10];
int cnt[300];
int ccnt[30][300];
int need[30];

void PreCalc(){
}

void go(int v){
	if (!v) return;
	go(v ^ (1<<dp[v]));
	printf(" %d",dp[v]+1);
}

void solve(){
	scanf("%d %d",&k,&n);
	memset(cnt,0,sizeof(cnt));
	memset(ccnt,0,sizeof(ccnt));
	for (int i = 0; i < k; i++){
		int a;
		scanf("%d",&a);
		cnt[a]++;  
	}
	for (int j = 0; j < n; j++){
		scanf("%d",&need[j]);
		int k;
		scanf("%d",&k);
		for (int i = 0; i < k; i++){
			int a;
			scanf("%d",&a);
			ccnt[j][a]++;
		}                			
	}

	memset(dp,-1,sizeof(dp));
	dp[0] = -2;
	queue<int> q;
	q.push(0);
	while (!q.empty()){
		int i = q.front(); q.pop();
		if (dp[i] == -1) continue;
		//eprintf("%d\n",i);
		for (int j = 0; j < n; j++) if (!(i & (1<<j))){
			int have = cnt[need[j]];
			for (int k = 0; k < n; k++)
				if (i & (1<<k)){
					have += ccnt[k][need[j]];
					have -= need[k] == need[j];
				}
			if (have > 0 && dp[i | (1<<j)] == -1){
				//eprintf("%d -> %d (have[%d] = %d)\n",i,j,need[j],have);
				dp[i | (1<<j)] = j; 
				q.push(i | (1<<j));
			}
		}
	}

	if (dp[(1<<n)-1] == -1) printf(" IMPOSSIBLE\n");
	else go((1<<n)-1),printf("\n");
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
  	if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
	  	eprintf("Test %d\n",testId);
  	printf("Case #%d:",testId);
  	solve();                        
  }
      
  TIMESTAMP(end);
  return 0;
}