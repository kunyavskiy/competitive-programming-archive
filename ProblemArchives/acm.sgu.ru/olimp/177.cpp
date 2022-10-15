#include <iostream>
#include <algorithm>
#include <queue>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <cassert>

#define mp make_pair

using namespace std;

typedef long double ld;

bool a[30][30];
int n,m;
const int dx[4]={0,1,0,-1};
const int dy[4]={1,0,-1,0};
const char dname[4]={'R','B','L','T'};
int dnum[255];


bool good(int x,int y){
    return x>=0 && y>=0 && x<n && y<m && a[x][y];
}


int used[30][30];
string ans;


void iterate(int& x,int& y,const string& ans){
    used[x][y]=1;
    for (int i=0;i<ans.size();i++)
        if (good(x+dx[dnum[ans[i]]],y+dy[dnum[ans[i]]])){
            x+=dx[dnum[ans[i]]];
            y+=dy[dnum[ans[i]]];
            used[x][y]=1;
        }   
}

string ans1;
int cnt;
pair<int,int> p[30][30];
char pc[30][30];

bool gotopos(int x,int y,int ex,int ey){
    ans1="";
    if (x==ex && y==ey)
        return true;
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            p[i][j]=mp(-1,-1);
    queue<pair<int,int> > q;
    q.push(mp(x,y));
    for (;!q.empty();){
        int X=q.front().first;
        int Y=q.front().second;
        if (X==ex && Y==ey)
            break;
        q.pop();
        for (int i=0;i<4;i++){
            int nx=X+dx[i];
            int ny=Y+dy[i];
            if (good(nx,ny) && p[nx][ny].first==-1){
               p[nx][ny]=mp(X,Y);
               pc[nx][ny]=dname[i];
               q.push(mp(nx,ny));
            }
        }
                
    }
    if (p[ex][ey].first==-1)
        return false;
    for (;ex!=x || ey!=y;){
        ans1+=pc[ex][ey];
        int tmp=ex;
        ex=p[tmp][ey].first;
        ey=p[tmp][ey].second;
    }
    reverse(ans1.begin(),ans1.end());
    return true;
}

void goeverywhere(int x,int y){
    memset(used,false,sizeof(used));
    iterate(x,y,ans);
    cnt=0;
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)           
            if ((used[i][j]&1)==0 && a[i][j])
            {
                cnt+=2;
                bool q=gotopos(x,y,i,j);
                if (!q){
                    printf("IMPOSSIBLE\n");
                    exit(0);
                }
                ans+=ans1;
                iterate(x,y,ans1);
            }
}


int main(){
    dnum[dname[0]]=0;dnum[dname[1]]=1;
    dnum[dname[2]]=2;dnum[dname[3]]=3;
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d",&n);
    m=n;
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++){
            char c;
            scanf(" %c ",&c);
            a[i][j]=(c=='.');
        }
    ans="";
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            if (a[i][j]){
                goeverywhere(i,j);    
            }
    if (ans.size()==0)
        ans+='R';
    cout<<ans<<endl;
    return 0;
}
