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

bool check(int a){
	for (int i =2 ;i*i <= a; i++)
		if (a % i == 0)
			return false;
	return true;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  cin >> t;
  for (; t --> 0;){
  	int n;
  	cin >> n;
  	if (check(n)){
  		cout << n <<endl;
  		continue;
  	}

  	if (check(n-2)){
  		cout << 2 <<" "<<n-2 <<endl;
  		continue;
  	}

  	if (n % 2 == 1){
  		cout << 3 << " ";
  		n -= 3;
  	}

  	for (int i = 3; ; i++)
  		if (check(i) && check(n-i)){
  			cout << i <<" "<<n-i << endl;
  			break;
  		}
  		
  }
  return 0;
}