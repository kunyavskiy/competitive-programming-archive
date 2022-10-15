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

const int MOD = 1000000007;

int pow(int a,int b){
    if (!b) return 1;
    if (b&1) return (pow(a,b-1)*1LL*a) % MOD;
    int temp = pow(a,b/2);
    return (temp * 1LL * temp) % MOD;
}

int inv(int a){
    return pow(a,MOD-2);
}

int a[2100][50];

pair<int,int> b[2100];

int conn[2100];

vector<int> used;          

int n,m;

bool norm(int id){
    for (int i = 0; i < m; i++)
        if (a[id][i] != 0){
            conn[id] = i;
            int temp = inv(a[id][i]);
            for (int j = 0; j < m; j++)
                a[id][j] = (a[id][j] * 1LL * temp) % MOD;
            return true;                
        }
    return false;
}

void subst(int id,int to){
    int temp = a[to][conn[id]];
    for (int i = 0; i < m; i++)
        a[to][i] = (a[to][i] - (temp * 1LL* a[id][i])%MOD + MOD) % MOD; 
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d %d",&n,&m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }

    for (int i = 0; i < n; i++)
        cin >> b[i].first, b[i].second = i;

    sort(b,b+n);

    int sum = 0;


    for (int i = 0; i < n; i++){
        for (int j = 0; j < (int)used.size(); j++)
            subst(used[j],b[i].second);

        if (norm(b[i].second)){
            used.pb(b[i].second);
            sum += b[i].first;
        }
    } 

    if ((int)used.size() < m){
       printf("0\n");
       return 0;
    }

    sort(used.begin(),used.end());
    printf("%d\n",sum);
    for (int i = 0; i < (int)used.size(); i++)
        printf("%d\n",used[i]+1);

    return 0;
}