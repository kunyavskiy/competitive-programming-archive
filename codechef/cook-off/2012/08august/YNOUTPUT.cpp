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

vector<vector<string> > v;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int t;
    cin >> t;
    v.resize(t);

    for (int i = 0; i < t; i++){
        v[i].resize(t);
        for (int j = 0; j < t; j++)
            cin >> v[i][j];
    }

    for (int i = 0; i < t; i++){
        vector<string> T = v[i];
        for (int j = 0; j <= t; j++){
            //cerr << i <<" "<<j<< endl;     
            if (j == t){
                for (int k = 0; k < t; k++)
                    printf("%s\n",T[k].data());
                return 0;
            }
            if (T[j] != ((T == v[j])?"YES":"NO"))
                break;
        }  
    }

    for (int i = 0; i < t; i++)
        printf("NO\n");  
    return 0;
}