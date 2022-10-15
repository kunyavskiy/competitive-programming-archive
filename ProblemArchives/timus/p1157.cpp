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

int calc(int a){
	int ans = 0;
	for (int i = 1; i*i <= a; i++){
		ans += (a%i == 0);
		//ans += (a%i == 0 && i*i != a);
	}
	return ans;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int m,n,k;
  cin >> m >> n >> k;

  for (int i = 1; i <= 10000; i++)
  	if (calc(i)==n && calc(i-k)==m){
  		cout << i << endl;
  		return 0;
  	}
  cout << 0 << endl;
  return 0;
}