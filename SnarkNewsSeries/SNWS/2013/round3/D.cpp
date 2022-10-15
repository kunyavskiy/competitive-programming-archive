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

int p[3100000];

bool check(string a,string b){
	b = a + '$' + b;
	p[0] = 0;
	for (int i = 1; i < (int)b.size(); i++){
		int j = p[i-1];
		while (j && b[j] != b[i])
			j = p[j-1];
		if (b[j] == b[i])
			j++;
		p[i] = j;
		if (p[i] == (int)a.size())
			return 1;
	}
	return 0;
}

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    int t;
    scanf("%d ",&t);
    for (int i = 0; i < t; i++){
    	string a,b;
    	getline(cin,a);
    	getline(cin,b);
    	if (a.size() != b.size()){
    		puts("NO");
    		continue;
    	};
		if (check(a,b+b))
			puts("YES");
		else {
			reverse(b.begin()+1,b.end());
			if (check(a,b+b))
				puts("YES");
			else
				puts("NO");
		}
    }
    return 0;
} 