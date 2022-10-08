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

#define TASKNAME "D"
#define TASKMOD "large"

typedef long long ll;
typedef long double ld;

void PreCalc(){
}

void solve(){
	vector<double> a, b;
	int n;
	scanf("%d",&n);
	a = vector<double>(n);
	b = vector<double>(n);
	for (int i = 0; i < n; i++)
		scanf("%lf",&a[i]);
	for (int i = 0; i < n; i++)
		scanf("%lf",&b[i]);

	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	{
		int ans = -1;
		for (int i = n; i >= 0; i--) {
			bool ok = true;
			for (int j = 0; j < i; j++)
				if (a[n - i + j] < b[j])
					ok = false;
			if (ok) {
				ans = i;
				break;
			}
		}
		assert(ans >= 0);
		printf("%d ", ans);
	}
	{
		int ans = 0;
		for (int i = 0; i < n; i++){
			for (int j = 0; j <= (int)b.size(); j++){
				if (j == (int)b.size()){
					ans++;
					b.erase(b.begin());
					break;
				}
				if (b[j] > a[i]){
					b.erase(b.begin() + j);
					break;
				}
			}
		}
		printf("%d\n", ans);
	}
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

  #pragma omp parallel for
  for (int testId = 1; testId <= testNum; testId++){
  	if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
	  	TIMESTAMPf("Test %d",testId);
  	printf("Case #%d: ",testId);
  	solve();                        
  }
      
  TIMESTAMP(end);
  return 0;
}