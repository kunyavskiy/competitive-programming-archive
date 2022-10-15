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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int ans[100][10];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  	for (int i = 1; i <= 9; i++)
  		ans[i][0] = 1;


  	for (int i = 0; i < 8; i++)
	  	for (int j = 90; j >= 0; --j)
  			for (int k = 9; k >= 0; --k)
  				ans[j+k][i+1] += ans[j][i];

    int n;
    cin >> n;

    int res = 0;
 	for (int i = 0; i < 9; i++)
 		res += ans[n][i];

 	if (n == 1)
 		res++;

 	cout << res << endl;	

  return 0;
}