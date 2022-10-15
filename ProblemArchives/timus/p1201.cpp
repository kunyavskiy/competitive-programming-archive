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
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


const int days[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};


void nextday(int& d,int& m,int& y){
    if (d == days[m] + (m == 2 && (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)))){
        d = 1, m++;
        if (m == 13){
            m = 1, y++;
        }
    }
    else
        d++;
}

void nextweek(int& d,int& m,int& y){
    for (int i = 0; i < 7; i++)
        nextday(d,m,y);
}

const string wdays[7] = {"mon","tue","wed","thu","fri","sat","sun"};

char out[7][1000];
char* cur;


#define print(...) {sprintf(cur,__VA_ARGS__); while (*cur) cur++;}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int D,M,Y;
    cin >> D >> M >> Y;

    bool printed1 = false;

    for (int i = 0; i < 7; i++){
        cur = out[i];
        int d,m,y;
        d = i+4, m = 1, y = 1599;

        print("%s",wdays[i].data());


        for (int i = 0; i < 50000; i++){
            nextweek(d,m,y);
            if (m == M && y == Y){
                if (d == 1)
                    printed1 = true;
                if (!printed1 && d <= 7){
                    print("     ");
                }
                if (d == D){
                    print(" [%2d]",d);
                }
                else {
                    print("  %2d ",d);
                }
            }
        }
    }

    int mlen = 0; 

    for (int i = 0; i < 7; i++){
       int curl = strlen(out[i]);
       while (out[i][curl-1] == ' '){
        curl--;
        out[i][curl] = 0;
       }

       mlen = max(mlen,curl);
    }

    for (int i = 0; i < 7; i++){
        int curl = strlen(out[i]);

        for (;curl < mlen; curl++)
            out[i][curl] = ' ';
        out[i][curl] = 0;
    }

    #ifdef LOCAL
        for (int i = 0; i < 7; i++)
            for (int j = 0; out[i][j]; j++)
                if (out[i][j] == ' ')
                    out[i][j] = '.';
    #endif


    for (int i = 0; i < 7; i++)
        puts(out[i]);
    return 0;
}