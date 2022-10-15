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

const int MAXN = 65536;

int p[MAXN];
vector<int> primes;


int pow(int a,int b,int mod){
    int res = 1;
    while (b){
        if (b&1)
            res = (res *1LL* a) % mod;
        a = (a*1LL*a)% mod;
        b >>=1;
    }
    return res;
}


bool check(int val,int n,vector<int>& tc){
    assert(val);
    for (int i = 0; i < tc.size(); i++){
       if (pow(val,tc[i],n) == 1)
            return false;
    }
    return true;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    for (int i = 2; i <MAXN; i++){
        if (p[i] == 0){
            p[i] = i;
            primes.pb(i);
        }
        for (int j = 0; j < primes.size() && primes[j] <= p[i] && i*primes[j] < MAXN; j++)
            p[i*primes[j]] = primes[j];
    }


    int t;
    scanf("%d",&t);

    for (;t--;){
        int n;
        scanf("%d",&n);
        if (n == 2){
            printf("1\n");
            continue;
        }
        if (n == 3){
            printf("2\n");
            continue;
        }
        vector<int> tocheck;
        for (int n1 = n-1; n1 != 1; n1 /= p[n1])
            tocheck.pb((n-1)/p[n1]);
        sort(tocheck.begin(),tocheck.end());
        tocheck.erase(unique(tocheck.begin(),tocheck.end()),tocheck.end());

/*        for (int i = 0; i < tocheck.size(); i++)
            cerr << tocheck[i] <<" ";
        cerr << endl;*/

        int i;
        for (i = n-1; i >= 0 && !check(i,n,tocheck); i--);
        printf("%d\n",i);
    }

    return 0;
}