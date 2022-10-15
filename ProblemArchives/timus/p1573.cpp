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
	int a,b,c;
	cin >> a >> b>> c;
	int k;
	cin >> k;
	int ans = 1;
	for (int i = 0; i < k; i++){
		string s;
		cin >> s;
		if (s[0] == 'B')
			ans *= a;
		else if (s[0] == 'R')
			ans *= b;
		else
			ans *= c;
	}

	cout << ans << endl;
  return 0;
}