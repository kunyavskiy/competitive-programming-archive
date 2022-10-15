#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


vector<int> sum (vector<int> sl1, vector<int> sl2)
{
  vector<int> c;
  int ost=0;
  for (int i=0;i<max(sl1.size(),sl2.size());i++)
  {
	  if (i<sl1.size()) ost+=sl1[i];
	  if (i<sl2.size()) ost+=sl2[i];
	  c.push_back(ost%10);
	  ost/=10;
  }
  if (ost!=0)
	  c.push_back(ost);
  return c;
  

}
int main()
{
  freopen("input.txt","rt",stdin);
  freopen("output.txt","wt",stdout);
  vector<int>  kolchet,kolnechet;
  kolchet.push_back(1);
  kolnechet.push_back(1);
  int n;
  scanf("%d \n",&n);
  for (int i=1;i<=n;i++)
  {
	  int a;
	  scanf("%d ",&a);
	  if (a<0) 
		  a=-a;
	  if (a%2==0)
		  kolchet=sum(kolchet,kolnechet);
	  else
	      kolnechet=sum(kolchet,kolnechet);
  }
  vector <int> kol=sum(kolchet,kolnechet);
  if (kol[0]>=2) kol[0]-=2;
  else
  {
    int i;
	for (i=1;kol[i]==0;kol[i++]=9);
	kol[i]--;
	kol[0]+=8;
  }
  if (kol[kol.size()-1]==0)
	  kol.pop_back();
  for (int j=kol.size()-1;j>=0;j--)
	  printf("%d",kol[j]);
  return 0;
}