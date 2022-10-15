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


int a[200][200];

int b[200][200];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n,m;
  	scanf("%d %d",&n,&m);
  	for (int i = 10; i < n+10; i++)
	  	for (int j = 10; j < m+10; j++)
	  		scanf("%d",&a[i][j]);

  	for (int i = 10; i < n+10; i++)
	  	for (int j = 10; j < m+10; j++)
	  		if (a[i][j] != 0)
	  			b[i][j] = -1;
	  		else {
	  			for (int l = 1; l <= 5 && !b[i][j]; l++){
	  				for (int k = 0; k <= l; k++){
	  					b[i][j] |= a[i+k][j+(l-k)];
	  					b[i][j] |= a[i+k][j-(l-k)];
	  					b[i][j] |= a[i-k][j+(l-k)];
	  					b[i][j] |= a[i-k][j-(l-k)];
					}
	  			}
	  		}	
  	for (int i = 10; i < n+10; i++,printf("\n"))
	  	for (int j = 10; j < m+10; j++)
			printf("%d ",b[i][j]);

    return 0;
}