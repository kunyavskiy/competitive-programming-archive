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
#include <sstream>

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

const string name[5] = {"trochee","iamb","dactyl","amphibrach","anapaest"};
const string mask[5] = {"101010","010101","100100","010010","001001"};

bool ok[6];

int main (void){
#ifdef LOCAL
  freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
#endif

    string s;
    getline(cin,s);
    int n;
    sscanf(s.data(),"%d",&n);

    memset(ok,1,sizeof(ok));

    for (int i = 0; i < n; i++){
        getline(cin,s);
        for (int i = 0; i < (int)s.size(); i++)
            if (s[i] == '-')
                s[i] = ' ';
        stringstream str(s);
        string t;
        for (int i = 0; str >> t; i++){
            for (int j = 0; j < 5; j++){
                if (int(mask[j][i%6] -'0') == 1)
                    ok[j] &= (t[0] == '[');
                else
                    ok[j] &= (t[0] != '[');
            }       
        }
    }

    for (int i = 0;i < 5; i++)
        if (ok[i]){
            cout << name[i] << endl;
            return 0;
        }          
    cout << "not a poem" << endl;
  return 0;  
}