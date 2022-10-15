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

int main(){
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n;
  	cin >> n;
  	for (int it = 0; it < n; it++){
  		int x,y;
  		char c1,c2;
  		cin >> c1 >> c2;
  		x = c1-'a';
  		y = c2-'1';
  		int ans = 0;

  		for (int i = -2; i <= 2; i++)
  			for (int j = -2; j <= 2; j++)
  				if (abs(i)+abs(j) == 3 && x+i>= 0 && x+i < 8 && y+j >= 0 && y+j < 8)
  					ans++;

  		cout << ans << endl;
  	}

	
  return 0;
}