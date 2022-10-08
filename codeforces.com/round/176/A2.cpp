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

#define TASKNAME "A2"

typedef long long ll;
typedef long double ld;


char c[5][5];

void YES(int a){
	if (a){
		printf("YES\n");
		exit(0);
	}
}

bool check(){
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (c[i][j] == c[i+1][j] && c[i][j] == c[i][j+1] && c[i][j] == c[i+1][j+1])
				return true;	
	 return false;
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  for (int i = 0; i < 4; i++)
  	for (int j = 0; j < 4; j++)
  		scanf(" %c",&c[i][j]);

  YES(check());
  for (int i = 0; i < 4; i++)
  	for (int j = 0; j < 4; j++){
  		c[i][j] = '.' + '#' - c[i][j];
  		YES(check());
  		c[i][j] = '.' + '#' - c[i][j];
  	}

  printf("NO\n"); 	
  TIMESTAMP(end);
  return 0;
}