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

#define TASKNAME "A"
#define TASKMOD "large"

typedef long long ll;
typedef long double ld;

void PreCalc(){
}

void solve(){
	ll cur = 0;
	int n;
	scanf(LLD"%d",&cur,&n);
	int ans = n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		scanf("%d",&a[i]);
	sort(a.begin(),a.end());
	int temp = 0;
	for (int i = 0; i < n; i++){
		if (cur > a[i]) {
			cur += a[i];                 
			ans = min(ans, temp + n - i - 1);    
		}
		else {
			if (cur == 1)
				break;
			temp++;
			cur += cur-1;
			i--;
		}                                
	}
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