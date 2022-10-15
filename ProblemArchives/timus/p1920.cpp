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

const int dx[4] = {0,1,0,-1};
const int dy[4] = {1,0,-1,0};


int ans[110][110];
int n,L;

void print(){
    printf("Overwhelming power of magic\n");
    int x = 0;
    int y = 0;
    do {
       printf("%d %d\n",x+1,y+1);
       int t = ans[x][y];
       x += dx[t];
       y += dy[t];
    } while (x || y);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d %d",&n,&L);

    if (L > n*n || L%2){
        printf("Unsuitable device\n");
        return 0;
    }

    for (int i = 0; i < n; i++)
       for (int j = 0; j < n; j++)
          ans[i][j] = ((j%2)?3:1);
       
    for (int i = 0; i < n; i++){
        if (i) ans[0][i] = 2;
        if (i % 2 == 1)
            ans[1][i] = 0;
        else
            ans[n-1][i] = 0;
    }

    if (n%2 == 0){
        ans[1][n-1] = 3;  
        for (int i = 1; i < n; i++)
            for (int j = 0; j < n; j++){
               if (j % 2 == 1)
                   continue;
               if (i == 1 && L == n*j+2*i){
                   ans[i][j] = 3;
                   print();
                   return 0;               
               }
               if (L == n*j + 2*i + 2){
                   ans[i][j] = 0;
                   ans[1][j+1] = 3;
                   print();
                   return 0;
               }
            }  
        assert(false);
    }else {
        for (int i = 1; i < n; i++)
            if ((i&1) == 0)
                ans[i][n-2] = 0, ans[i][n-1] = 3;
            else
                ans[i][n-1] = 2;
        ans[1][n-2] = 3;


        if (L <= n*(n-1)){
            for (int i = 1; i < n; i++)
                ans[i][n-2] = 3;
        }
        else {
            for (int i = 1; i < n && L < n*n-1; i++){
                ans[i][n-2] = 3;
                L++;
            }
            print();
            return 0;
        }
        


          
        for (int i = 1; i < n; i++)
            for (int j = 0; j < n; j++){
               if (j % 2 == 1)
                   continue;
               if (i == 1 && L == n*j+2*i){
                   ans[i][j] = 3;
                   print();
                   return 0;               
               }
               if (L == n*j + 2*i + 2){
                   ans[i][j] = 0;
                   ans[1][j+1] = 3;
                   print();
                   return 0;
               }
            }
    }

    print();            
    return 0;
}