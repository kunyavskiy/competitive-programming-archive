#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
    #define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MaxLength = 30;
const int Lines = 8;
const int MaxStation = 15;
const int Stations[Lines] = {13, 10, 11, 12, 9, 14, 15, 13};
const char Line[Lines][MaxStation][MaxLength + 1] = {
    {"7_klyuchey", "Sortirovochnaya", "China_town", "Zarechny", "City", "1905_year_square", "Kuybyshevskaya",
        "Sibirskaya", "Siniye_kamni", "Lechebnaya", "Varshavskaya", "Kompressornaya", "Koltsovo"},
    {"Zelyony_ostrov", "Tatishchevskaya", "Verh_Isetskaya", "Kommunarov_square", "1905_year_square",
        "Teatralnaya", "Vostochnaya", "Vtuzgorodok", "Kamennye_palatki", "University"},
    {"MEGA", "Metallurgov", "Kraulya", "Central_stadium", "Moskovskaya", "1905_year_square",
        "Shevchenko", "Pionerskaya", "Turbinnaya", "Elmash", "Taganskaya"},
    {"Akademicheskaya", "Yugo_zapadnaya", "Volgogradskaya", "Posadskaya", "Geologicheskaya", "Teatralnaya",
        "Gagarinskaya", "Komsomolskaya", "Shefskaya", "Ozyornaya", "Italyanskaya", "Kalinovskaya"},
    {"Sovhoznaya", "Voennaya", "Aviatsionnaya", "Dvorets_sporta", "Geologicheskaya",
        "Kuybyshevskaya", "Vostochnaya", "Gagarinskaya", "Vilonovskaya"},
    {"Keramicheskaya", "Vtorchermet", "Samolyotnaya", "Botanicheskaya", "Parkovaya", "Mayakovskaya",
        "Oborony_square", "Kuybyshevskaya", "Teatralnaya", "Shevchenko", "Uralskaya", "Zvezda",
        "I_Pyatiletki_square", "Pobedy"},
    {"Himmash", "Nizhne_Isetskaya", "Uktusskie_Gory", "Shcherbakovskaya", "Botanicheskaya", "Chkalovskaya",
        "Bazhovskaya", "Geologicheskaya", "1905_year_square", "Dinamo", "Uralskaya", "Mashinostroiteley",
        "Uralmash", "Prospekt_Kosmonavtov", "Bakinskih_Komissarov"},
    {"Moskovskaya", "Kommunarov_square", "City", "Uralskaya", "Pionerskaya", "Gagarinskaya", "Vtuzgorodok",
        "Sibirskaya", "Oborony_square", "Bazhovskaya", "Dvorets_sporta", "Posadskaya", "Moskovskaya"}
};

map<string,int> id;

int getid(string s){
    if (id.find(s) != id.end())
        return id[s];
    int t = id.size();
    return id[s] = t;
}

int g[150][150];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    
    memset(g,0x3f,sizeof g);

    for (int i = 0; i < Lines; i++)
        for (int j = 1; j < Stations[i]; j++){
            int a = getid(Line[i][j]);
            int b = getid(Line[i][j-1]);
            g[a][b] = g[b][a] = 1;
        }


    int n = id.size(); ;
    for (int i = 0; i < n; i++)
        g[i][i] = 0;

    for (int k = 0; k < n; k++)
       for (int i = 0; i < n; i++)
           for (int j = 0; j < n; j++)     
               g[i][j] = min(g[i][j],g[i][k]+g[k][j]);

    int m;
    cin >>m;
    for (int i = 0; i < m; i++){
        string s,t;
        cin >> s >> t;
        cout << g[getid(s)][getid(t)] << endl;
    }

    return 0;
}