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

int primes[65];

ll best,ans,n;

void go(ll cur,ll cnt,int pos,int size){
//	cerr << cur <<" "<<cnt <<" "<<pos <<" "<<primes[pos] <<" "<< size << endl;
	if (cnt > ans || (cnt == ans && best > cur)){
		ans = cnt;
		best = cur;
	}

	if (size == 0)
		return;

	ll tmp = cur;

	for (int i = 1; i <= size && n/primes[pos] >= tmp; i++){
		tmp *= primes[pos];
		go(tmp,cnt*(i+1),pos+1,i);		
	}
}

bool check(int n){
	for (int i =2 ; i*i <= n; i++)
		if (n % i == 0)
			return false;
	return true;
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int cnt = 0;

  for (int i = 2; cnt < 60; i++)
  	 if (check(i)) 
  	 	primes[cnt++] = i;
  	 


  int t;
  cin >> t;

  for (; t --> 0;){
	  cin >> n;
	  best = ans = 0;
	  go(1,1,0,100);
	  cout << best <<" "<<ans<< endl;
  }



  return 0;
}