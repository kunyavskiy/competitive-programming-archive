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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

bool prime[110000];

int a[5];
int ans;

void go(int x,int y,int n){
    //cerr << x <<" "<<y<<" "<< a[0] <<" "<<a[1] <<" "<<a[2]<<endl;
    if (x == n){
        ans++;
        return;
    }
    if (y == n){
        if (prime[a[x]])
            go(x+1,x+1,n);
        return;
    }

    for (int i = 0; i < 10; i++){
        a[x] = 10*a[x] + i;
        if (x != y)
            a[y] = 10*a[y] + i;
        go(x,y+1,n);
        a[x] /= 10;
        if (x != y)
            a[y] /= 10;
    }
}

int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    memset(prime,1,sizeof(prime));

    prime[0] = prime[1] = false;

    for (int i = 2; i < 100000; i++){
        if (prime[i])
            for (int j = i; i*1LL*j < 100000; j++)
                prime[i*j] = false;
    }

    int t;
    scanf("%d",&t);

    while (t --> 0){
        ans = 0;
        string b;
        cin >> b;
        int n = 0;

        while (n < (int)b.size()){
            a[0] = 10*a[0]+b[n]-'0';
            a[n] = b[n]-'0';
            n++;
        }


        go(0,n,n);
        
        cout << ans << endl;

    }

  return 0;
}

