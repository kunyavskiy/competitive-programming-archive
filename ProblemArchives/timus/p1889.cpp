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


string a[1100];

set<string> used;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
  	cin >> a[i];

  vector<int> ans;

  for (int i = 1; i <= n; i++)
  	if (n % i == 0){
  		used.clear();
  		int cnt = n/i;
  		bool q = true;
  		for (int j = 0; j < n; j+= cnt){
  			string s = "";
  			for (int k = j; k < j+cnt; k++){
  				//cerr << s <<" "<<a[k] << endl;
  				if (a[k] == "unknown")
  					continue;
  				if (s == "")
  					s = a[k];
  				if (s != a[k])
  					q = false;
 			}
 			if (used.find(s) != used.end() && s != "")
 				q = false;
// 			cerr << "!"<< s << "! "<<q<< endl;
 			if (s != "");
 				used.insert(s);
  		}
	  	if (q)	
	  		ans.pb(i);
//	  	cerr<<endl;
  	}

  if (ans.size() == 0)
  	printf("Igor is wrong.\n");
  else {
    for (int i = 0; i < ans.size(); i++)
    	printf("%d%c",ans[i]," \n"[i+1 == ans.size()]);
  }
	
  return 0;
}