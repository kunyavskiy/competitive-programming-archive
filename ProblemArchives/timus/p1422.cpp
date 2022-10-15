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


int x[2100];
int y[2100];
int z[2100];

int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}

struct triple{
    int x,y,z;
    triple(int x,int y,int z):x(x),y(y),z(z){
        norm();
    }
    triple(){
    }
    void norm(){
        int g = gcd(abs(x),gcd(abs(y),abs(z)));
        if (g == 0)
            return;
        x /= g;
        y /= g;
        z /= g;
        if (x < 0 || (x == 0 && y <0) || (x == 0 && y == 0 && z < 0)){
            x *= -1;
            y *= -1;
            z *= -1;
        }
    }
    bool operator<(const triple& r) const{
        if (x != r.x) return x < r.x;
        if (y != r.y) return y < r.y;
        if (z != r.z) return z < r.z;
        return false;
    }
    bool operator==(const triple& r) const{
        return x == r.x && y == r.y && z == r.z;
    }                                           
};

triple t[2100];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n;
    scanf("%d",&n);
    int ans = 0;

    for (int i = 0; i < n; i++)
        scanf("%d %d %d",&x[i],&y[i],&z[i]);
    
    int ptr = n-1;

    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++)
            t[j-i-1] = triple(x[i] - x[j], y[i] - y[j], z[i] - z[j]);
        sort(t,t+ptr);
        int cnt = 0;
        int mcnt = 0;
        for (int j = 0; j < ptr; j++){
                if (j && t[j] == t[j-1])
                    cnt++;
                else
                    cnt = 1;
                mcnt = max(mcnt,cnt);
            }

         ans = max(ans, mcnt+1);


        --ptr;
    }


    printf("%d\n",ans);

    return 0;
}