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

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int a;char c;
    scanf("%d%c",&a,&c);
    if (1 <= a && a <= 2){
    	if (c == 'A' || c=='D')
    		printf("window\n");
    	else
    		printf("aisle\n");    			
    }
    else if (3 <= a && a <= 20){
    	if (c == 'A' || c == 'F')
    		printf("window\n");
    	else
    		printf("aisle\n");	
    }
    else {
    	if (c == 'A' || c == 'K')
    		printf("window\n");
    	else if (c == 'C' || c == 'D' || c == 'G' || c == 'H')
    		printf("aisle\n");
    	else
    		printf("neither\n");
    }
  return 0;
}