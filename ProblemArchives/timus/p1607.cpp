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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int a,b,c,d;
	cin >> a >> c >> b >> d;

	if (a >= b){
		cout << a << endl;
		return 0;
	}

	for (;;){
		if (a + c >= b){
			cout << b << endl;
			break;
		}
		a += c;
		if (b - d <= a){
			cout << a << endl;
			break;
		}
		b -= d;
	}
  return 0;
}