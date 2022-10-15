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

vector<pair<int,int> > v;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n;
  scanf("%d",&n);
  v.resize(n);

  for (int i = 0; i < n; i++)
  	cin >> v[i].first >> v[i].second;

  sort(v.begin(),v.end());

  multiset<int> s;

  for (int i = 0; i < n; i++)
  	s.insert(v[i].second);
  int st = -(1<<30);

  int ans = 0;

  for (int ptr = 0;; ){
  	while (ptr < n && v[ptr].first < st){
  		s.erase(s.find(v[ptr].second));
  		++ptr; 
  	}


  	if (s.size()){
  		st = (*s.begin())+1;
  		++ans;
  	}
  	else 	
  		break;
	
  }

  cout << ans << endl;

  return 0;
}