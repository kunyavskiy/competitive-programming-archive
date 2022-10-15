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

int a[250][250];
int b[250][250];
int res[250];
int n;


void xorit(int* a,int* b){
    for (int i = 0; i < n; i++)
        a[i] ^= b[i];
}

void swapit(int* a,int* b){
    for (int i = 0; i < n; i++)
        swap(a[i],b[i]);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

   scanf("%d",&n);

   for (int i = 0; i < n; i++){
     int t;

     for (scanf("%d",&t); t != -1; scanf("%d",&t))
        a[i][t-1] = 1;

     b[i][i] = true;
   }

   for (int i = 0; i < n; i++){
       for (int j = i+1; j < n; j++)
           if (a[j][i]){
             swapit(a[i],a[j]);
             swapit(b[i],b[j]);
             break;
           }

       assert(a[i][i]);

       for (int j = 0; j < n; j++)
         if (j != i && a[j][i])
            xorit(a[j],a[i]),xorit(b[j],b[i]);   
   }

   for (int i = 0; i < n; i++)
     xorit(res,b[i]);

   for (int i = 0; i < n; i++)
    if (res[i])
        printf("%d ",i+1);

    return 0;
}