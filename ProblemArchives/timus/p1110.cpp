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

int calc(int x,int n,int m){
	if (n == 0)
		return 1;
	if (n & 1)
		return (calc(x,n-1,m)*x) % m;
	int val = calc(x,n>>1,m);
	return (val*val)%m;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n,m,y;
	cin >> n >> m >> y;

	bool q = false;

	for (int i = 0; i < m; i++)
		if (calc(i,n,m) == y){
			if (q)
				cout <<" ";
			else
				q = true;
			cout << i;
		}
	if (!q)
		cout << -1 << endl;
  return 0;
}