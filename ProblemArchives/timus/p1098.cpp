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


int get(int n,int N){
    if (n == 1)
        return 0;
    int temp = get(n-1,N);
    return (temp+N+1)%n;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    char c;
    while (cin.get(c))
        if (c != '\n') 
            s+=c;
    int n = s.size();
    int val = get(n,1998);

    if (s[val] == '?')
        cout <<"Yes"<<endl;
    else if (s[val] == ' ')
        cout <<"No"<<endl;
    else
        cout <<"No comments"<<endl;
    return 0;
}