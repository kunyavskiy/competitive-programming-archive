#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "e"

const int inf = 1000000000;
const ld eps = 1e-9;

const int MOD = 1000003;

int pow(int a,int b){
	if (!b)
		return 1;
	if (b & 1)
		return (pow(a,b-1)*1LL*a)%MOD;
	int temp = pow(a,b>>1);
	return (temp*1LL*temp)%MOD;
}

int inv(int a){
	return pow(a,MOD-2);
}

int main(){
  #ifdef LOCAL
  	int START = clock();
  #endif
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  int n;
  scanf("%d",&n);

  int ans = 1;
  int cur = 1;

  for (int i = n; i > 0; i--){
  	ll temp = inv(n-i+1);
  	cur = (cur*2LL)%MOD;
  	cur = (cur *1LL* (2*n-i+1)*1LL* i)%MOD;
  	cur = (cur *1LL* temp*temp)%MOD;
  	ans = (ans + cur)%MOD;
  }

  cout << ans << endl;

  #ifdef LOCAL
  	cerr << (clock() - START)*1.0/CLOCKS_PER_SEC << endl;
  #endif
  return 0;
}

