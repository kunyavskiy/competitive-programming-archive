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

const int MAXN = 1000010;

int p[MAXN];
ll s[MAXN];
int d[MAXN];
vector<int> primes;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	p[0] = p[1] = 0;
	s[0] = s[1] = 1;
	d[0] = d[1] = 1;

	for (int i = 2; i < MAXN; i++){
		if (p[i] == 0){
			p[i] = i;
			primes.pb(i);
		}

		for (int j = 0; j < primes.size() && primes[j] <= p[i] && i*1LL*primes[j] < MAXN;j++)
			p[i*primes[j]] = primes[j];		
	}



	for (int i = 2; i < MAXN; i++){
		if (p[i] == p[i/p[i]])
			d[i] = d[i/p[i]];
		else
			d[i] = i/p[i];
//		assert(((s[i/p[i]] * (p[i]-1) + s[d[i]])*p[i] - s[d[i]])%(p[i]-1) == 0);
		s[i] = ((s[i/p[i]] * (p[i]-1) + s[d[i]])*p[i] - s[d[i]])/(p[i]-1);
	}

//	return 0;

	int l,r;
	cin >> l >> r;
	int b = l;

	for (int j = l+1; j <= r; j++)
		if (s[j]*1LL*b < s[b]*1LL*j)
			b = j;

    cout << b << endl;
  return 0;
}