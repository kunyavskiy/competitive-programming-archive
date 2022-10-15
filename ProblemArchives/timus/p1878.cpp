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

int C(int a,int b){
	return min((a-b+4)%4,(b-a+4)%4);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int a,b,c,d;
	cin >> a >> b >> c >> d;
	cin >>c >> d;
	int ans = 1<<30;
	for (int i = 1; i <= 4; i++)
		ans = min(ans,C(a,i)+C(b,i)+C(c,i)+C(d,i));
	cout << ans << endl;
  return 0;
}