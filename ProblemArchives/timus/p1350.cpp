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

#define TASKNAME "1350"

typedef long long ll;
typedef long double ld;

set<string> have;

int bad[11100];
char buf[111111];


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  int n;
  scanf("%d",&n);

  for (int i = 0; i < n; i++){
  	scanf("%s",buf);
  	have.insert(buf);
  }

  int k;
  scanf("%d",&k);
  int cnt;
  scanf("%d",&cnt);
  for (int i = 0; i < cnt; i++){
  	scanf("%s",buf);
  	have.erase(buf);
  }

  for (int i = 0; i < k; i++){
  	int cnt;
  	scanf("%d",&cnt);
  	for (int j = 0; j < cnt; j++){
  		scanf("%s",buf);
  		bad[i] += have.count(buf);
  	}
  }
      
  int m;
  scanf("%d",&m);
  for (int i = 0; i < k; i++)
  	if (bad[i] == 0)
  		printf("YES\n");
  	else if (bad[i] + m <= (int)have.size())
  		printf("MAYBE\n");
  	else
  		printf("NO\n");

  TIMESTAMP(end);
  return 0;
}