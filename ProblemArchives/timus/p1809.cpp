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

int ans;
int bx[4];
int by[4];
int cx[4];
int cy[4];

void go(int a,int b){
    if (ans <= b)
        return;
    if (a == 4){
        for (int i = 0; i < 4; i++){
            int cnt = 0;
            for (int j = 0; j < 4; j++){
                cnt += cx[i] == cx[j];
                cnt += cy[i] == cy[j];
            }
            if (cnt != 3)
                return;
        }
        ans = b;
        memcpy(bx,cx,sizeof(int)*4);
        memcpy(by,cy,sizeof(int)*4);
        return;
    }

    go(a+1,b);

    int ox = cx[a], oy = cy[a];

    for (int i = 1; i <= 20; i++)
        for (int j = 1; j <= 20; j++){
            cx[a] = i, cy[a] = j;
            go(a+1,b+1);
        }
    cx[a] = ox, cy[a] = oy;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    for (int i = 0; i < 4; i++)
        cin >> cx[i] >> cy[i];

    ans = 3;
    
    go(0,0);

    assert(ans <= 2);
    

    for (int i = 0; i < 4; i++)
        cout << bx[i] << " "<<by[i]<<endl;

    return 0;
}