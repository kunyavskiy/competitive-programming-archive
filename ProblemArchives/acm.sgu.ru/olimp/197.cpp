#include <vector>
#include <fstream>
#define forc(i,n) for(int i=1;i<=n;i++)
#define read(n) scanf("%d",&n);

using namespace std;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n,m;
	scanf("%d %d ",&m,&n);
	vector<int> t(n+1);
	int tres=0,minres;
	for (int i=1;i<=m;i++)
	{
		int a;
		read(a);
		t[a]++;
		tres+=a?(n-a+1):0;
	}
	minres=tres;
	for (int i=1;i<=n;i++)
	{
		tres+=m;
		tres-=((n+1)*t[i]);
		minres=min(minres,tres);
	}
	printf("%d",minres);
	return 0;
}