#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int a[3];

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	cin>>a[0]>>a[1]>>a[2];
	sort(a,a+3);
	cout<<2-(a[2]==a[1])-(a[1]==a[0])<<endl;			
    return 0;
}