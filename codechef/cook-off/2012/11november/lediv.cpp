// WHAT'S WRONG WITH YOU GUYS??? WTF IS PENTIUM 3??? PLEASE UPGRADE SERVERS! IT'S RIDICULOUS TO TEST SOLUTIONS ON 9-YEAR OLD SYSTEM!"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 110000;

int mv[MAXN];

void solve(){
	int n;
	scanf("%d",&n);
	int a = 0;
	for (int i = 0; i < n; i++){
		int b;
		scanf("%d",&b);
		a = __gcd(a,b);
	}
	if (a == 1)
		printf("-1\n");
	else
		printf("%d\n",mv[a]);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

   for (int i = 2; i < MAXN; i++){
   	  if (mv[i] == 0){
   	  	mv[i] = i;

   	  	for (ll j = i*1LL*i; j < MAXN; j+=i)
   	  		if (mv[j] == 0 || mv[j] > i)
   	  			mv[j] = i;
   	  }
   }

   int t;
   scanf("%d",&t);
   while (t-->0)
   	solve();

  return 0;
}