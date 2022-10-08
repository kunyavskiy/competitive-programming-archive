#include <iostream>
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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "E"

typedef long long ll;
typedef long double ld;

int gr[10000];


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

    gr[0] = gr[1] = gr[2] = 0;

//    printf("0 0 0");

    for (int i = 3; i < 10000; i++){
    	bool xx[3];
    	xx[0] = xx[1] = xx[2] = 0;
    	xx[gr[i-i/3]] = true;
    	xx[gr[(i/3)]] = true;
    	if (!xx[0]) gr[i] = 0;
    	else if (!xx[1]) gr[i] = 1;
     	else {
     		assert(!xx[2]);
     		gr[i] = 2;
     	}	
     	if (gr[i] == 2)
     		printf("%d\n",i);
//     	printf(" %d",gr[i]);
    }

   int cnt[3];
   cnt[0] = cnt[1] = cnt[2] = 0;

/*   for (int i = 0; i < 100; i++){
   	  cnt[gr[i]]++;
   	  printf("%d ",cnt[1]);
   } */

      
  return 0;
}