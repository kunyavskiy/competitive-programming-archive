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
	int l = 2,r = 10;

	cin >> n;

	for (int i = 0; i < n; i++){
		int a;string s;
		cin >> a >> s;
		if (s == "hungry")
			l = max(l,a);
		else
			r = min(r,a);
	}

	if (l < r)
		cout << r << endl;
	else
		cout << "Inconsistent" << endl;  return 0;
}