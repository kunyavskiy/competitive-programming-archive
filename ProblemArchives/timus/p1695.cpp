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

ll msk[60];
int smask[60];
int umask[60];

const int _PREC = 24;
int PREC;

#pragma pack(1)
struct botva {
unsigned short ans1;
unsigned char ans2;
} ans[(1<<_PREC)+10];
int n;

#define ANS(x) ((int(ans[x].ans1) | (int(ans[x].ans2)<<16)) + 1)


int PREC1;

ll res;
ll multiply;


void go(int last,int mask1,int mask2){
    if (last == n)
        return;
    go(last+1,mask1,mask2);
    if (mask2 & (1<<(last-PREC))){
      res += ANS(mask1&smask[last]);
      go(last+1,mask1&smask[last],mask2&umask[last]);

    }
    //go(last+1,mask1,mask2);
}

void Load(){
    char s[55][55];
    for (int i = 0; i < n; i++)
        scanf(" %s",s[i]);

    int ord[55];
    int deg[55];
    for (int i = 0; i < n; i++){
        ord[i] = i; 
        deg[i] = 0;
        for (int j = 0; j < n; j++)
            deg[i] += s[i][j] == '1';
    }
                                     
    for (int i = 0 ;i < n; i++)
        for (int j = i+1; j < n; j++)
            if (deg[ord[j]] < deg[ord[i]])
                swap(ord[j],ord[i]);

    multiply = 1;
    int n0 = n;
    while (deg[ord[n-1]] == n0-1 && n >= 40){
        multiply *= 2;
        --n;
    }


    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            if (deg[ord[j]] > deg[ord[i]])
                swap(ord[j],ord[i]);  

    random_shuffle(ord,ord+n);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            if (s[ord[i]][ord[j]] == '1')
                msk[i] |= (1LL<<j);
        smask[i] = msk[i] & PREC1;
        umask[i] = msk[i] >> PREC;
    }
}

int main(){
  #ifdef LOCAL
    cerr << sizeof(ans) / 1024.0 / 1024 << endl;
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);  
  #endif

    ld START = clock();

    scanf("%d",&n);
    PREC = min(n-1,_PREC);

    PREC1 = (1<<PREC)-1;

    Load();

    int up = 0;

    ans[0].ans1 = 0;

    for (int i = 1; i < (1<<PREC); i++){
        while (i & (1<<(up+1))) up++;
        int t = ANS(i ^ (1<<up)) + ANS(i & smask[up]);
        ans[i].ans1 = (t-1) & ((1<<16)-1);
        ans[i].ans2 = (t-1) >> 16;
    }

    res = ANS((1<<PREC)-1);
     
    assert((clock() - START)/CLOCKS_PER_SEC < 0.2);

    go(PREC,(1<<PREC)-1,(1<<(n-PREC))-1);
    
    cout << res * multiply << endl;

   #ifdef LOCAL
      cerr << (clock() - START)/CLOCKS_PER_SEC << endl;
   #endif
    return 0;
}