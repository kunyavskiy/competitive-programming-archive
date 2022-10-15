#include <fstream>
#include <vector>
#include <algorithm>
#define newobr(a,b) obr[av[a]]=av[b]
using namespace std;

vector<int> av(7);





int sloj(int a,int b, int c,int d, int e, int f)
{
	int res=av[a];
	res=res*10+av[b];
	res=res*10+av[c];
	res=res*10+av[d];
	res=res*10+av[e];
	res=res*10+av[f];
	return res;
}
int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int a;
	scanf("%d",&a);
	for (int i=6;a!=0;a/=10)
		av[i--]=a%10;
	/*newobr(1,4);
	newobr(2,3);
	newobr(5,6);
	newobr(4,1);
	newobr(3,2);
	newobr(6,5);
	vector<int> cif;
	for (int i=1;i<=6;i++)
	  for (int j=1;j<=6;j++)
	    for (int k=1;k<=6;k++)
			cif.push_back(sloj(i,j,k));
	sort(cif.begin(),cif.end());
	vector<int> cif2;
	int l=cif.size()-1;
	for (int i=168;i<=l;i++)
	{
		if ((cif[i]!=0) && (cif[i]!=cif[i-1]))
			cif2.push_back(cif[i]);
	}
	l=cif2.size()-1;
	for (int i=0;i<=l;i++)
	{
		printf("cif.push_back(sloj(%d",cif2[i]/100000);
		cif2[i]%=100000;
		printf(",%d",cif2[i]/10000);
		cif2[i]%=10000;
		printf(",%d",cif2[i]/1000);
		cif2[i]%=1000;
		printf(",%d",cif2[i]/100);
		cif2[i]%=100;
		printf(",%d",cif2[i]/10);
		cif2[i]%=10;
		printf(",%d));\n",cif2[i]);
	}*/
   vector<int> cif;

   cif.push_back(sloj(1,2,3,4,5,6));//+
   cif.push_back(sloj(1,3,2,4,6,5));//+
   cif.push_back(sloj(1,5,6,4,3,2));//+
   cif.push_back(sloj(1,6,5,4,2,3));//+

   cif.push_back(sloj(2,1,4,3,6,5));//+
   cif.push_back(sloj(2,4,1,3,5,6));//+
   cif.push_back(sloj(2,5,6,3,1,4));//+
   cif.push_back(sloj(2,6,5,3,4,1));//+

   cif.push_back(sloj(3,1,4,2,5,6));//+
   cif.push_back(sloj(3,4,1,2,6,5));//+
   cif.push_back(sloj(3,5,6,2,4,1));//+
   cif.push_back(sloj(3,6,5,2,1,4));//+

   cif.push_back(sloj(4,2,3,1,6,5));//+
   cif.push_back(sloj(4,3,2,1,5,6));//+
   cif.push_back(sloj(4,5,6,1,2,3));//+
   cif.push_back(sloj(4,6,5,1,3,2));//+

   cif.push_back(sloj(5,1,4,6,2,3));//+
   cif.push_back(sloj(5,2,3,6,4,1));//+
   cif.push_back(sloj(5,3,2,6,1,4));//+
   cif.push_back(sloj(5,4,1,6,3,2));//+

   cif.push_back(sloj(6,1,4,5,3,2));//+
   cif.push_back(sloj(6,2,3,5,1,4));//+
   cif.push_back(sloj(6,3,2,5,4,1));//+
   cif.push_back(sloj(6,4,1,5,2,3));//+
   sort(cif.begin(),cif.end());
   int b;
   scanf("%d",&b);
   for (int i=0;i<=cif.size()-1;i++)
   {
	   if (cif[i]==b)
	   {
		   printf("%d",i+1);
		   return 0;
	   }
   }
   printf("0");
   return 0;
}