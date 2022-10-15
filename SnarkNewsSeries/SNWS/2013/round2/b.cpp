#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MOD = 1000000007;

void ADD(int& x,int y){
	if ((x += y) >= MOD) x -= MOD;
}

int c[3100][3100];

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

  	c[0][0] = 1;
  	for (int i = 0; i < 3100; i++)
  	for (int j = 0; j < 3100; j++){
  		if (i) ADD(c[i][j],c[i-1][j]);
  		if (i && j) ADD(c[i][j],c[i-1][j-1]);
  	}

  	int x1,y1,z1;
  	int x2,y2,z2;
  	cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
  	int x,y,z;
  	x = abs(x1 - x2);
  	y = abs(y1 - y2);
  	z = abs(z1 - z2);


  	ll ans = (c[x+y+z][x] * 1LL * c[y+z][z]) % MOD;

  	cout << ans << endl;


    return 0;
} 