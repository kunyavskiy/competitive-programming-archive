#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
    #define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 18;

int n;
char s[310];

int dp[(1<<MAXN)+10];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	scanf("%d %s",&n,s);
  	if (n > MAXN){
  		printf("NO\n");
  		return 0;
  	}


  	for (int i = 0;s[i]; i++){
  		int t = s[i] - 'a';
  		if (t >= n) continue;
  		for (int j = (1<<n)-1; j; j--)
  			if ((j & (1<<t)) && dp[j ^ (1<<t)] == (j ^ (1<<t)))
  				dp[j] |= (1<<t); 				
  	}

  	if (dp[(1<<n)-1] == (1<<n)-1)
  		puts("YES\n");
  	else
  		puts("NO\n");
  		

    return 0;
}