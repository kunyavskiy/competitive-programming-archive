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


#undef assert
#define assert(x) if (!(x))  throw 1

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


int fi(int n){
	int res = 1;
	for (int i = 2; i*i <= n; i++){
		if (n % i == 0){
			res *= i-1;
			n /= i;
		}
		while (n % i == 0){
			res *= i;
			n /= i;
		}
	}
	if (n-1)
		res *= n-1;
	return res;
}

int pow(int a,int b,int c){
	if (b == 0)
		return 1;
	if (b & 1)
		return (pow(a,b-1,c) * a) % c;
	int temp = pow(a,b/2,c);
	return (temp * temp) % c;
}

int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int k;
	scanf("%d",&k);
	for (; k-->0;){
		int e,n,c;
		cin >> e >> n>>c;
		int f = fi(n);
		assert(f != 1);
		assert(gcd(f,e) == 1);
		int d = pow(e,fi(f)-1,f);
		assert(fi(f)*2-1 >= 0);
		assert((d * e)%f == 1); 
		cout << pow(c,d,n) << endl;
	}
  return 0;
}