#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <sstream>
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


int res[110];

map<string,int> number;

int getnum(string s){
    if (number.find(s) == number.end()){
        int cnt = number.size();
        number[s] = cnt;
        return cnt;
    }
    return number[s];
}

string name[110];
vector<int> g[110];


//vector<int> ans;
//vector<int> tempans;


int main (void){
#ifdef LOCAL
  freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
#endif

    int n;
    string s;
    getline(cin,s);
    sscanf(s.data(),"%d",&n);

    for (int i = 0; i < n; i++){
        getline(cin,s);
        stringstream str(s);
        int id;
        string name;
        str >> name;
        id = getnum(name);
        ::name[id] = name;

        int cnt = 0;
        str >> cnt;

        for (int i = 0; i < cnt; i++){
            str >> name;
            g[id].pb(getnum(name));
        }   


    }


    for (int i = 0; i < n; i++)
        res[i] = 1<<30;


    int ans = 0;

    string twit;
    getline(cin,twit);



        res[0] = twit.size();

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (res[j] > 140)
                    continue;
                int nl = res[j] + 6 + name[j].size();
                for (int k = 0; k < (int)g[j].size(); k++)
                    res[g[j][k]] = min(res[g[j][k]],nl);            
            }
        }



    int cnt = 0;
    for (int i = 0; i < n; i++)
        cnt += res[i] < (1<<28);

    cout << cnt << endl;

    for (int i = 0; i < n; i++)
        if (res[i] < (1<<28))
         cout << name[i] << endl;

  return 0;  
}