#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <set>
#include <utility>
#include <algorithm>
#include <map>
#define pii pair<int,int>
#define ppii pair<pii,pii>
#define mp make_pair
using namespace std;


set<int> reb;//c����� ������� ����� ����� ����������.
map<pii,int> rebnum;//map<pair<����� �������1,����� ������� 2>,����� �����.>
vector< ppii> gr;//������ �����. vector<�������,pair<��� ����������� ����� �� ����.>>
const int inf=1<<30;//� ��� �� �����������?))
class snmkr{//�����, ����������� �������.
public:
	vector<int> p;// ��� ���
	int kol;//���������� �����.
	void setsize(int n)// �������������
	{
		this->p.resize(n);
		for (int i=0;i<n;i++)
			this->p[i]=i;
		this->kol=0;
	}
	int root (int a)
	{
		if (this->p[a]==a)
			return a;
		return this->p[a]=root(this->p[a]);
	}
	void uni (int a,int b,int c) //������ �������� - ����� �����.
	{
		a=this->root(a);
		b=this->root(b);
		if (a!=b)
		{
			reb.insert(c);//�������� ����� � ������.
			++kol;
			if (rand()%2)
				this->p[a]=b;
			else
				this->p[b]=a;
		}
	}
};

class snmnorm:public snmkr{// ����� ��� �������� ������ ��������� �����.
public:
	vector<vector<int>> g;// ������� ��������� ��� ���������.
	vector<int> minreb;  //����������� ����� � ����������.
	vector<int> minnum;  //��� �����
	vector<int> st;      //��� ���������� ����� � ����������. 
	vector<int> stnum;   //����� ���������� �����
	int size;
	void setsize(int n)//������������� �������.
	{
		this->p.resize(n);
		this->size=n;
		for (int i=1;i<n;i++)
			this->p[i]=i;
		this->minreb.assign(n,inf);
		this->st.assign(n,inf);
		this->stnum.resize(n);
		this->minnum.resize(n);
		this->g.resize(n);
		for (int i=0;i<n;i++)
			this->g[i].assign(n,inf);
	}
	void uni(int a,int b,int c,bool init=false)// ����������� ��������� � a � b. ���� init=f�lse, �� ������ ���������� ���� a �� c.
	{
		a=this->root(a);
		b=this->root(b);		
		if (!init){reb.insert(c);reb.erase(this->stnum[a]);}//������.
		if (rand()%2)//�����������
		{
			this->p[a]=b;
			int t=a;//����� � a �������� ����� ������������� ������.
			a=b;
			b=t;
		}
		else
		{
			this->p[b]=a;
			stnum[a]=stnum[b];//��������� � ����� ��� a ������.
			st[a]=st[b];
		}

		for (int i=1;i<size;i++)// ������ ��� ����� b - ����� a, ������ � ��� ����.
			if (this->minnum[i]==b)
				this->minnum[i]=a;
		minreb[a]=inf;//����������� ������� ��� a
		minnum[a]=0;
		for (int i=1;i<size;i++)
		if ((p[i]=i)&&(i!=a))
		{
			int t=this->minreb[a];
			this->minreb[a]=min(this->minreb[a],this->g[a][i]=this->g[i][a]=min(this->g[i][a],this->g[i][b]));// ��� �������  �� ���� ��� ���� � g[i][a],g[i][b], ������ � ������� ������� ��� a.
			if (t!=this->minreb[a])
				minnum[a]=i;
		}
	}
	void unimax()// ����� ������ ������.
	{
		int m=-(inf);
		int mn=0;
		for (int i=1;i<this->size;i++)
			if (((this->st[i])-(this->minreb[i])>m)&&(p[i]==i))//���� ����� �������� � ������� �� ����������,��..
			{
				m=(this->st[i])-this->minreb[i];
				mn=i;
			};
		uni(mn,this->minnum[mn],rebnum[mp(mn,this->minnum[mn])]);//����� �����������.
	}
	snmnorm(int n)//�����������(������������� ������������).
	{
		setsize(n);
		for (int i=0;i<gr.size();i++)//���������� ������ ���������
		{
			this->g[gr[i].first.first][gr[i].first.second]=g[gr[i].first.second][gr[i].first.first]=gr[i].second.first;
		};
		for (int i=1;i<size;i++)// ������ ����������� �����.
			for (int j=1;j<size;j++)
				if (minreb[i]>g[i][j])
				{
					minreb[i]=g[i][j];
					minnum[i]=j;
				};
		for (set<int>::iterator iter=reb.begin();iter!=reb.end();++iter)// ����� ��������� �����.
		{
			int t=*iter;
			if ((gr[t].first.first==0)||(gr[t].first.second==0))
			{
				st[gr[t].first.first+gr[t].first.second]=gr[t].second.first;
				stnum[gr[t].first.first+gr[t].first.second]=t;
			}
		};
		for (set<int>::iterator iter=reb.begin();iter!=reb.end();++iter)// ����������� � ���������� �� ����������� �����.
		{
			int t=*iter;
			if ((gr[t].first.first!=0)&&(gr[t].first.second!=0))
				uni(gr[t].first.first,gr[t].first.second,t,true);
		}

	}
};

bool lessppiipii (ppii a,ppii b)//�������� ��������� ��� �����.
{
	return a.second.first<b.second.first;
}
int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n,m,k;
	scanf("%d %d %d\n",&n,&m,&k);
	gr.resize(m);
	int stol=0;
	for (int i=0;i<m;i++)// ���������� �����, ������� ���������� ���� �����.
	{
		scanf("%d %d %d\n",&gr[i].first.first,&gr[i].first.second,&gr[i].second.first);
		gr[i].first.first--;//0-����������.
		gr[i].first.second--;
		gr[i].second.second=i;
		if ((gr[i].first.first==0)||(gr[i].first.second==0))
			stol++;
	}
	sort(gr.begin(),gr.end(),lessppiipii);//����������
	for (int i=0;i<m;i++)	//��������� ������� �����	
		rebnum[mp(gr[i].first.first,gr[i].first.second)]=rebnum[mp(gr[i].first.second,gr[i].first.first)]=i;
	snmkr a;//�������
	a.setsize(n);
	for (int i=0;i<gr.size();i++)
    	if ((gr[i].first.first==0)||(gr[i].first.second==0))//������� ��������� �����
		   a.uni(gr[i].first.first,gr[i].first.second,i);
	for (int i=0;i<gr.size();i++)//����� ���������
		   a.uni(gr[i].first.first,gr[i].first.second,i);
	if ((stol<k)||(a.kol<n-1))// ���� ���� ��������� ����� ��� ���� �� �������
	{
		printf("-1");
		return 1;
	}
	snmnorm b(n);// ������� �������� �����.
	for (;stol>k;stol--)//���� ��������� �� ������� ������� ����
	{
		b.unimax();// ������ ����� ������.
	}
	printf("%d\n",n-1);
	for (set<int>::iterator iter=reb.begin();iter!=reb.end();++iter)//�����
		printf("%d ",gr[*iter].second.second+1);
	return 0;
}