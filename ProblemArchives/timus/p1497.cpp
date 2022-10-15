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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


int n;

char c[1000][1000];
char c2[1000][1000];

void rotate(){
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c2[j][n-i-1] = c[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = c2[i][j];
}

bool check(){
    for (int i = 1; i < n; i++)
        for (int j = 1; j < n; j++)
            if (c[i][j] == '0' && c[i-1][j] == '1')
                return 0;
    return 1;
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf(" %c",&c[i][j]);

    for (int i = 0; i < 4; i++){
        if (check()){
            printf("Yes\n");
            return 0;
        }
        rotate();
    }
    printf("No\n");
  return 0;
}