#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;
vector<int>  result;
multiset<int> p;
bool gen(int maxval)
{
	multiset<int> copy=p;
	result.push_back(maxval);
	for (;!copy.empty();)
	{
		int newval=*(--copy.end())-maxval;
		result.push_back(newval);
		if (result[result.size()-1]<0)
		{
			result.clear();
			return false;
		}
		for (int i=0;i<result.size()-1;i++)
		{
			if (copy.find(result[i]+newval)==copy.end())
			{
				result.clear();
				return false;
			}
			copy.erase(copy.find(result[i]+newval));
		}
	}

	return true;
}
int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		int a;
		scanf("%d",&a);
		p.insert(a);
	}
	int kol=0;
	int val=0;
	for (int i=*(--p.end())/2;i<*(--p.end());i++)
		if (gen(i))
		{
			kol++;
			val=i;
			result.clear();
		}
	if (kol==1)
	{
		gen(val);
		printf("%d\n",result.size());
		for (int i=result.size()-1;i>=0;i--)
			printf("%d ",result[i]);
		return 0;
	}
	printf("NO SOLUTION");
	return 0;
}