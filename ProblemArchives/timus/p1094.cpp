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

char ans[100];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  memset(ans,' ',sizeof(ans));
  ans[80] = 0;

  int ptr = 0;

  char c;

  while ((c = getc(stdin)) != EOF){
  	if (c == 10 || c == 13)
  		continue;
  	if (c == '<')
  		ptr--;
  	else if (c == '>')
  		ptr++;
  	else
  		ans[ptr] = c,ptr++;
  	if (ptr < 0 || ptr == 80)
  		ptr = 0;
  }

  cout << ans << endl;
	
  return 0;
}