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

char _s[1100000];
int s[1100000];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  gets(_s);
  int n;
  for (n=0;_s[n];n++)
  	if ('0' <= _s[n] && _s[n] <= '9')
  		s[n] = _s[n]-'0';
  	else
  		s[n] = _s[n]-'A'+10;

  int x = *max_element(s,s+n); 
  if (x < 1)
  	x = 1;

  for (int i = x+1; i <= 36; i++){
  	int c = 0;
  	for (int j = 0; j <= n-1; j++)
  		c = (c*i + s[j])%(i-1);
  	if (c == 0){
  		cout << i << endl;
  		return 0;
  	}
  }

  printf("No solution.\n");
  return 0;
}