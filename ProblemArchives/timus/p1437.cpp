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

bool dp[260][260][260];

bool can[860];


queue<int> qx;
queue<int> qy;
queue<int> qz;


void relax(int a,int b,int c){
    if (dp[a][b][c]) return;
    dp[a][b][c] = true;
    qx.push(a);
    qy.push(b);
    qz.push(c);
    can[a] = can[b] = can[c] = can[a+b] = can[a+c] = can[b+c] = can[a+b+c] =  1;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int a,b,c;
    cin >> a >> b >> c;
                  

    relax(0,0,0);

    while (!qx.empty()){
        int x = qx.front();qx.pop();
        int y = qy.front();qy.pop();
        int z = qz.front();qz.pop();

        relax(a,y,z);
        relax(x,b,z);
        relax(x,y,c);

        relax(x + min(a-x,y), y - min(a-x,y),z);
        relax(x + min(a-x,z), y,z - min(a-x,z));
        relax(x - min(x, b-y), y + min(x, b-y), z);
        relax(x - min(x, c-z), y , z + min(x, c-z));
        relax(x, y - min(y, c-z), z + min(y,c-z));
        relax(x, y + min(b-y,z), z - min(b-y,z)); 
    }

    int sum = 0;
    for (int i = 1; i < 860; i++)
        sum += can[i];

    cout << sum << endl;




    return 0;
}