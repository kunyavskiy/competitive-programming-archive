#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "C"

typedef long long ll;
typedef long double ld;

const int MOD = 1000000007;

int pow(int a,ll b){
	if (!b) return 1;
	if (b & 1) return (pow(a,b-1) * 1LL * a) % MOD;
	ll temp = pow(a,b/2);
	return (temp * temp) % MOD;
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  ll n,k;

  while (cin >> n >> k){
  	if (!n && !k) break;
  	vector<ll > v(k);
  	for (int i = 0; i < k; i++){
  		cin >> v[i];
  	}
  	sort(v.begin(),v.end());           
  	reverse(v.begin(),v.end());
  	ll res = 0;
  	for (int i = 0; i < (int)v.size(); i++){
  		if (n >= v[i])
  			res += n - v[i] + 1, n = v[i] - 1, i--;
  		else if (n >= v[i]/2 && v[i] > 1){
	  		res ++;
	  		n = v[i]/2 - 1;
	  	}
  	}
  	res += n;


  	cout << pow(2,res) << endl;
  }

      
  TIMESTAMP(end);
  return 0;
}