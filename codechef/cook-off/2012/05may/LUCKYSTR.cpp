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


string a[55];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n,k;
  cin >> n;
  cin >> k;
  for (int i = 0; i < n; i++)
     cin >> a[i];
  

  for (int i = 0; i < k; i++){
    string b;
    cin >> b;
    bool good = false;
    if (b.length() >= 47)
        good = true;

    for (int j = 0; j < n && !good; j++)
        if (b.find(a[j]) != string::npos)
            good = true;

    if (good){
        printf("Good\n");
    }
    else {
        printf("Bad\n");
    }
  }

  return 0;
}