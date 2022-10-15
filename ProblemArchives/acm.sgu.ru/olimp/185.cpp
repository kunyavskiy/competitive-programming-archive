#include <fstream>;
using namespace std;


int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int a;
	scanf("%d",&a);
	int res=a==2?4:2*a+4*(a/2-2);
	printf("%d",res);
}