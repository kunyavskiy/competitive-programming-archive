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

int sum(int x){
	int ans=0;
	for (int i=1;i<=x;i++)
		ans+=i*(!(x%i));
	return ans;
}

int main()
{                        
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	vector<int> ans;
	int best=0;
	int a,b;
	cin>>a>>b;
	for (int i=a;i<=b;i++){
		int tmp=sum(i);
		if (tmp > best){
			ans.clear();
			best=tmp;			
		}
		if (tmp == best)
			ans.pb(i);
	}
	for (int i=0;i<ans.size();i++)
		cout<<ans[i]<<endl;
	return 0;
}