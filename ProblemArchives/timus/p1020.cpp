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
	ld fx,fy,lx,ly,ans;
	int n;
	cin >> n >> ans;
	cin >> lx >> ly;
	fx = lx,fy = ly;

	ans *= 2*acos(-1.0);


	for (int i = 1; i < n; i++){
		ld a,b;
		cin >> a >> b;
		ans += sqrt((a-lx)*(a-lx) + (b-ly)*(b-ly));
		lx = a;
		ly = b;
	}

	ans += sqrt((fx-lx)*(fx-lx) + (fy-ly)*(fy-ly));

	cout.precision(2);
	cout << fixed << ans << endl;
  return 0;
}