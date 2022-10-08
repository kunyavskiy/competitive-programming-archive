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

#define TASKNAME "C"
#define TASKMOD "large"

typedef long long ll;
typedef long double ld;

vector<string> dic;
vector<int> dicsz;

void PreCalc(){
	FILE* f = fopen("garbled_email_dictionary.txt","r");

	char buf[100];
	while (fgets(buf,sizeof(buf),f)){
	    int len = strlen(buf);
	    while (buf[len-1] == '\n' || buf[len-1] == '\r')
	    	len--;
	    buf[len] = 0;
	    dic.pb(buf);
	    dicsz.pb(dic.back().size());
	}

	fclose(f);
}

const int MAXN = 4100;

int dp[MAXN][6];

char s[MAXN];

void match(int pos,int str,int curlast,int& last,int& cost){
	string& t = dic[str];
	int len = t.size();
	last = curlast;
	cost = 0;
	for (int i = 0; i < len; i++){
		last++;
		if (t[i] != s[pos + i]){
			if (last < 5) {
				cost = -1;
				return;
			}
			cost++;
			last = 0;
		}
	}
}

void solve(){
	memset(dp,63,sizeof(dp));
	gets(s);
	int len = strlen(s);

	dp[0][5] = 0;

	int sz = (int)dic.size();

	for (int i = 0; i < len; i++)
		for (int j = 0; j < 6; j++){
		   if (dp[i][j] > 100000) continue;   
		   for (int k = 0; k < sz; k++){
			   int cost = -1;
			   int last = 5;
			   if (i + dicsz[k] > len) continue;
			   match(i,k,j,last,cost);
			   if (cost == -1) continue;
			   last = min(last,5);
			   dp[i+dicsz[k]][last] = min(dp[i+dicsz[k]][last], dp[i][j] + cost);
		   }            	       
		}

	int ans = *min_element(dp[len],dp[len] + 6);
	assert(ans <= len);
	printf("%d\n",ans);	
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
  	printf("Case #%d: ",testId);
  	solve();                        
  }
      
  TIMESTAMP(end);
  return 0;
}