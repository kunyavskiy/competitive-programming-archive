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

#define taskname "a"

const int inf = 1000000000;
const ld eps = 1e-9;

/*int dp[1100];


bool check(int x,int k){
	if (x > k)
		return 1;
	if (x == k)
		return 0;
	if (dp[x] != -1)
		return dp[x];
	return dp[x] = !check(x+1,k) || !check(2*x,k);
}*/

ll calc(ll val){
	if (val == -1)
		return 0;
	ll ans = 0;
	for (int i = 61; i >= 0; i--){
	    if (val&(1ll<<i))
	      ans+=(1ll<<(i/2));
		if ((!(i & 1)) && (val & (1ll<<i))){
			break;
		}

	}
	return ans;
}

int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  /*for (int i = 1; i < 1000; i++){
  	memset(dp,-1,sizeof(dp));
  	if (check(1,i))
	  	cout << i<<endl;
  }*/

  ll l,r;
  cin >> l >> r;
  //cerr<<calc(r+1)<<" "<<calc(l)<<endl;
  cout << (r-l+1) - (calc(r+1ll) - calc(l)) << endl;
  return 0;
}



