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

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int h,w,n;
	cin >> h >> w >> n;
	int ans;
	int ch,cl;

	ch = ans = 0;
	cl = -1;

	ans = 1;

	for (int i = 0; i < n; i++){
		string s;
		cin >> s;
		if (cl + s.size() +1 > w){
			ch++;
			if (ch == h)
				ans++,ch = 0;
			cl = -1;
		}
		cl += s.size()+1;
	}
	cout << ans << endl;
  return 0;
}