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


void norm(string& s){
	sort(s.begin(),s.end());
}

bool cmp(string a,string b){
	if (a.size() != b.size())
		return a.size() < b.size();
	return a<b;
}

map<int,string> s;

string go(int n){
	if (s.find(n) != s.end())
		return s[n];
	if (n == 1)
		return "";
	string& ans = s[n];
	ans = "1111111111111111111111111111111111111111111111111111111111111111111111111111";
	for (int i = 2; i < 10; i++){
		if (n % i)
			continue;
		string t = go(n/i);
		t += char('0'+i);
		norm(t);
		if (cmp(t,ans))
			ans = t;
	}
	return ans;	
} 

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n;
	cin >> n;
	if (n == 0)
		cout <<"10"<<endl;
	else if (n == 1)
		cout << 1 << endl;
	else {
		if (go(n).size() > 40)
			cout << -1 << endl;
		else
			cout << go(n) << endl;
	}
	return 0;
}