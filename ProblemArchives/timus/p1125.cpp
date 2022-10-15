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

int a[51][51];


int n,m;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d %d",&n,&m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
                char c;
                scanf(" %c",&c);
                a[i][j] = c == 'W';
            }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
                int id;
                scanf("%d",&id);
                
                if (id % 2){
                    //cerr << i <<" "<<j<<endl;                  
                    for (int i1 = 0; i1 < n; i1++)
                        for (int j1 = 0; j1 < m; j1++){
                            int d = (i1 - i) *(i1-i) + (j1-j)*(j1-j);
                            if (int(sqrt(d)) == sqrt(d))
                                a[i1][j1] ^= 1;
                        }
                
                }

            }

     for (int i = 0; i < n; i++,printf("\n"))
        for (int j = 0; j < m; j++)
            printf("%c",(char)('W'*a[i][j] + 'B' * (1-a[i][j])));
    return 0;
}