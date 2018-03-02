#include <bits/stdc++.h>

using namespace std;

struct ride {
    pair<int, int> start;
    pair<int, int> end;
    int startT, endT, distance, index;
    int sort_by;
};

typedef pair<int, int> ii;
int rows, cols, vechs, rides, bonus, steps;
bool no_hurry = false;
map<int, vector<pair<int, ii>>> finishing_at;
map<int, vector<int>> assigns;
vector<ride> rides_vec;


int distance(ii from, ii to) {
    return abs(from.first - to.first) + abs(from.second - to.second);
}

void prep() {
    scanf("%d %d %d %d %d %d", &rows, &cols, &vechs, &rides, &bonus, &steps);
    for(int i = 0; i < rides; i++) {
        int a, b, x, y, s, f;
        scanf("%d %d %d %d %d %d", &a, &b, &x, &y, &s, &f);
        ride t;
        t.start = {a, b};
        t.end = {x, y};
        t.index = i;
        t.distance = abs(a - x) + abs(b - y);
        t.startT = s;
        t.endT = f;
        rides_vec.push_back(t);
    }
    for(int j = 0; j < vechs; j++) finishing_at[0].push_back({j, {0, 0}});
}

void print_sol() {
    for(int i = 0; i < vechs; i++) {
        cout << assigns[i].size();
        for(auto rr : assigns[i]) {
            printf(" %d", rr);
        }
        cout << endl;
    }
}

/*
// sorting function
bool myfunction (ride i,ride j) {
    if(no_hurry) {
        return i.distance < j.distance;
    } else {
        if(i.sort_by == j.sort_by) {
            return i.endT < j.endT;
            // return i.distance < j.distance;
        }
        return i.sort_by < j.sort_by;
    }
}
*/

int calc_score(ride this_ride, pair<int, ii> vec, int time_step) {
    int dist = distance(vec.second, this_ride.start);
    int score = 0;
    score += this_ride.distance*0.8;
    // if(dist + i <= this_ride.startT) score += 2*bonus;
    score -= dist*2;
    int waiting_time = this_ride.startT - (time_step + dist);
    // if(waiting_time < 0) waiting_time = 0;
    score -= 0.5*waiting_time;
    return score;
}

void solve() {
    for(int i = 0; i <= steps; i++) {
        if(rides_vec.size() == 0) break;
        for(auto vec : finishing_at[i]) {
            int best_ride = -1;
            int best_score = INT_MIN;
            int next_avail_at = 0;
            for(int k = 0; k < rides_vec.size(); k++) {
                auto this_ride = rides_vec[k];

                int dist = distance(vec.second, this_ride.start);
                int end_ride_at = max(i + dist, this_ride.startT) + this_ride.distance;
                // we're gonna miss the end of this ride, skip it
                if(end_ride_at > this_ride.endT) continue;
               
                int score = calc_score(this_ride, vec, i);
                if(score >= best_score) {
                    best_score = score;
                    best_ride = k;
                    next_avail_at = end_ride_at;
                }
            }
            // couldn't find good rides for this vech, make it avail at next timestep
            if(best_ride == -1) {
                finishing_at[i+1].push_back(vec);
                continue;
            }
            ride this_ride = rides_vec[best_ride];
            assigns[vec.first].push_back(this_ride.index);
            finishing_at[next_avail_at].push_back({vec.first, this_ride.end});
            rides_vec.erase(rides_vec.begin() + best_ride);
        }
    }
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);

    string inFileName = "./datasets/";
    string outFileName = "./output/";
    inFileName += argv[1];
    outFileName += argv[2];

    if(inFileName == "c_no_hurry.in") no_hurry = 1;
    freopen(inFileName.c_str(), "r", stdin);
    freopen(outFileName.c_str(), "w", stdout);
    
    prep();
    solve();
    print_sol();
}


