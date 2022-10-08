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
#define TASKMOD "large"

typedef long long ll;
typedef long double ld;

void PreCalc(){
}

int na[2100];
int nb[2100];
int a[2100];
int b[2100];

int ans[2100];
//bool used[2100];
int n;

void _myassert(bool q,string s){
	if (q) return;
	for (int k = 0; k < n; k++)
		eprintf("%2d%c",ans[k]," \n"[k==n-1]);
	for (int k = 0; k < n; k++)
		eprintf("%2d%c",a[k]," \n"[k==n-1]);
	for (int k = 0; k < n; k++)
	    eprintf("%2d%c",b[k]," \n"[k==n-1]);
	eprintf("\n");
	for (int k = 0; k < n; k++)
		eprintf("%2d%c",na[k]," \n"[k==n-1]);
	for (int k = 0; k < n; k++)
	   eprintf("%2d%c",nb[k]," \n"[k==n-1]);
	eprintf("%s\n",s.data());
	assert(false);
}

#define myassert(x) _myassert(x,#x)

void solve(){
	scanf("%d",&n);
	for (int i = 0; i < n; i++)	
		scanf("%d",&na[i]);
	for (int i = 0; i < n; i++)	
		scanf("%d",&nb[i]);

	for (int i = 0; i < n; i++)
		ans[i] = -1;

	for (int i = 0; i < n; i++)
		a[i] = b[i] = 1;

	for (int i = 0; i < n; i++){
		for (int j = 0; j <= n; j++){
			myassert (j != n);			
			if (ans[j] != -1) continue;
//			eprintf("!!%d %d %d %d %d\n",j,a[j],na[j],b[j],nb[j]);
			if (a[j] == na[j] && b[j] == nb[j]){
				bool ok = true;
				for (int k = 0; k < n && ok; k++) {
					ok &= (ans[k] != -1 || ((a[j]+1)*(k > j) <= na[k] && (b[j]+1)*(k < j) <= nb[k]));
				}
				if (!ok) continue;
				ans[j] = i;
//				used[j] = true;
				for (int k = 0; k < j; k++){
					if (ans[k] == -1)
					    b[k] = max(b[k],b[j]+1);
				}	
				for (int k = j+1; k < n; k++){
					if (ans[k] == -1)
					    a[k] = max(a[k],a[j]+1);
				}
				for (int k = 0; k < n; k++)
					myassert(ans[k] != -1 || (a[k] <= na[k] && b[k] <= nb[k]));
				break;
			}
		}
	}

	for (int i = 0; i < n; i++)
		printf("%d%c",ans[i]+1," \n"[i==n-1]);
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