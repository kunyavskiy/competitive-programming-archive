// WHAT'S WRONG WITH YOU GUYS??? WTF IS PENTIUM 3??? PLEASE UPGRADE SERVERS! IT'S RIDICULOUS TO TEST SOLUTIONS ON 9-YEAR OLD SYSTEM!"
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
  cin >> t;

  while (t-->0){
    string s;
    cin >> s;

    int sum = 2;
    for (int i = 1; i < (int)s.size(); i++){
        sum += (s[i] - s[i-1] + 26)%26;
        sum++;    
    }


    if (sum <= 11*(int)s.size())
        cout <<"YES\n";
    else
        cout <<"NO\n";
  }

  return 0;
}