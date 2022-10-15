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

#define TASKNAME "proddiff"

typedef long long ll;
typedef long double ld;

int curans[50];
int bestans[50];
int blen,clen;

int pr[50],prptr;


void go(int n){
	if (clen > blen){
		memcpy(bestans,curans,sizeof(int)*clen);
		blen = clen;
		bestans[blen-1] *= n;
	}
//	eprintf("%d (%d)  %d %d %d %d\n",clen,n,curans[0],curans[1],curans[2],curans[3]);
	for (int i = 0; i < clen; i++)
		for (int j = 0; j < prptr; j++){
			if (curans[i]* 1LL * pr[j] > curans[clen-1] && n % (curans[i] * 1LL *pr[j]) == 0){
				curans[clen] = curans[i] * pr[j];
				clen++;
				go(n / curans[clen-1]);
				clen--;
			}
		}
}

int main(){
  freopen(TASKNAME".in","r",stdin);
  freopen(TASKNAME".out","w",stdout);

  int n;
  scanf("%d",&n);

  bestans[0] = curans[0] = 1;
  blen = clen = 1;
  int n0 = n;
  for (int i = 2; i * i <= n0; i++){
  	if (n % i == 0){
  		pr[prptr++] = i;
  		while (n0 % i == 0) n0 /= i;
  	}
  }
  if (n0 != 1) pr[prptr++] = n0;
  eprintf("%d\n",prptr);
  go(n);

  printf("%d\n",blen);
  for (int i = 0; i < blen; i++)
  	printf("%d%c",bestans[i]," \n"[i==blen-1]);
             
      
  TIMESTAMP(end);
  return 0;
}