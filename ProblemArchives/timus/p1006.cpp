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
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int N = 20;
const int M = 50;

unsigned char s[N+1][M+1];                  


bool check(int x1,int x2,unsigned char c){
   return (s[x1][x2] == c || s[x1][x2] == 32);
}

bool check(int x1,int y1,int x2,int y2){
    if (!check(x1,y1,218)) return false;
    if (!check(x1,y2,191)) return false;
    if (!check(x2,y1,192)) return false;
    if (!check(x2,y2,217)) return false;

    for (int i = x1+1; i < x2; i++){
        if (!check(i,y1,179)) return false;
        if (!check(i,y2,179)) return false;
    }
    for (int i = y1+1; i < y2; i++){
        if (!check(x1,i,196)) return false;
        if (!check(x2,i,196)) return false;  
    }

    return true;
}

bool erase(int x1,int y1,int x2,int y2){
    bool q = false;
    q |= (s[x1][y1] != ' ');s[x1][y1] = ' ';
    q |= (s[x1][y2] != ' ');s[x1][y2] = ' ';
    q |= (s[x2][y1] != ' ');s[x2][y1] = ' ';
    q |= (s[x2][y2] != ' ');s[x2][y2] = ' ';
    for (int i = x1+1; i < x2; i++){
        q |= (s[i][y1] != ' ');
        q |= (s[i][y2] != ' ');
        s[i][y1] = s[i][y2] = ' ';
    }
    for (int i = y1+1; i < y2; i++){
        q |= (s[x1][i] != ' ');
        q |= (s[x2][i] != ' ');
        s[x1][i] = s[x2][i] = ' ';
    }
    return q;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    for (int i = 0; i < N; i++){
        scanf(" ");
        for (int j = 0; j < M; j++) {
            s[i][j] = (unsigned char)getc(stdin);
        }
    }

    vector<pair<pair<int,int>,int> > v;

    while (true){
       bool q = true;
       for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
           for (int k = 1; i+k < N && j+k < M; k++)
              if (check(i,j,i+k,j+k) && erase(i,j,i+k,j+k)){
                  v.pb(mp(mp(i,j),k+1));
                  q = false;


                 /*for (int i = 0;i < N; i++,cerr<<endl)
                     for (int j = 0; j < M; j++)
                         cerr << s[i][j];
                 cerr<<endl<<endl; */
              } 
       if (q) break;
    } 
                            

    reverse(v.begin(),v.end());

    printf("%d\n",v.size());
    for (int i = 0; i < (int)v.size(); i++)
        printf("%d %d %d\n",v[i].first.second,v[i].first.first,v[i].second);

    return 0;
}