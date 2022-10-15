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
#include <bitset>
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

bitset<100010> b[110]; 
int a[110];
vector<int> res;

void gen(int x,int y){
    if (x == 0)
        return;
    if (a[x-1] <= y && b[x-1][y - a[x-1]] && b[x-1][y]){
        printf("-1\n");
        exit(0);
    }
    if (b[x-1][y])
        res.pb(x-1),gen(x-1,y);
    else
        gen(x-1, y - a[x-1]);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    b[0][0] = 1;

    int need, n;
    scanf("%d %d",&need,&n);


    for (int i = 0; i < n; i++){
        scanf("%d",&a[i]);
        b[i+1] = b[i] | (b[i] << a[i]); 
    }

    if (b[n][need] == 0){
        printf("0\n");
        return 0;
    }

    gen(n,need);
    sort(res.begin(),res.end());
    for (int i = 0; i < (int)res.size(); i++)
        cout << res[i]+1 << " ";

    return 0;
}