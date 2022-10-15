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

int ans[550][550];


int cnt;

bool in(int Lx,int Ly,int Rx,int Ry,int x,int y){
    return Lx <= x && x < Rx && Ly <= y && y < Ry;
}

void solve(int Lx,int Ly,int Rx,int Ry,int x,int y){  
    if (Rx - Lx == 1){
        return; 
    }    

    int Mx = (Lx+Rx)/2;
    int My = (Ly+Ry)/2;

    int ccnt = ++cnt;

    if (in(Lx,Ly,Mx,My,x,y))
       solve(Lx,Ly,Mx,My,x,y);
    else
       solve(Lx,Ly,Mx,My,Mx-1,My-1), ans[Mx-1][My-1] = ccnt;

    if (in(Lx,My,Mx,Ry,x,y))
       solve(Lx,My,Mx,Ry,x,y);
    else
       solve(Lx,My,Mx,Ry,Mx-1,My), ans[Mx-1][My] = ccnt;

    if (in(Mx,My,Rx,Ry,x,y))
       solve(Mx,My,Rx,Ry,x,y);
    else
       solve(Mx,My,Rx,Ry,Mx,My), ans[Mx][My] = ccnt;

    if (in(Mx,Ly,Rx,My,x,y))
       solve(Mx,Ly,Rx,My,x,y);
    else
       solve(Mx,Ly,Rx,My,Mx,My-1), ans[Mx][My-1] = ccnt;  
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    memset(ans,0,sizeof(ans));

    int n;
    int a,b;
    cin >> n >> a >> b;

    solve(0,0,(1<<n),(1<<n),a-1,b-1);

    for (int i = 0; i < (1<<n); i++,printf("\n"))
        for (int j = 0; j < (1<<n); j++)
            printf("%2d ",ans[i][j]);

    return 0;
}