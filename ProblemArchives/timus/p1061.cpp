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
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int n,k;
ll a[110000];
ll sum[110000];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d %d",&n,&k);

    if (k > n){
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n; i++){
        char c;
        scanf(" %c ",&c);
        if (c == '*')
            a[i] = (1<<30);
        else
            a[i] = c - '0';
        sum[i] = (i?sum[i-1]:0)+a[i];
    }

    for (int i = n-1; i >= k; --i)
        sum[i] -= sum[i-k];


    int id = min_element(sum+k-1,sum+n) - sum;

    if (sum[id] >= (1<<30)){
        printf("0\n");
        return 0;
    }

    printf("%d\n",id-k+2);



    return 0;
}