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


ld A[1100];
ld B[1100];
int n;

bool check(ld last){
	ld x = (last - B[n-1])/A[n-1];
	for (int i = 0; i < n; i++)
		if (A[i]*x + B[i] < 0)
			return false;
	return true;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	cin >> n;
  	A[0] = 0; cin >> B[0];
  	A[1] = 1; B[1] = 0;

  	for (int i = 2 ; i < n; i++){
  		A[i] = 2*A[i-1] - A[i-2];
  		B[i] = 2*B[i-1] - B[i-2] + 2;
  	}

  	ld l = 0;
  	ld r = 1e20;

  	for (int i = 0; i < 500; i++){
  		ld mid = (l+r)/2;

  		if (check(mid))
  			r = mid;
  		else
  			l = mid;
  	}


  	cout.precision(15);
  	cout <<fixed << (l+r)/2 << endl;


  return 0;
}