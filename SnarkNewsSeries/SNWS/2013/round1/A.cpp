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


string norm(string s){
	string res = "";

	for (int i = 0; i < (int)s.size(); i++)
		if ('A' <= s[i] && s[i] <= 'Z')
			s[i] = s[i] + 'a' - 'A';
		else if (!('a' <= s[i] && s[i] <= 'z'))
			s[i] = ' ';

	for (int i = 0; i < (int)s.size(); i++)
		if (s[i] != ' ')
			res += s[i];
		else
			if (i > 0 && s[i-1] != ' ')
				res += " ";
	if (res.size() && res[res.size()-1] == ' ')
		res = string(res.begin(),res.end()-1);        
	return res;	
}

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    string s,t;
    getline(cin,s);
    getline(cin,t);
        
    s = norm(s);
    t = norm(t);
    if (s == t)
    	puts("YES\n");
    else
    	puts("NO\n");
    return 0;
} 