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

ll n;

bool check(ll a){
	while (a){
		if (a  % 3 == 2)
			return false;
		a /= 3;
	}
	return true;
}

void solve(ll m,ll k){
	if (n+m > 4294967291LL)
		return;
	if (m && check(n+m)){
		cout << n+m <<" "<<m<<endl;
		exit(0);
	}
	if (k < 4294967291LL)
	solve(m,k*3);
	solve(m+k,k*3);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	cin >> n;
	solve(0,1);
	printf("0\n");
    return 0;
}              
