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

typedef unsigned long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "i"

const int inf = 1000000000;
const ll LINF = 1LL<<50;
const ld eps = 1e-9;


vector<ll> v;
ll p,n,k;

ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}


ll mult(ll a,ll b){
	if (b == 0 || a <= LINF/b)
		return (a*b)%p;
	return ((4ULL*mult(a/2ULL,b/2ULL))%p + (2ULL*(a/2ULL)*(b%2ULL))%p + (2ULL*(a%2ULL)*(b/2ULL))%p+((a%2ULL)*(b%2ULL)))%p;
}

ll pow(ll a,ll b){
	if (!b)
		return 1%p;
	if (b & 1)
		return mult(pow(a,b-1),a);
	ll temp = pow(a,b>>1);
	return mult(temp,temp);
}

void mult(ll a){
//	cerr <<"MULT "<<a<<endl;
	v.pb(a);
}

void divide(ll b){
//	cerr <<"DIV "<<b<<endl;
	for (int i = 0; i < (int)v.size() && b != 1; i++){
//	    cerr << v[i] <<"*";
		ll g = gcd(b,v[i]);
		v[i] /= g;
		b /= g;
	}
//	cerr << endl;
	assert(b == 1);
}


ll get(){
	ll ans = 1;
	for (int i = 0; i < (int)v.size(); i++)
		ans = mult(ans,v[i]);
	return ans%p;
}


int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  cin >> n >> k >> p;

  assert(k <= n);
  cerr << pow(2ULL,69ULL) << endl;


  for (ll i = 0; i <= k; i++){
  	  if (i){
	  	  mult(n-i+1);
  		  divide(i);
  	  }
  	  cout << mult(pow(2,n-i),get())%p << " \n"[i==k];
  } 
  return 0;
}

