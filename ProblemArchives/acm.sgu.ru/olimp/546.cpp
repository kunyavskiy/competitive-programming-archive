#include <vector>
#include <fstream>
#include <set>
#include <utility>
#include <algorithm>
#define forc(i,n) for(int i=1;i<=n;i++)
#define read(n) scanf("%d",&n);
#define mp make_pair

using namespace std;


int n;
multiset<int> c;
vector<int> pos;



bool per()
{
	if (c.empty())
		return true;
	int a=*(--c.end());
	//c.erase(--c.end());
	vector<int> deleted;
	//deleted.push_back(a);
	multiset<int>::iterator iter;
	bool q=true;
	for (int i=0;i<pos.size();i++)
	{
		int k=abs(pos[i]-a);
		iter=c.find(k);
		if (iter==c.end())
		{
			for (int j=0;j<deleted.size();j++)
				c.insert(deleted[j]);
			deleted.resize(0);
            q=false;
			break;
		}
		deleted.push_back(*iter);
		c.erase(iter);
	}
	if (q)
	{
		pos.push_back(a);
		if (per())
			return true;
		for (int j=0;j<deleted.size();j++)
				c.insert(deleted[j]);
		deleted.resize(0);
		pos.pop_back();
	}
	q=true;
	a=pos[1]-a;
	for (int i=0;i<pos.size();i++)
	{
		int k=abs(pos[i]-a);
		iter=c.find(k);
		if (iter==c.end())
		{
			for (int j=0;j<deleted.size();j++)
				c.insert(deleted[j]);
			deleted.resize(0);
            q=false;
			break;
		}
		deleted.push_back(*iter);
		c.erase(iter);
	}
	if (q)
	{
		pos.push_back(a);
		if (per())
			return true;
		for (int j=0;j<deleted.size();j++)
				c.insert(deleted[j]);
		deleted.resize(0);
		pos.pop_back();
	}
	//c.insert(pos[1]-a);
	return false;
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	read(n);
	forc(i,n)
	{
		int a;
		read(a);
		c.insert(a);
	}
	pos.push_back(0);
	pos.push_back(*(--c.end()));
	c.erase(--c.end());
	per();
	if (!c.empty())
		return 1;
	sort(pos.begin(),pos.end());
	for (int i=1;i<pos.size();i++)
		printf("%d ",pos[i]);
	return 0;
}