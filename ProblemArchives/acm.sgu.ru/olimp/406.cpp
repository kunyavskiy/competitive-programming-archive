#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;



vector<int> a(11000),num(11000);
void qsort(int l,int r)
{
	int i=l;
	int j=r;
	int m=a[(l+r)/2];
	while (i<=j)
	{
		for (;a[i]<m;i++);
		for (;a[j]>m;j--);
		if (i<=j)
		{
			 int t=a[i];
			 a[i]=a[j];
			 a[j]=t;
			 t=num[i];
			 num[i]=num[j];
			 num[j]=t;
			 i++;
			 j--;
		}
	}
  if (l<j) qsort(l,j);
  if (i<r) qsort(i,r);
}
int main()
{
  freopen("input.txt","rt",stdin);
  freopen("output.txt","wt",stdout);
  int n,d;
  scanf("%d %d\n",&n,&d);
  a.resize(n+1);
  num.resize(n+1);
  int i;
  for (i=1;i<=n;i++)
  {
    scanf("%d",&a[i]);
	num[i]=i;
  }
  stack<int> pbil;
  pbil.push(-1);
  for (i=n;i>0;i--)
	  pbil.push(i);
  qsort(1,n);
  queue<int> person;
  vector<int> bil(n+1);
  int k=0;
  for (i=1;i<=n;i++)
  {
	 while ((person.empty()==false) &&  (a[person.front()]<a[i]-d))
	 {
		 pbil.push(bil[num[person.front()]]);	
		 person.pop();
	 }

	 bil[num[i]]=pbil.top();
	 k=max(k,pbil.top());
	 pbil.pop(); 
	 person.push(i);

  };
  printf("%d\n",k);
  for (i=1;i<=n;i++)
	    printf("%d ",bil[i]);
  return 0;
}