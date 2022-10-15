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

int a[3][3];
int b[4][4];
int n;


int ans;

bool good(int x,int y){
    return 0 <= x && x < 4 && 0 <= y && y < 4;
}

int mask;

void go(int x,int y,int cnt){
    if (y == 4){
        go(x+1,0,cnt);
        return;
    }
    if (x == 4){
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (b[i][j] != b[0][0])
                    return;                  
        ans = min(ans,cnt);
        return; 
    }

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (a[i+1][j+1] && good(x+i,y+j))
                b[x+i][y+j] ^= 1;

                         
    go(x,y+1,cnt+1);

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (a[i+1][j+1] && good(x+i,y+j))
                b[x+i][y+j] ^= 1;

                          
    go(x,y+1,cnt);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++){
            char c;
            scanf(" %c",&c);
            b[i][j] = (c == 'W');
        }


    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++){
            char c;
            scanf(" %c",&c);
            a[i][j] = (c == '1');
        }

    ans = 17;

    go(0,0,0);

    if (ans == 17)
        printf("Impossible\n");
    else
        printf("%d\n",ans);

    return 0;
}