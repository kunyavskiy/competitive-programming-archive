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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


int _val[65000];
int *val = _val + 32500;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    memset(_val,63,sizeof(_val));
    int undef = val[0];

    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        int a,b,y;
        cin >> a >> b >> y;
        for (int j = a;j < b; j++)
            val[j] = y;
    }
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        int a,b,y;
        cin >> a >> b >> y;
        for (int j = a;j < b; j++)
            val[j] = undef;
    }

    vector<int> v;
    int cnt = 0;


    for (int i = -32100; i < 32000; ){
        if (val[i] == undef)
            i++;
        else {
            cnt++;
            v.pb(i);
            int j = i;
            while (val[j] == val[i])
                j++;
            v.pb(j);
            v.pb(val[i]);
            i = j;          
        }
    }

    cout << cnt;
    for (int i = 0; i < (int)v.size(); i++)
        cout <<" "<<v[i];
    cout << endl;


    return 0;
}