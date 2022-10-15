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

string s;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  cin >> s;
  string add = "";
  add+=s[0];
  int n = s.size();

  for (int i = 1; i < n; i++){
  	bool ok = true;

  	for (int l = i,r = n-1; l < r; l++,r--)
  		if (s[l] != s[r]){
  			ok = false;
  			break;
  		}

  	if (ok)
  		break;
	add+=s[i];
  }

  reverse(add.begin(),add.end());

  cout << s+add << endl;
  return 0;
}