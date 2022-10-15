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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  string s;
  getline(cin,s);
  sscanf(s.data(),"%d",&t);

  for (int i = 0; i < t; i++){
    getline(cin,s);
    vector<char> a(s.begin(),s.end());
    sort(a.begin(),a.end());

    getline(cin,s);


    int cnt = 0;

    for (int i = 0; i < (int)s.size(); i++)
        cnt += binary_search(a.begin(),a.end(),s[i]);

    printf("%d\n",cnt);


  }

  return 0;
}

