#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> rasl(int a)
{
	vector<int> c;
	for (;a;a/=10)
		c.push_back(a%10);
	sort(c.begin(),c.end());
	return c;
}

int sloj (vector<int> a)
{
	int res=0;
	int l=a.size()-1;
	for (int i=0;i<=l;i++)
		res=res*10+a[i];
	return res;
}
int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int t,al,bl,c;
	scanf("%d",&t);
	vector<int>a=rasl(t);    
	scanf("%d",&t);
	scanf("%d",&c);
	vector<int>b=rasl(t);
	vector<int> av,bv;
	av.push_back(sloj(a));
	for (;next_permutation(a.begin(),a.end());)
		av.push_back(sloj(a));	
	bv.push_back(sloj(b));
	for (;next_permutation(b.begin(),b.end());)
		bv.push_back(sloj(b));	
	sort(av.begin(),av.end());
	int kolit=bv.size()-1;
	for (int i=0;i<=kolit;i++)
		  if (binary_search(av.begin(),av.end(),c-bv[i]))
		  {
			  printf("YES\n");
			  printf("%d %d",c-bv[i],bv[i]);
			  return 0;
		  }
  printf("NO");
  return 0;
}