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

#define forn(i,n) for(int i=0;i<(n);i++)
#define ford(i,n) for(int i=(n)-1;i>=0;i--)

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long long ll;
typedef long double ld;

int a[8];

bool check(){
    for (int i=1;i<=3;i++)
        for (int j=i+1;j<=3;j++)
            if ((a[i]^a[j]^a[4])!=a[(i^j)+4])
                return false;
    return true;
}

void print(){
    for (int i=1;i<=7;i++)
        printf("%d ",a[i]);
    printf("\n");
    exit(0);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    for (int i=1;i<=7;i++)
      cin>>a[i];
    if (check())
        print();
    for (int i=1;i<=7;i++){
        a[i]^=1;
        if (check()) print();
        a[i]^=1;
    }
    assert(false);
    return 0;
}