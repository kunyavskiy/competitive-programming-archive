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

set<pair<int,int>,greater<pair<int,int> > > s;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int k;
  scanf("%d",&k);
  for (int i = 0; i < k; i++){
  	int a;
  	scanf("%d",&a);
  	s.insert(mp(a,i+1));
  }

  int last = 0;

  while (s.size()){
  	if (s.begin()->second != last || s.size()==1){
  		cout << s.begin()->second<<" ";
  		if (s.begin()->first != 1)
			s.insert(mp(s.begin()->first-1,s.begin()->second));
		last = s.begin()->second;
		s.erase(s.begin());
  	}
  	else {
  		pair<int,int> temp = *s.begin();
  		s.erase(s.begin());
  		cout << s.begin()->second<<" ";
  		if (s.begin()->first != 1)
			s.insert(mp(s.begin()->first-1,s.begin()->second));
		last = s.begin()->second;
		s.erase(s.begin());
		s.insert(temp);

  	}
  }

  return 0;
}