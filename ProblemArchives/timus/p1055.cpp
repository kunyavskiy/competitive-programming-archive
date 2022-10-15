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

int p[55000];

void add(int n,int coef){
	for (int i = 2; i*i <= n; i++){
		while (n % i == 0){
			p[i]+=coef;
			n/=i;
		}
	}
	if (n -1)
		p[n] += coef;
}


void addf(int n,int coef){
	for (int i = 2; i <= n; i++)
		add(i,coef);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n,m;

  	cin >> n >> m;

  	addf(n,1);
  	addf(m,-1);
  	addf(n-m,-1);

  	int ans = 0;
  	for (int i = 0; i < 55000; i++){
//  		cerr << p[i] << " ";
  		ans += !!p[i];
  	}

  	cout << ans << endl;

  return 0;
}