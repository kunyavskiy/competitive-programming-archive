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

string res;

int p[300000];

unsigned char ans[300000];
int ptr = 0;

int go(int start){
	//cerr <<"! " << start<<" "<<(int)ans[0] <<" "<<(int)ans[1] <<" "<<(int)ans[2] <<" "<< (int)ans[3] << endl;
	int cur = start;                                 
	while (true){                                                                             
		if (res[cur] == '>')
			ptr++;
		else if (res[cur] == '<')
			ptr--;
		else if (res[cur] == '+')
			ans[ptr]++;
		else if (res[cur] == '-')
			ans[ptr]--;
		else if (res[cur] == '['){
			if (ans[ptr] == 0)
				cur = p[cur];
		}
		else if (res[cur] == ']'){
			cur = p[cur] - 1;
		}
		else if (res[cur] == '.'){
			#ifndef LOCAL
			printf("%c",(char)ans[ptr]);
			#else
			printf("%d ",ans[ptr]);
			#endif
		}
		else if (res[cur] == '#')
			exit(0);
		//cerr << res[cur] <<"["<<cur<<"] ";
		//cerr << (int)ans[0] <<" "<<(int)ans[1] <<" "<<(int)ans[2] <<" "<< (int)ans[3] << endl;
		cur++;
	}
}

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    string _;
    while (getline(cin,_))
    	res += _;

    stack<int> s;

    for (int i = 0; i < (int)res.size(); i++)
    	if (res[i] == '[')
    		s.push(i);
    	else if (res[i] == ']'){
    		p[i] = s.top();
    		p[s.top()] = i;
    		s.pop();
    	}

    go(0);


    return 0;
} 