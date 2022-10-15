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

int n;
char s[50][50];


void rev(int x,int y){
    s[x][y] = '+'^'-'^s[x][y];
    printf("%d ",y+1);
    
}

void rev(int x1,int x2,int y1,int y2){
    int a[50];
    for (int i = 0; i < n; i++)
        a[i] = i;

    swap(a[x1],a[y1]);
    swap(a[x2],a[y2]);

    for (int i = 0; i < n; i++)
        rev(i,a[i]);

    swap(a[x1],a[x2]);

   
    for (int i = 0; i < n; i++)
        rev(i,a[i]);
}


int calc(){
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans += (s[i][j] == '+');
    return ans;
}

void print(){

      #ifdef LOCAL
        for (int i = 0; i < n; i++)
            fprintf(stderr,"%s\n",s[i]);
        cerr<<endl;
      #endif
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    printf("There is solution:\n");

    scanf("%d",&n);
    n = 2*n+1;

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        scanf(" %c",&s[i][j]);  

    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-1; j++)
            if (s[i][j] == '+'){
                rev(i,i+1,j,j+1);
                print();
            }

    print();

    
    for (int it = 0; it < 2; it++){
      for (int i = 0; i < n-1; i++){
        if ((s[i][i] == '+') + (s[i][n-1] == '+') + (s[n-1][i] == '+') >= 2){
            rev(i,n-1,i,n-1);
        }
      }
      if (calc() >= n){
        for (int i = 0; i < n; i++)
            rev(i,i);
        printf("\n");
      }     
      print();
    }

                                    
    
    assert(calc() < n);
    return 0;
}