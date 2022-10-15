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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int a[110000];
int b[110000];



int main(){
  #ifdef LOCAL
  	ld start = clock();
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n;
  	cin >> n;
  	int sqn = sqrt(n * log((ld)n));
  	sqn = max(sqn,2);

  	for (int i = 0; i < n; i++){
  		scanf("%d",&a[i]);
  		b[i] = a[i];
  	}

  	for (int i = 0; i < n; i+= sqn)
  		sort(b+i,b + min(n,i+sqn));


  	int q;
  	scanf("%d",&q);

  	for (int it = 0; it < q; it++){
  	    int l,r,x;
  	    scanf("%d %d %d",&l,&r,&x);
  	    --l,--r;

  	    bool ok = false;

  	    for (;l % sqn != 0 && l <= r && !ok; l++)
  	    	ok |= a[l] == x;
  	    for (;r % sqn != sqn-1 && l <= r && !ok; --r)
  	    	ok |= a[r] == x;

  	    for (;l <= r && !ok; l += sqn)
  	    	ok |= binary_search(b+l,b+min(n,l+sqn),x);

  	    printf("%c","01"[ok]);	
  		
  	} 
  	printf("\n");


  #ifdef LOCAL
  	cerr << -(start - clock())/CLOCKS_PER_SEC << endl;
  #endif

	
  return 0;
}