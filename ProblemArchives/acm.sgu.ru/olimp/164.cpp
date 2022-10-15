#include <vector>
#include <fstream>
#define forc(i,n) for(int i=1;i<=n;i++)
#define read(n) scanf("%d",&n);

using namespace std;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n;
	read(n);
	vector<int> t;
	t.push_back(0);
	t.push_back(0);
	int a;
	read(a);
	t.push_back(a);
	read(a);
	t.push_back(t[2]+a);
	for (int i=4;i<=n;i++)
	{
		read(a);
		t.push_back(min(t[i-1],t[i-2])+a);
	}
	printf("%d",t[n]);
	return 0;
}