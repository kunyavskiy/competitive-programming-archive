#include <cstdio>
#include <vector>

using namespace std;

class Matching{
  int n, m;
  vector<vector<int>> g;
  vector<bool> used;
  vector<int> mt;

  bool dfs(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int u : g[v])
	if (mt[u] == -1 || dfs(mt[u])) {
	  mt[u] = v;
	  return true;
	}
    return false;
  }
public:
  Matching(int n, int m):n(n),m(m),g(n){}

  void addEdge(int a, int b){g[a].push_back(b);};

  int indep(){
      mt.resize(m, -1);
      int ans = n + m;
      for (int i = 0; i < n; i++){
	used = vector<bool>(n, false);
	if (dfs(i)) ans--;
      }
      return ans;
  }
};

const int MAXN = 101;
char s[MAXN][MAXN];

int main(){
    int n, m;
    scanf("%d%d",&n,&m);
    for (int i = 0; i < n; i++)
	scanf("%s",s[i]);

    int ans = 0;
    for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++)
	    if (s[i][j] == '1') {
		vector<int> ids0(n, -1);
		vector<int> ids1(m, -1);
		int cnt0 = 0, cnt1 = 0;
		for (int i1 = 0; i1 < n; i1++)
		    if (i1 != i && s[i1][j] == '1')
			ids0[i1] = cnt0++;
		for (int j1 = 0; j1 < m; j1++)
		    if (j1 != j && s[i][j1] == '1')
			ids1[j1] = cnt1++;
		Matching mat(cnt0, cnt1);
		for (int i1 = 0; i1 < n; i1++)
		    for (int j1= 0; j1 < n; j1++)
			if (ids0[i1] != -1 && ids1[j1] != -1 && s[i1][j1] == '0')
			    mat.addEdge(ids0[i1], ids1[j1]);
                ans = max(ans, mat.indep());
	    }
    printf("%d\n", 2*(2+ans));
}
