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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "D"

typedef long long ll;
typedef long double ld;


int a[10][10][10];

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	a[0][0][0] = 1;

  	for (int it = 1; it < 10; it++){
  		for (int i = 0; i < 10; i++)
  			for (int j = 0; j < 10; j++){
  				for (int i1 = 0; i1 <= i; i1++)
  					for (int j1 = 0; j1 <= j; j1++)
  						a[it][i][j] += a[it-1][i1][j1];
  				eprintf("%d%c",a[it][i][j]," \n"[j==9]);
  			}
  	     eprintf("\n");
  	}

      
  TIMESTAMP(end);
  return 0;
}