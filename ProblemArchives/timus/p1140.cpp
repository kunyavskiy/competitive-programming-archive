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


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n;
    cin >> n;

    int dx,dy;
    dx = dy = 0;

    for (int i = 0; i < n; i++){
        char c;int x;
        cin >> c >> x;
        if (c == 'X')
            dx += x;
        else if (c == 'Y')
            dx += x, dy += x;
        else {
            assert(c == 'Z');
            dy += x;
        }
    } 
           

    int x,y,z;             
    x = y = z = 0;
    x = dx, z = dy;

    if (x > 0 && z > 0){
        int t = min(x,z);
        x -= t, z -= t, y += t;
    }
    if (x < 0 && z < 0){
        int t = max(x,z);
        x -= t, z -= t, y += t;
    }

    x = -x, y = -y, z = -z;
    int cnt = 0;
    cnt += !!x + !!y + !!z;          
    cout << cnt << endl;
    if (x) cout << "X "<<x << endl;
    if (y) cout << "Y "<<y << endl;
    if (z) cout << "Z "<<z << endl;  
    return 0;
}