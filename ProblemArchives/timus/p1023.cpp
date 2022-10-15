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

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n;
	cin >> n;
	if (n <= 2)
		cout << 0 << endl;
	else {                
		for (int i = 3; i*i <= n; i++)
			if (n % i == 0) {
				cout << i-1 << endl;
				return 0;
			}
		if (n % 2 == 0 && n/2 > 2)
			cout << n/2 - 1 << endl;
		else
			cout << n-1 << endl;
	}
	  
	return 0;
}