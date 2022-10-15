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
#include <sstream>
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

struct node{
    node* next[10];
    bool term;
    node* p;
    int c;
    node* lnk;
};

node mem[2000];int memptr;

node* root;

node* getmem(){
    return mem + (memptr++);
}

void add(string s){
    node* t = root;
    for (int i = 0; i < (int)s.size(); i++){
        if (!t->next[s[i]-'0']){
            t->next[s[i]-'0'] = getmem();
            t->next[s[i]-'0']->p = t;
            t->next[s[i]-'0']->c = s[i]-'0';
        }
        t = t->next[s[i]-'0'];
    } 
    t->term = true;
}

void mklinks(){
    queue<node*> q;
    q.push(root);

    while (!q.empty()){
        node* v = q.front(); q.pop();
        if (v == root){
            v->lnk = root;
            for (int i = 0; i < 10; i++){
                if (!v->next[i])
                    v->next[i] = root;
                else
                    q.push(v->next[i]);
            }
            continue;
        }
        if (v->p == root)
            v->lnk = root;
        else
            v->lnk = v->p->lnk->next[v->c];
        v->term |= v->lnk->term;
        for (int i = 0; i < 10; i++){
            if (!v->next[i])
                v->next[i] = v->lnk->next[i];
            else
                q.push(v->next[i]);
        }
    }
}

template<typename T>
string vtos(T x){
    stringstream str;
    str << x;
    string s;
    return str.str();
}

long long dp[21][2][2][2000];


long long count(string R){
    while (R.size() < 20)
        R = '0'+R;

    for (int i = 0; i < memptr; i++)
        dp[20][1][1][i] = dp[20][0][1][i] = 1;

    for (int i = 19; i >= 0; i--)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                for (int p = 0; p < memptr; p++){
                    dp[i][j][k][p] = 0;
                    for (int next = 0; next < 10; next++){
                        if (!j && next > R[i]-'0')
                            continue;
                        int ni = i+1;
                        int nj = j | (next < R[i] - '0');
                        int np = mem[p].next[next]-mem;
                        int nk = k | mem[np].term;
                        dp[i][j][k][p] += dp[ni][nj][nk][np];
                    }
               }
    return dp[0][0][0][0];
}

void solve(string R,long long K){
    
    while (R.size() < 20)
        R = '0'+R;

    K--;

    if (count(R) <= K){
        printf("no such number\n");
        return ;
    }
                                
    int j,k,p;
    j = k = p = 0;

    long long ans = 0;


    for (int i = 0; i < 20; i++){
        for (int next = 0; next < 10; next++){
            if (!j && next > R[i]-'0')
                continue;
            int ni = i+1;
            int nj = j | (next < R[i] - '0');
            int np = mem[p].next[next]-mem;
            int nk = k | mem[np].term;
            if (dp[ni][nj][nk][np] > K){
                j = nj, k = nk, p = np;
                ans = 10 * ans + next;
                break;
            }
            K -= dp[ni][nj][nk][np];
        }
    }
        

    cout << ans << endl;
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    long long L,R,K;
    int n;
    cin >> L >> R >> K;
    root = getmem();

    cin >> n;

    for (int i = 0; i < n; i++){
        string s;
        cin >> s;
        add(s);
    }

    mklinks();

    K += count(vtos(L-1));
    solve(vtos(R),K);
    return 0;
}