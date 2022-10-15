#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

char nextl[1100000];
char nextr[1100000];

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

        string s;
        getline(cin,s);

        for (int i = (int)s.size()-1; i >= 0; i--)
        	if (s[i] == ')')
        		nextr[i] = ')';
        	else if (s[i] == '(')
        		nextr[i] = '(';
        	else
        		nextr[i] = nextr[i+1];


        for (int i = 0; i < (int)s.size(); i++)
        	if (s[i] == ')')
        		nextl[i] = ')';
        	else if (s[i] == '(')
        		nextl[i] = '(';
        	else
        		nextl[i] = (i?nextl[i-1]:0);
        		 



        int cnt = 0;
        for (int i = 0; i < (int)s.size(); i++){
        	if (s[i] == '(')
        		cnt++;
        	char t = s[i];
        	if (nextl[i] == '(' || nextr[i] == ')')
        		s[i] = '*';
        	if (t == ')')
        		cnt--;
        }
        printf("%s\n",s.data());
        return 0;
} 