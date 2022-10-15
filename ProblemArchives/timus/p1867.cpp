#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <queue>
#include <string>
#include <ctime>
#include <stack>

#define sqr(x) ((x)*(x))
#define sz(a) (int)a.size()
#define pb push_back
#define mp make_pair
#define zero(a) memset (a, 0, sizeof(a))



#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define taskname ""

const int inf = (int)1e9;

int a[110][110];
int _a[110][110];

int ord[110];

int x[110];
int y[110];
int n;

int isqrt(int a){
    int c = (int)sqrt((double)a);
    while (c*c > a)
        --c;
    while ((c+1)*(c+1) <= a)
        ++c;
    return c;       
}

bool check(int last){
    for (int i = 0; i < last; i++)
        if ((x[i] - x[last])*1LL*(x[i] - x[last]) + (y[i] - y[last]) * 1LL* (y[i] - y[last]) != a[i][last])
            return false;
    return true;
}

int start = clock();

void go(int n){

    if (clock() - start > 0.95 * CLOCKS_PER_SEC){
      printf("Impossible");
        exit(0);
    }
        

    if (n == 0){
        x[0] = y[0] = 0;
        go(n+1);
        return;
    }

    if (n == ::n){
        int x1[110],y1[110];
        for (int i = 0; i < n; i++)
            x1[ord[i]] = x[i], y1[ord[i]] = y[i];
        for (int i = 0; i < n; i++)
            printf("%d %d\n",x1[i],y1[i]);
        exit(0);
    }

    int id = 0;
    for (int i = 0; i < n; i++)
        if (a[n][i] < a[n][id])
            id = i;



    for (int dx = isqrt(a[n][id]); dx >= 0; --dx){
        int dy = isqrt(a[n][id] - dx*dx);


        if (dy > dx)
            break;

        if (dx*dx + dy*dy != a[n][id])
            continue;      

        if (dx == 0 && dy == 0){
            x[n] = x[id];
            y[n] = y[id];
            if (check(n))
                go(n+1);
            break;
        }   


        for (int i = -1; i < 2; i+=2)
            for (int j = -1; j < 2; j+=2){
                x[n] = x[id] + i*dx;
                y[n] = y[id] + j*dy;
                if (check(n))
                    go(n+1);

                x[n] = x[id] + i*dy;
                y[n] = y[id] + j*dx;
                if (check(n))
                    go(n+1);
            }
            

    }
        
}



int main (void){
    srand(time(NULL));
#ifdef LOCAL
  freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
#endif
  scanf("%d", &n);
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      scanf("%d", &_a[i][j]);

  for (int i = 0; i < n; i++)
    ord[i] = i;

  random_shuffle(ord,ord+n);

//  cerr << ord[0] << " "<<ord[1] <<" "<<ord[2] <<endl;

  for (int i = 0; i < n; i++)
    for (int j = 0;j < n; j++)
        a[i][j] = _a[ord[i]][ord[j]];



  go(0);

  printf("Impossible");

  return 0;
  
}

