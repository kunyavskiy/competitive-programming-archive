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


int a[7][7];
int b[7];

char s[1000010];
int x[7];

void last(int from,int cnt){   
   // cout << from <<" "<< cnt << endl;
   // cout.flush();
    for (int i = from-1; i >= from-cnt; i--)
        s[i] = 'b';
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    
    a[0][0] = 1;
    a[1][1] = a[1][2] = 1;
    a[2][3] = a[2][4] = a[2][5] = a[2][6] = 1;
    a[3][0] = a[3][1] = 1, a[3][2] = -1;
    a[4][0] = a[4][3] = a[4][4] = 1, a[4][5] = a[4][6] = -1;
    a[5][1] = a[5][2] = a[5][3] = a[5][5] = 1, a[5][4] = a[5][6] = -1;

    for (int i = 0; i < 6; i++)
        cin >> b[i];


    for (int i = 0; i < 6; i++){

        if (a[i][i] == 0){
            for (int j = i; j < 6; j++)
                if (a[j][i] != 0){
                    for (int k = 0; k < 7; k++)
                        swap(a[i][k],a[j][k]);
                   swap(b[i],b[j]);
                   break;
                }         
        }

        if (a[i][i] < 0){
            for (int j = 0; j < 7; j++)
                a[i][j] *= -1;
            b[i] *= -1;
        }
        if (a[i][i] == 2){
            #ifdef LOCAL
                for (int j = 0; j < 7; j++)
                    assert(a[i][j] %2 == 0);
            #endif
            for (int j = 0; j < 7; j++)
                a[i][j] /= 2;
            if (b[i] % 2 != 0){
                printf("-1\n");
                return 0;
            }
            b[i] /= 2;
        }

        #ifdef LOCAL
            assert(a[i][i] == 1);
        #endif

        for (int j = 0; j < 6; j++){
            if (i == j)
                continue;                                         
            int coef = a[j][i];
            for (int k = 0; k < 7; k++)
                a[j][k] -= a[i][k] * coef;
            b[j] -= b[i] * coef;
        }
                
              
    }

    /*for (int i = 0; i < 6; cerr <<"="<<b[i] <<endl,i++)
        for (int j = 0; j < 7; j++)
            cerr << a[i][j] <<" ";  */

    for (int i = 0; i < 3; i++){
        x[i] = b[i];
        if (x[i] < 0){
            printf("-1\n");
            return 0;
        }
    }
    if (x[2] > x[0]){
        printf("-1\n");
        return 0;
    }

    int l = 0;
    int r = (1<<30);
    l = max(l,-b[3]);
    r = min(r, b[4]);
    r = min(r, b[5]);

    l = max(l, b[4] - b[1]);
    l = max(l, b[2] - b[0]);

    if (l > r){
        printf("-1\n");
        return 0;
    }

    x[6] = l;
    for (int i = 3; i < 6; i++)
        x[i] = b[i] - a[i][6] * x[6];
    
    //cerr<<"!!!"<<endl;
    //for (int i = 0; i < 7; i++)
    //    cerr << i<<" "<<x[i] << endl;

    /*for (int i = 0; i < 7; i++)
        assert(x[i] >= 0);
    assert(x[6] <= x[2]);
    assert(x[5] <= x[0] - x[2]);
    assert(x[4] <= x[1]);
    assert(x[2] <= x[0]); */

         
    int ans = x[0]+x[1]+x[3];
    cout << ans << endl;
    memset(s,'a',sizeof(char)*ans);
    puts(s);
    last(ans,x[0]);
    puts(s);    
    memset(s,'a',sizeof(char)*ans);
    last(ans,x[2]);
    last(ans-x[0],x[1]);
    puts(s);
    memset(s,'a',sizeof(char)*ans);
    last(ans,x[6]);
    last(ans-x[2],x[5]);
    last(ans-x[0],x[4]);
    last(ans-x[0]-x[1],x[3]);
    puts(s);

    //cerr << x[3]+x[4]+x[5]+x[6] << endl;
    
    return 0;
}