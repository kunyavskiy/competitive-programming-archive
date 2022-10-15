#include <fstream>
#define read(n) scanf("%d",&n);

using namespace std;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n;
    read(n);
	int res=2;
	for (int i=1;i<n;i+=2)
		res=res*2-1;
	printf("%d",res);
	return 0;
}