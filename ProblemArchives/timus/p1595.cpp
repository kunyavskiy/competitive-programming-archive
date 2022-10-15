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

const int MAXN = 10000000;

set<ll> s;
int n;

bool used[MAXN];

void insert(ll x){
	if (x >= MAXN) s.insert(x);
 	else used[x] = true;	
}

bool find(ll x){
	if (x >= MAXN) return s.find(x) != s.end();
	return used[x];
}

ll smod(ll a,ll b){
	return ((a%b) + b) % b;
}

void gcdex(ll a,ll b,ll& x,ll& y){
	if (b == 0){
		x = 1;
		y = 0;
		return ;
	}
	ll x1,y1;
	gcdex(b,a%b,x1,y1);
	x = y1;
	y = x1 - (a/b) * y1;
}

ll inv(ll a,ll b){
	ll x,y;
	gcdex(a,b,x,y);
	return x;
}

ll next(ll a,ll b,ll m){
	a = smod(a,m);
	b = smod(b,m+1);

	ll t = smod((b - a) * 1LL * inv(m,m+1),m+1);

	ll res = m * t + a;
	ll mod = m * (m+1);
	res = smod(res,mod);

	assert(res % m == smod(a,m));
	assert(res % (m+1) == smod(b,m+1));

	while (find(res))
		res += mod;
	return res;
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    ll sum = 0;

    cin >> n;


    int ptr = 1;
    for (int i = 1; ptr <= n && i <= 2*n; i++){
    	if ((sum + ptr) % i == 0){
    		sum += ptr;
    		assert(sum % i == 0);
    		printf("%d ",ptr);
    		insert(ptr);
	    	while (find(ptr))
    			ptr++;    
    	}
    	else {
    		ll t = next(-sum,-sum-ptr,i);
    		sum += t;
    		assert(sum % i == 0);
			printf(LLD" ",t);
    		insert(t);
    	}
                  
    }
    cout << endl;

    #ifdef LOCAL
    	cerr << clock() << endl;
    #endif
    return 0;
}