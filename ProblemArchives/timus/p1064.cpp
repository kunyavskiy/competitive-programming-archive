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
	#define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 110000;

bool ok[MAXN];

bool check(int n,int id,int cnt){

  int p, q, i, L;

  p = 0;   
  q = n-1; 
  L = 0;   
  if (id > q)
    return false;
  while (p <= q) {
    i = (p + q) / 2;
    ++L;
    if (i == id) 
      return L == cnt;    
    if (id < i)
      q = i - 1;
    else
      p = i + 1;
  }    
  assert(false);
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int id,cnt;
    cin >> id >> cnt;


    for (int i = 1; i <= 10000; i++)
        ok[i] = check(i,id,cnt);

    int start = -1;

    vector<pair<int,int> > ans;

    for (int j = 1; j <= 10001; j++){
        if (ok[j]){
            if (start == -1)
                start = j;
        }
        else {
            if (start != -1){
                ans.pb(mp(start,j-1));
                start = -1;
            }
        }
    }

    cout << ans.size() << endl;

    for (int i = 0; i < ans.size(); i++)
        cout << ans[i].first <<" "<<ans[i].second << endl;

    return 0;
}