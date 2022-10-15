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

vector<int> v[2][2];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

     int n;
     scanf("%d",&n);

     for (int i = 0; i < 5*n; i++){
        int x,y;
        scanf("%d %d",&x,&y);
        v[abs(x)%2][abs(y)%2].pb(i+1);
     }

     printf("OK\n");
     for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if ((int)v[i][j].size() >= n){
                for (int k = 0; k < n; k++)
                    printf("%d ",v[i][j][k]);
                return 0;
            }

    return 0;
}