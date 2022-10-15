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

int need[4][4];

int change[4][4];

int calc(){
	for (int i = 1; i <= 4; i++)
		for (int j = 0; j < 4; j++){
				int add = need[i-1][j] ^ change[i-1][j];
				if (j)
					add ^= change[i-1][j-1];
				if (j != 3)
					add ^= change[i-1][j+1];
				if (i != 1)
					add ^= change[i-2][j];
				if (i != 4 )
					change[i][j] = add;
				else {
					if (add == 1)
						return 1<<30;	
				}
			}
	int cnt = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			cnt += change[i][j];		

	return cnt;
}

int ans;

void go(int a){
	if (a == 4){
		ans = min(ans,calc());
		return;
	}
	change[0][a] = 0;
	go(a+1);
	change[0][a] = 1;
	go(a+1);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  	for (int i = 0; i < 4; i++)
  		for (int j = 0; j < 4; j++){
  			char c;
  			cin >> c;
  			need[i][j] =  (c == 'w');
  		}


  	ans = (1<<30);

  	go(0);

  	for (int i = 0; i < 4; i++)
  		for (int j = 0; j < 4; j++)
  			need[i][j] ^= 1;

  	go(0);

  	if (ans != (1<<30))
  		cout << ans << endl;
  	else
  		cout << "Impossible" << endl;



  return 0;
}