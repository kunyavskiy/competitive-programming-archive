#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <bitset>
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

int n;
bitset<30000> mask;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n;
  scanf("%d",&n);
  for (int i = 0; i< n; i++){
  	char c;
  	scanf(" %c",&c);
  	mask[i] = (c == '>');
  }

  int ans = 0;

  while (true){

/*  	  cout <<"!"<<endl;
  	  for (int i = 0; i < n; i++)
  	  	cout << mask[i];
  	  cout << endl;	*/

  	  bitset<30000> temp = mask & ((~mask)>>1);
      temp[n-1] = 0;
  	  ans += temp.count();
  	  if (!temp.count())
  	  	break;
                           
      temp ^= (temp<<1);

  	  /*for (int i = 0; i < n; i++)
  	  	cout << temp[i];
  	  cout << endl;*/

  	  mask ^= temp;             
  }

  cout << ans << endl;

  return 0;
}