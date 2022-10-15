#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "F"

typedef long long ll;
typedef long double ld;

const double eps = 1e-9;

double solve(double x,double y,double l){
	if (x < eps || x > l-eps)
		return eps;
	if (y < eps || y > l-eps)
		return eps;
	if (l/3 < x && x < 2*l/3 && l/3 < y && y < 2*l/3)
		return min(min(x - l/3,2*l/3-x),min(y - l/3, 2*l/3 - y));
    while (x > l/3) x -= l/3;
    while (y > l/3) y -= l/3;
    return solve(x,y,l/3);
    	
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	while (true){
  		double l,x,y;
  		if (!(cin >> l >> x >> y))
  			break;
  		cout.precision(15);
  		cout << fixed << solve(x,y,l) << endl;
  	}

      
  return 0;
}