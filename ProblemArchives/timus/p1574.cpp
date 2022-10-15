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

string s;

const int MAXN = 111000;

int sp[MAXN],ss[MAXN],mp[MAXN],ms[MAXN];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    getline(cin,s);
    int n = s.size();

    for (int i = 0; i < n; i++){
        sp[i] = (i?sp[i-1]:0)+2*(s[i] == '(')-1;
        mp[i] = min((i?mp[i-1]:0),sp[i]);
    }

    for (int i = n-1; i >= 0; i--){
        ss[i] = ((i < n-1)?ss[i+1]:0)+2*(s[i] == '(')-1;
        ms[i] = min(0,((i < (n-1))?ms[i+1]:0)+2*(s[i] == '(')-1);
    }

    int ans = 0;

    if (sp[n-1] != 0){
        printf("0\n");
        return 0;
    }
    ans += sp[n-1] == 0 && mp[n-1] == 0;


    for (int i = 1; i < n; i++){
//        cerr << ss[i] <<" "<<mp[i-1] <<" "<<ss[i]+mp[i-1] <<" "<<ms[i] << endl;
        ans += (ss[i] + mp[i-1]) == 0 && (ms[i] == 0);
    }
    
    cout << ans << endl;

    return 0;
}