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

string s;

vector<int> prev[4100];
int dp[4100];
int n;

void gen(int n){
    if (dp[n] == 1){
        cout << string(s.begin(),s.begin()+n+1);
        return;
    }
    for (int j = 0; j < prev[n].size(); j++)
       if (dp[n] == dp[prev[n][j]]+1){
            gen(prev[n][j]);
            cout <<" "<<string(s.begin()+prev[n][j]+1,s.begin()+n+1);
            return;
       }
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    getline(cin,s);
    n = s.size();

    for (int i = 0; i < n; i++){
        for (int j = 0;; j++){
            if (i - j < 0)
                break;
            if (i + j >= n)
                break;
            if (s[i-j] != s[i+j])
                break;
            prev[i+j].pb(i-j-1);
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 1;; j++){
            if (i - j+1 < 0)
                break;
            if (i + j >= n)
                break;
            if (s[i-j+1] != s[i+j])
                break;
            prev[i+j].pb(i-j);
        }
    }

    for (int i = 0; i < n; i++,dp[i] = 1<<29){
        for (int j = 0; j < prev[i].size(); j++){
            if (prev[i][j] == -1)
                dp[i] = 1;
            else
                dp[i] = min(dp[i],dp[prev[i][j]]+1);             
        }
    }

    
    cout << dp[n-1] << endl;
    gen(n-1);
    cout << endl;

    return 0;
}