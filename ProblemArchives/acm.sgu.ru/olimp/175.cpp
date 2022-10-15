#include <vector>
#include <fstream>
#include <set>
#include <utility>
#include <algorithm>
#define forc(i,n) for(int i=1;i<=n;i++)
#define read(n) scanf("%d",&n);
#define mp make_pair

using namespace std;


int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
    multiset <int> bat;
	vector<pair<int,int>> rob;
	vector<int>batt;
	int n,m;
	read(n);
	read(m);
	rob.reserve(n);
	forc(i,n)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		rob.push_back(mp(b,a));
	}
	forc(i,m)
	{
		int a;
		read(a);
		batt.push_back(a);
	}
	sort(rob.begin(),rob.end());
	sort(batt.begin(),batt.end());
	int l=batt.size()-1;
	for (int i=max(0,l-n+1);i<=l;i++)
		bat.insert(batt[i]);
	int res=0;
	for (int i=rob.size()-1;(i>=0)  && (!bat.empty());i--)
	{
		multiset<int>::iterator a=bat.lower_bound(rob[i].second);
		if (a!=bat.end())
		{
			res+=rob[i].first;
			bat.erase(a);
		}
	}
	printf("%d",res);
	return 0;
}