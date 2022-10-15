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


vector<int> primes;

bool used[1<<20];

void gen(){
	for (int i = 2; primes.size() < 15000; i++){
//		if (i % 1000 == 0)
//			cerr << i <<" "<<primes.size()<<" "<<i*i<< endl;
		if (!used[i]){
			primes.pb(i);
			for (ll j = i*1LL*i; j < (1<<20); j+=i)
				used[j] = true;
		}
	}
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  gen();
  int n;
  scanf("%d",&n);
  for (int i = 0; i < n; i++){
  	int k;
  	scanf("%d",&k);
  	printf("%d\n",primes[k-1]);
  }
  return 0;
}