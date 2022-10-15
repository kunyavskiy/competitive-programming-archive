#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <stack>
#include <deque>
#include <queue>
#include <string>
#include <algorithm>
#include <cassert>
#include <ctime>

#define mp make_pair
#define pb push_back

using namespace std;

typedef long long int64;
typedef long double ld;

const string TASKNAME = "brackets";
const string INFILE = TASKNAME+".in";
const string OUTFILE = TASKNAME + ".out";

const int MAXN=2*50000+1000;

string s;
int bal[MAXN];
int next[MAXN];
int n;

int main(){
//	freopen(INFILE.data(),"r",stdin);
//	freopen(OUTFILE.data(),"w",stdout);
	getline(cin,s);
	n = s.size();
	bal[0] = 0;
	for (int i=1;i<=n;i++)
		bal[i] = bal[i-1]+(s[i-1]=='(')-(s[i-1]==')');
	next[n] = n;
	for (int i=n-1;i>=0;--i)
		if (bal[i] == 0)      
			next[i] = i;
		else
			next[i]=next[i+1];
	int64 ans = 0;
	for (int i=0;i<=n;i++){
		ans += n-i+1;
		ans += next[i] - i;
	}
	cout << ans << endl;
	return 0;
}
