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


char a[210000];

int cnt[2][10];

void print(int x,int y){
    while (cnt[0][x] && cnt[1][y]){
        --cnt[0][x], --cnt[1][y];
        printf("%d",max(x,y));
    }
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  gets(a);
  sscanf(a,"%d\n",&t);
  while (t-->0){
     memset(cnt,0,sizeof(cnt));
     for (int i = 0; i < 2; i++){
        a[0] = 0;
        gets(a);
        for (int j = 0; a[j]; j++)
            cnt[i][a[j]-'0']++;
     }
     for (int i = 6; i >= 0; i--)
         if (i != 4)
             print(7,i),print(i,7);
     print(4,7), print(7,4);
     print(7,7);
     for (int i = 0; i < 4; i++)
         print(i,4),print(4,i);
     print(4,4);
     printf("\n");
  }

  return 0;
}