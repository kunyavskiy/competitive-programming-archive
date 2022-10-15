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

#undef assert
#define assert(Expr) if (!(Expr)) throw 1;

bool in(int t1,int s1,int t2,int s2){
//	assert(t1 != 3);
	if (t1 == 1){       
		if (t2 == 1)
			return s1 >= s2;
		if (t2 == 2)
			return s1*2 >= s2;
		if (t2 == 3)
			return s1*s1*16 >= s2*s2*3;
		assert(false);
	}

	if (t1 == 2){
		if (t2 == 1)
			return s1*s1*2 >= s2*s2*4;
		if (t2 == 2)
			return s1*s1*2 >= s2*s2;
		if (t2 == 3)
			return s1*s1*8 >= s2*s2*3;
		assert(false);
	}

	if (t1 == 3){
		if (t2 == 1)
			return s1 >= 2*s2;
		if (t2 == 2)
			return s1 >= s2;		
		if (t2 == 3)
			return s1*s1*4 >= s2*s2*3;
		assert(false);
	}
	assert(false);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int a,b;
  	cin >> a >> b;
  	int n;
  	cin >> n;
  	int ans = 0;
  	for (int i = 0; i < n; i++){
  		int c,d;
  		cin >> c >> d;
  		bool q = in(a,b,c,d);
  		ans += q;
  		cerr << ans << endl;
  	}
  		
  	cout << ans << endl;

  return 0;
}