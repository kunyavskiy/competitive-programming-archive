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

char buf[100];
int x,y;
                       
int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  
  int t;
  scanf("%d",&t);

  for (;t --> 0;){

	  int S = scanf(" The Machinegunners played %s game, scored %d goals, and conceded %d goals.",buf,&x,&y);
	  assert( S == 3);
	  if (buf[0] == 'h'){
	  	int minv,maxv;
	  	minv = 100,maxv = -1;
	  	for (int i = 0; i <= 30; i++)
	  		for (int j = 0; j<= 30; j++){
	  			if (x+i > y + j || (x+i == y+j && i >= y))
	  				minv = min(minv,i);
	  			if (x+i < y + j || (x+i == y+j && i <= y))
	  				maxv = max(minv,i); 			
	  		}
	  	cout << minv <<" "<<maxv << endl;
	  }
	  else {
	  	int minv,maxv;
	  	minv = 100,maxv = -1;
	  	for (int i = 0; i <= 30; i++)
	  		for (int j = 0; j<= 30; j++){
	  			if (x+i > y + j || (x+i == y+j && x >= j))
	  				minv = min(minv,i);
	  			if (x+i < y + j || (x+i == y+j && x <= j))
	  				maxv = max(minv,i); 			
	  		}
	  	cout << minv <<" "<<maxv << endl;
	  }

  }


  return 0;
}