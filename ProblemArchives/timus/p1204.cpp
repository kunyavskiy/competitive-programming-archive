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

int pow(int a,int b,int m){
	if (b == 0)
		return 1;
	if (b & 1)
		return (pow(a,b-1,m)*1LL*a)%m;
	int temp = pow(a,b>>1,m);
	return (temp*1LL*temp)%m;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int t;
  	cin >> t;
  	while (t --> 0){
		int n;
		cin >> n;
		int p,q;
		for (p=2; n%p; ++p);
		q = n/p;
		cout << "0 1 ";
		int a = p*pow(p,q-2,q);
		int b = q*pow(q,p-2,p);
		cout << min(a,b) <<" "<<max(a,b) << endl;
	}
  return 0;
}