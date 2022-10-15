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
	int last = 0;

	for (int i = 0; i < n; i++){
		int a;
		cin >> a;
		if (last + 1 < a){
			printf("%d\n",last+1);
			return 0;
		}
		last = a + last ;
	}
	cout << last+1 << endl;
  return 0;
}