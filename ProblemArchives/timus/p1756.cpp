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
	int m,d1,d2;
	cin >> m >> d1 >> d2;

	int cnt = (m*d1)/d2 + !!((m*d1)%d2);

	int cnt2 = m*d1;

	for (int i = 0; i < d2; i++){
		cout << min(cnt,cnt2) << " \n"[i==d2-1];
		cnt2 -= min(cnt,cnt2);
	}

  return 0;
}