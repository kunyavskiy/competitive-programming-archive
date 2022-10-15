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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


bool a[8][8];

string ans[64];
int n;

const int dx[8] = {-2,-2,-1,-1,1,1,2,2};
const int dy[8] = {1,-1,2,-2,2,-2,1,-1};



void go(int i,int j,int c){
    if (i < 0 || j < 0 || i >= n || j >= n || a[i][j])
        return;
    a[i][j] = true;
    ans[c][0] = 'a' + i;
    ans[c][1] = '1' + j;

    if (c == n*n-1){
        for (int i = 0; i < n*n; i++)
            cout << ans[i] << "\n";
        exit(0);
    }


    for (int k = 0; k < 8; k++)
        go(i+dx[k],j+dy[k],c+1);
    a[i][j] = false;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    cin >> n;

    for (int i = 0; i < n*n; i++)
        ans[i] = "  ";

    if (n == 8){
        printf("a1\nb3\na5\nb7\nc5\na6\nb8\nc6\na7\nb5\na3\nb1\nc3\na4\nb6\na8\nc7\nd5\nb4\na2\nc1\nd3\nb2\nc4\nd6\nc8\ne7\nf5\nd4\nc2\ne3\nd1\nf2\ne4\nd2\nf1\nh2\nf3\ne1\ng2\nh4\ng6\nh8\nf7\nd8\ne6\nf4\ne2\ng1\nh3\ng5\nh7\nf8\nd7\ne5\ng4\nh6\ng8\nf6\ne8\ng7\nh5\ng3\nh1\n");
        return 0;
    }

    if (n == 7){
        printf("c1\na2\nb4\na6\nc7\nb5\na7\nc6\na5\nb7\nc5\na4\nb6\nc4\na3\nb1\nc3\nd5\ne7\nf5\nd6\nf7\ng5\ne4\nd2\nb3\na1\nc2\nd4\nf3\ng1\ne2\ng3\nf1\ne3\ng2\ne1\nd3\nb2\nd1\nf2\ng4\nf6\nd7\ne5\ng6\nf4\ne6\ng7\n");
        return 0;       
    }
    

    for (int i = 0; i <= n-i; i++)
        for (int j = 0; j <= n-j; j++)
           go(i,j,0);
        
    printf("IMPOSSIBLE\n");   
    return 0;
}