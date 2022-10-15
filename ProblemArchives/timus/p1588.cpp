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
    #define sqrt(x) sqrt((double)x)
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int x[310];
int y[310];

int len[310];
bool used[310];
int n;

ld ans;

bool check(int i,int j,int k){
    int a = y[i] - y[j];
    int b = x[j] - x[i];
    int c = -a*x[i]-b*y[i];

    if (a*x[k]+b*y[k]+c != 0)
        return true;
    if (!(min(x[i],x[j]) <= x[k] && x[k] <= max(x[i],x[j])))
        return true;
    if (!(min(y[i],y[j]) <= y[k] && y[k] <= max(y[i],y[j])))
        return true;
    return false;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
        scanf("%d %d",&x[i],&y[i]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            bool ok = true;

            for (int k = 0; k < n; k++)
                if (i != k && j != k)
                    ok &= check(i,j,k);

            if (ok)
                ans += sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
        }
    


    cout << (int)(ans/2) <<endl;

    return 0;
}