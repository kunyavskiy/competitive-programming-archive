#include <iostream>
#include <vector>
#include <string>
using namespace std;


const int inf=1<<25;

vector<int> a;
vector<vector<int>> t;
int len(int l,int r)
{
	if ((l==r)||(l==r+1))
		return 0;
	if (t[l][r]!=-1)
		return t[l][r];
	t[l][r]=inf;
	for (int l1=l+1,r1=r-1,suml=a[l],sumr=a[r],count=0;l1<=r1+1;)
	{
		if ((suml==sumr) && (suml!=0))
			t[l][r]=min(t[l][r],count+len(l1,r1));
		if (suml<=sumr)
		{
			suml+=a[l1++];
				count++;
			if (suml>62)
				break;
		}
		else
		{
			sumr+=a[r1--];
				count++;
			if (sumr>62)
				break;
		}
	}
	int sum=0;
	for (int i=l;i<=r;i++)
		sum+=a[i];
	if (sum<=62)
		t[l][r]=min(t[l][r],r-l);
	return t[l][r];
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	string s;
	getline(cin,s);
	a.resize(s.size());
	for (int i=0;i<s.size();i++)
		if ((s[i]>='A') && (s[i]<='Z'))
			a[i]=s[i]-'A'+1;
		else if ((s[i]>='a') && (s[i]<='z'))
			a[i]=s[i]-'a'+27;
		else
			a[i]=s[i]-'0'+53;
	t.resize(s.size());
	for (int i=0;i<t.size();i++)
		t[i].assign(t.size(),-1);
	int res=len(0,s.size()-1);
	if (res==inf)
		printf("-1");
	else
		printf("%d",res);
	return 0;
}