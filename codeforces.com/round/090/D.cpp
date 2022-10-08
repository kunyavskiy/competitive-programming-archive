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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 1100000;

char s[MAXN];
char t[MAXN];
char t2[MAXN];
char str[2*MAXN];
int p[2*MAXN];

void calcp() {
	int n = strlen(str);
	for (int i=1; i<n; ++i) {
		int j = p[i-1];
		while (j > 0 && s[i] != s[j])
			j = p[j-1];
		if (str[i] == str[j])  ++j;
		p[i] = j;
	}
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    gets(s);
    gets(t);
    int n = strlen(s);
    if (strlen(t) != n){
    	cout << -1 <<" "<<-1 << endl;
    	return 0;
    }
    memcpy(t2,t,sizeof(t));
    reverse(t2,t2+n);
    memcpy(str,s,sizeof(char)*n);
    reverse(Str,str+n);
    str[n] = char(1);
    memcpy(str+n+1,t,sizeof(char)*n);
    reverse(str+n+1,str+2*n+1);
    calcz();

    int ansi,ansj;
    ansi = ansj = -1;

    for (int i = 0; s[i] == t2[i] && i < n; i++){
    	int maxs = p[2*n - i - 1];
    	if (n - maxs - i >= 0)
    		
    }

    return 0;
}