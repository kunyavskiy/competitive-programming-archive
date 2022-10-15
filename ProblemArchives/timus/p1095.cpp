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

int cnt[10];

bool check(string s){
    int cnt = 0;
    for (int i = 0; i < s.size(); i++)
        cnt = (cnt*10+s[i]-'0')%7;
    return cnt == 0;
}


void solve(){
    string s;
    getline(cin,s);
    for (int i = 0; i < 10; i++)
        cnt[i] = 0;
    for (int j = 0; j < (int)s.size(); j++)
        cnt[s[j]-'0']++;
    cnt[1]--,cnt[2]--,cnt[3]--,cnt[4]--;
    s = "";
    for (int i = 1; i < 10; i++)
        for (int j = 0; j < cnt[i]; j++)
            s+=char(i+'0');
    s += "1234";

    while (!check(s))
        if (!next_permutation(s.end()-4,s.end())){
            printf("0\n");
            return;
        }
    for (int j = 0; j < cnt[0]; j++)
        s += "0";
    cout << s << endl;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    string s;
    getline(cin,s);
    int t;
    sscanf(s.data(),"%d",&t);
    for (; t --> 0;)
        solve();

    return 0;
}