#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

unsigned long int res(unsigned long int a)
{	
	return a<3?0:a==3?1:a%2==0?2*res(a/2):res(a/2)+res(a/2+1);
}
int main()
{
    freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	unsigned long int n;
	scanf("%d",&n);
	printf("%d",res(n));
    return 0;
}