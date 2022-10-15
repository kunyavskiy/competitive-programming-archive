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
    #define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

map<pair<int,pair<ll,ll> >,ll> res;


ll getll(){
	string s;
	cin >> s;
	ll res = 0;
	for (int i = 0; i < (int)s.size(); i++)
		res += (s[i] - '0') * (1LL<<i);
	return res;
}

ll solve(int len,ll from,ll to){
	if (res.find(mp(len,mp(from,to))) != res.end())
		return res[mp(len,mp(from,to))];
	ll& ans = res[mp(len,mp(from,to))];
	if (from == to)
		return ans = 0;
	if (len == 0)
		return ans = 1;
	if ((from & (1LL<<len)) == (to & (1LL<<len)))
		return ans = solve(len-1,from & ~(1LL<<len),to & ~(1LL<<len));
	return ans = 1 + solve(len-1,from & ~(1LL<<len),(1LL<<(len-1))) + solve(len-1,(1LL<<(len-1)),to & ~(1LL<<len));
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	
  int n;
  cin >> n;
  ll from = getll();
  ll to = getll();
  cout << solve(n,from,to) << endl;

  return 0;  
}