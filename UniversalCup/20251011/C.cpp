#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

struct Participation {
  int race_id;
  int result;
  int performance;
};

struct Race {
  int day;
  int is_special;
  int is_rated;
  int score;
  vector<pair<int, int>> participants;
};

struct Participant {
  vector<Participation> participations;
  int base_rating;
};

int emulate(vector<Participant> participants, vector<Race> races) {
  int days = races.back().day;
  vector<vector<int>> races_by_day(days + 1);
  for (int i = 0; i < (int)races.size(); i++) {
    races_by_day[races[i].day].push_back(i);
  }
  for (int i = 0; i < (int)participants.size(); i++) {
    for (int j = 0; j < (int)participants[i].participations.size(); j++) {
      assert(participants[i].participations[j].race_id < (int)races.size());
      races.at(participants[i].participations[j].race_id).participants.emplace_back(i, j);
    }
  }


  auto get_rating = [&](int p, int d) {
    auto& part = participants[p];
    vector<pair<int, int>> H;
    bool has_dq = 0;
    bool has_any = false;
    for (auto& participation : part.participations) {
      if (races[participation.race_id].day <= d) {
        if (!races[participation.race_id].is_rated) continue;
        has_any = true;
        if (races[participation.race_id].day <= d - 365) continue;
        if (participation.performance < 0) {
          has_dq = true;
        } else {
          H.emplace_back(participation.performance, races[participation.race_id].is_special);
        }
      }
    }
    if (!has_any) return part.base_rating;
    if (H.empty()) {
      return 0;
    }
    sort(H.rbegin(), H.rend());
    int initSize = H.size();
    int h = min<int>(H.size(), max<int>(2 * H.size() / 5, 4));
    if ((int)H.size() > h) H.resize(h);
    if (H.size() > 1 && !H[0].second) H.erase(H.begin());
    int sum = 0;
    for (int i = 0; i < (int)H.size(); i++) {
      sum += H[i].first;
    }
    int penalty = 2 * max(0, 4 - (int)initSize);
    if (has_dq) penalty = max(0, penalty - 2);
    return sum * (100 - penalty) / (100 * (int)H.size());
  };

  int knorm = 10000;
  for (int day = 0; day <= days; day++) {
    if (day % 365 == 0 && day != 0) {
      int max_rating = 0;
      for (int j = 0; j < (int)participants.size(); j++) {
        max_rating = max(max_rating, get_rating(j, day - 1));
      }
      if (max_rating == 0) knorm = 10000; else knorm = max_rating;
    }
    for (int race_id: races_by_day[day]) {
      auto& race = races[race_id];
      vector<pair<int, int>> ps;
      for (auto [part, id_in_part] : race.participants) {
        auto& participation = participants[part].participations[id_in_part];
        if (participation.result == 0) continue;
        ps.emplace_back(participation.result, -get_rating(part, day - 15));
      }
      sort(ps.begin(), ps.end());
      int ninfl = max(3, (2 * (int)ps.size()) / 3);
      if ((int)ps.size() < ninfl) {
        race.is_rated = 0;
        continue;
      }
      ll total = 0;
      for (int i = 0; i < ninfl; i++) {
        total += ps[i].first * -ps[i].second * 10000LL;
      }
      race.score = total  / (ninfl * knorm);
      race.is_rated = 1;
      for (auto [part, id_in_part] : race.participants) {
        auto& participation = participants[part].participations[id_in_part];
        if (participation.result == 0) {
          participation.performance = -1;
        } else {
          participation.performance = race.score / participation.result;
        }
        //eprintf("performance of %d in %d is %d\n", part, race_id, participation.performance);
      }
    }
  }
  return get_rating(0, days);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2 ) {
    vector<Participant> participants(n);
    vector<Race> races(m);
    for (int i = 0; i < n; i++) {
      scanf("%d", &participants[i].base_rating);
    }
    for (int i = 0; i < m; i++) {
      scanf("%d", &races[i].day);
    }
    for (int i = 0; i < m; i++) {
      scanf("%d", &races[i].is_special);
    }
    for (int i = 0; i < n; i++) {
      int k;
      scanf("%d", &k);
      participants[i].participations.resize(k);
      for (auto& p: participants[i].participations) {
        scanf("%d%d", &p.race_id, &p.result);
        --p.race_id;
      }
      ranges::sort(participants[i].participations, [](const Participation &a, const Participation &b) {
             return a.race_id < b.race_id;
           });
    }

    vector<int> result;

    for (int i = 0; i < (1 << participants[0].participations.size()); i++) {
      vector<Participant> participants_copy = participants;
      vector<Participation> nparts;
      for (int j = 0; j < (int)participants[0].participations.size(); j++) {
        if (i & (1 << j)) {
          nparts.push_back(participants[0].participations[j]);
        }
      }
      participants_copy[0].participations = nparts;
      int rating = emulate(participants_copy, races);
      //eprintf("mask=%d, rating=%d\n", i, rating);
      result.push_back(rating);
    }
    sort(result.rbegin(), result.rend());
    result.erase(unique(result.begin(), result.end()), result.end());
    printf("%d\n", (int)result.size());
    for (auto& x: result) {
      printf("%d\n", x);
    }
  }

  return 0;
}
