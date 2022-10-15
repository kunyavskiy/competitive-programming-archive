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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


int a[51][51];
int b[51][51];
int c[51][51];
int temp[51][51];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            scanf("%d",&a[i][j]),a[i][j] = !!a[i][j];
        b[i][i] = 1;
    }



    for (int it = 1; it <= n*(n+1); it++){
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++){
                temp[i][j] = 0;
                for (int k = 0; k < n && !temp[i][j]; k++)
                    temp[i][j] |= a[i][k] && b[k][j];
            }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                b[i][j] = temp[i][j];
            
        if (it >= n*(n-1)){
            for (int i = 0; i < n; i++) 
                for (int j = 0; j < n; j++)
                    c[i][j] |= b[i][j];
        }
     //   cerr << b[0][0] <<b[0][1] <<endl<<b[1][0]<<b[1][1]<<endl;
    }

   // cerr << c[0][0] <<c[0][1] <<endl<<c[1][0]<<c[1][1]<<endl;


    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!c[i][j]){
                printf("No\n");
                return 0;
            }
    printf("Yes\n");
    return 0;
}