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
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


vector<string> vals;

string s;
vector<string> cur;




int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  getline(cin ,s);
  int n;

  sscanf(s.data(),"%d",&n);

  for (int i = 0; i < n; i++){
    getline(cin,s);

    string a = string("")+s[0]+s[1]+s[3]+s[2];
    for (int i = 0; i < 4; i++){
        cur.pb(a);
        rotate(a.begin(),a.begin()+1,a.end());
    } 
    reverse(a.begin(),a.end());
    for (int i = 0; i < 4; i++){
        cur.pb(a);
        rotate(a.begin(),a.begin()+1,a.end());
    } 

    a = string("")+s[0]+s[4]+s[3]+s[5];
    for (int i = 0; i < 4; i++){
        cur.pb(a);
        rotate(a.begin(),a.begin()+1,a.end());
    } 
    reverse(a.begin(),a.end());
    for (int i = 0; i < 4; i++){
        cur.pb(a);
        rotate(a.begin(),a.begin()+1,a.end());
    }

    a = string("")+s[2]+s[4]+s[1]+s[5];
    for (int i = 0; i < 4; i++){
        cur.pb(a);
        rotate(a.begin(),a.begin()+1,a.end());
    } 
    reverse(a.begin(),a.end());
    for (int i = 0; i < 4; i++){
        cur.pb(a);
        rotate(a.begin(),a.begin()+1,a.end());
    }
    

  
    sort(cur.begin(),cur.end());
    cur.erase(unique(cur.begin(),cur.end()),cur.end());
    for (int i = 0; i < (int)cur.size(); i++)   
        vals.pb(cur[i]);
    cur.clear();
  }

  sort(vals.begin(),vals.end());
  int ans = 0;
  int cur = 0;
  for (int i = 0; i < (int)vals.size(); i++){
    if (i && vals[i] != vals[i-1])
        cur = 0;
    cur++;
    ans = max(ans,cur); 
  }

  cout << ans << endl;
  return 0;
}