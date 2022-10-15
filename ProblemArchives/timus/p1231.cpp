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


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    
    int k;
    scanf("%d",&k);

    printf("%d\n", 6*k+13);
    for (int i = 1; i < k; i++){
    	printf("%d - %d - >\n",i,i+1);
    	printf("%d + %d + >\n",i,i);
    	printf("%d # %d # <\n",i,i+k);
    }
    printf("%d - %d - >\n",k,2*k+1);
    printf("%d + %d + >\n",k,k);
    printf("%d # %d # <\n",k,k+k);

    for (int i = k+1; i <= 2*k; i++){
    	printf("%d - %d - <\n",i,i);
    	printf("%d + %d + <\n",i,i);
    	printf("%d # %d # >\n",i,i-k);
    }

   	printf("%d - %d - <\n",2*k+1,2*k+3);
   	printf("%d + %d + >\n",2*k+1,2*k+1);
   	printf("%d # %d # <\n",2*k+1,2*k+2);

   	printf("%d - %d - <\n",2*k+2,2*k+4);
   	printf("%d + %d + <\n",2*k+2,2*k+2);

   	printf("%d - %d + =\n",2*k+3,1);
   	printf("%d + %d + <\n",2*k+3,2*k+3);

   	printf("%d - %d - >\n",2*k+4,2*k+6);
   	printf("%d + %d + <\n",2*k+4,2*k+4);
   	printf("%d # %d # >\n",2*k+4,2*k+5);

   	printf("%d + %d + >\n",2*k+5,2*k+5);

   	printf("%d - %d + =\n",2*k+6,1);
   	printf("%d + %d + >\n",2*k+6,2*k+6);

    return 0;
}