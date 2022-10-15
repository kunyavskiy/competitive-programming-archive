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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


string can[16][3];
int need[16];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
  	cin >> can[i][0] >> can[i][1] >> can[i][2];

  for (int i = 0; i < n; i++)
  	cin >> need[i],--need[i];


  for (int it = 0; it < 2; it++){

	  string last = ""; 
	  last += char(1);
 
	  for (int i = 0; i < n; i++){
  		int id = need[i];
	  	sort(can[id],can[id]+3);
  		for (int j = 0; j <= 4; j++){
  			if (j == 4){
	  			printf("IMPOSSIBLE\n");
	  			assert(!it);
  				return 0;
	  		}
  			if (can[id][j] > last){
  				if (it)
  					cout << can[id][j] << endl;
	  			last = can[id][j];
	  			break;
	  		} 		
  		}
	  }
  }
  return 0;
}