// WHAT'S WRONG WITH YOU GUYS??? WTF IS PENTIUM 3??? PLEASE UPGRADE SERVERS! IT'S RIDICULOUS TO TEST SOLUTIONS ON 9-YEAR OLD SYSTEM!"
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

#ifdef LOCAL
    ld START = clock();
#endif


bool dp[35][1100];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    dp[0][0] = 1;
    for (int i = 0; i <= 30; i++)
        for (int j = 0; j <= 1000; j++){
           if (!dp[i][j])
              continue;
           //cerr << j << " ";

           for (int k = 0; i+k+1 <= 30; k++)
              for (int l = 0; j+l+i+k+2 <= 1000; l++)
                if (dp[k][l])
                    dp[i+k+1][j+l+i+k+2] = true;              
        }
    
    int t;
    scanf("%d",&t);

    for (int i = 0; i < t; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        for (int j = b; j >= -1; j--){

            if (j == -1){
               printf("%d\n",j); 
            }
            else if (dp[a][j]){
                printf("%d\n",b-j);
                break;
            }
        }
    }


    #ifdef LOCAL
        cerr << (clock() - START)/ CLOCKS_PER_SEC << endl;
    #endif


  return 0;
}