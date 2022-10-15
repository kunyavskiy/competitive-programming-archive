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

int n,m,k;

int cnt[255];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d %d %d",&n,&m,&k);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            char c;
            scanf(" %c ",&c);
            cnt[c]++;
        }

    for (char c; scanf(" %c ",&c) == 1; )
        cnt[c]--;

    for (int i = 0; i < 255; i++)
        for (int j = 0; j < cnt[i]; j++)
            printf("%c",char(i));
            



    return 0;
}