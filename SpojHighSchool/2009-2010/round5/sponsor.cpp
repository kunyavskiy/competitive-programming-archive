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
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double
#define fileinout
using namespace std;

vector<int> ans;

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	ans.assign(30000,100000);
	for (;;){
		ld Tec;
		cin>>Tec;
		int tec=Tec*1000;
		if (tec>40*1000)
			break;
		tec=30000-tec;
		vector<int>::iterator iter=lower_bound(ans.begin(),ans.end(),tec);
		*iter=tec;
	}
	vector<int>::iterator iter=lower_bound(ans.begin(),ans.end(),50000);
	cout<<(iter-ans.begin())*100<<endl;
  return 0;
}