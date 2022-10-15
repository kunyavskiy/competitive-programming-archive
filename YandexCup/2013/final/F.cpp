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

#define TASKNAME "F"

typedef long long ll;
typedef long double ld;


const int MOD = 1000000007;


int n;
int a[55][55];
int b[55][55];
int temp[55][55];

void multiply(int a[][55],int b[][55],int c[][55]){
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			c[i][j] = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		    for (int k = 0; k < n; k++)
		    	c[i][j] = (c[i][j] + a[i][k] * 1LL * b[k][j]) % MOD;
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  int t;
  scanf("%d %d",&t,&n);

  n++;
  for (int i = 0; i < n-1; i++)
  	for (int j = 0; j <= i; j++)
  		a[n-i-2][j] = (1LL<<(i-j)) % MOD;
 
  for (int i = 0; i < n; i++)
  	a[n-1][i] = 1;

  for (int i = 0; i < n; i++)
     b[i][i] = 1;


/*  for (int i = 0; i < n; i++)
  	for (int j = 0; j < n; j++)
  		eprintf("%d%c",a[i][j]," \n"[j==n-1]);	*/

  t++;
  for (int i = 0; (1LL<<i) <= t; i++){
  	if (t & (1<<i)){
  		multiply(a, b, temp);
  		memcpy(b, temp,sizeof(b));
  	}
  	multiply(a, a, temp);
	memcpy(a, temp,sizeof(a));
  }

  printf("%d\n",(int)((b[n-1][0] * 1LL * b[n-1][0]) % MOD)); 

      
  TIMESTAMP(end);
  return 0;
}