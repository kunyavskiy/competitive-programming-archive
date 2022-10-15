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

set<int> s;
string t;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif


  getline(cin,t);
  int n = t.size();

  for (int i = 1; i < 10000000; i *= 10){
  	int a = 0;
  	for (int j = 0; j < n; j++){
  		a = (a * 10 + t[j] - '0') % i;
  		s.insert(a);
  	}               
  }

  for (int i = 1; ; i++)
  	if (s.find(i) == s.end()){
  		cout << i << endl;
  		return 0;
  	}


  return 0;
}