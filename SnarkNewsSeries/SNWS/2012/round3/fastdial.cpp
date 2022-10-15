#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "fastdial"

using namespace std;

typedef long long int64;
typedef long double ld;

const int x[10] = {0,3,3,3,2,2,2,1,1,1};
const int y[10] = {1,0,1,2,0,1,2,0,1,2};

ld dp[2][10];

ld dist(int a,int b){
    return sqrt((x[a] - x[b])*(x[a] - x[b]) + (y[a] - y[b])*(y[a]-y[b]));
}

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            dp[0][j]= 0;

   int last;char c;
   last = -1;

   for (;scanf(" %c ",&c)==1;){
      if (last == -1){
        last = c-'0';
        continue;   
      }

      for (int i = 0; i < 10; i++)
        dp[1][i] = 1e100;

      int cur = c-'0';

      for (int i = 0; i < 10; i++)
        dp[1][i] = min(dp[1][i],dp[0][i] + dist(cur,last));
      for (int i = 0; i < 10; i++)
        dp[1][last] = min(dp[1][last],dp[0][i] + dist(i,cur));

      last = cur;

      for (int i = 0; i < 10; i++)
        dp[0][i] = dp[1][i];        
   }

   cout.precision(15);
   cout << fixed << *min_element(dp[0],dp[0]+10) << endl;


	return 0;
} 