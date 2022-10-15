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
	bool sb = true, cb = true;

	char c;
	int cnt  = 0;
	while ((c = getc(stdin)) != EOF){
		if ('a' <= c && c <='z'){
			if (sb)
				cnt++;
			sb = cb = false;
			continue;	
		}

		if ('A' <= c && c <='Z'){
			if (!cb)
				cnt++;
			sb = cb = false;	
			continue;
		}

		if (c == '.' || c == '!' || c == '?')
			sb = cb = true;
		else
			cb = true;
	}

	cout << cnt << endl;
  return 0;
}