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


ll s[110000];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    cin >> n;
    for (int i = 0; i <= n; i++){
    	int a,b,c;
    	cin >>a >>b>>c;
    	s[a-1] += c;
    	s[b] -= c;
    }

    for (int i = 1; i < n; i++)
    	s[i] += s[i-1];

    for (int i = 0; i < n; i++)
    	cout << s[i] <<" \n"[i == n-1];

  return 0;
}