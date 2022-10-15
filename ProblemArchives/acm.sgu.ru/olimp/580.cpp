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
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

int main()
{                        
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	set<string> need;
	int n;
	cin>>n;
	for (int i=0;i<n;i++){
		string s;
		cin>>s;
		need.insert(s);
	}
	cin>>n;
	int sum=0;
	for (int i=0;i<n;i++){
		string s;int c;
		cin>>s>>c;
		if (need.find(s) == need.end())
			sum+=c;		
	}
	cout<<sum<<endl;
	return 0;
}