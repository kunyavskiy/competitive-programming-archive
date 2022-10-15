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

#define taskname "nicknames"

using namespace std;

typedef long long ll;
typedef long double ld;


bool check(string a,string b){ 
    if (a.size() < b.size())
        swap(a,b);
    if (string(a.begin(),a.begin()+b.size()) == b)
        return false;
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    if (string(a.begin(),a.begin()+b.size()) == b)
        return false;
    return true;
}

bool check(string a,string b,string c){
    return check(a,b) && check(a,c) && check(b,c);
}

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

    int t;
    cin >> t;
    while (t --> 0){
        string a,b,c;
        cin >> a >> b >> c;
        if (check(a,b,c))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }


	return 0;
} 