#include  <vector>
#include  <utility>
#include  <algorithm>

using namespace std;

bool lesssort(pair<int,int> a,pair<int,int> b)
{
	if (a.second==b.second)
		return a.first>b.first;
	return a.second<b.second;
}

bool lessbin(int a,int b)
{
	return a>b;
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n;
	scanf("%d",&n);
	vector<pair<int,int>> otr(n);
	for (int i=0;i<n;i++)
		scanf("%d %d",&otr[i].first,&otr[i].second);
	sort(otr.begin(),otr.end(),lesssort);
	vector<int> t;
	t.assign(n,-(1<<30));
	vector<int> from;
	for (int i=0;i<n;i++)
	{
		vector<int>::iterator a=upper_bound(t.begin(),t.end(),otr[i].first,lessbin);
		from.push_back(a-t.begin()+1);
		*a=otr[i].first;
	}
	int ns=0;
	for (int i=0;i<n;i++)
      ns=max(ns,from[i]);
	printf("%d\n",ns);
	int ll=-(1<<30);
	for (int i=n-1;i>=0;i--)
	if ((from[i]==ns)&&(otr[i].first>=ll))
	{
		printf("%d %d\n",otr[i].first,otr[i].second);
		ns--;
	}

}