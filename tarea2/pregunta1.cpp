#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> select_songs(vector<int> init, vector<int> duration){
    vector<pair<int, int>> finish_time(init.size(), make_pair(0,0));
    vector<int> selected;

    for (size_t song = 1; song < init.size(); song++) {
        finish_time[song] = make_pair(init[song] + duration[song], song);
    }

    sort(finish_time.begin(), finish_time.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.first < b.first;
    });

    selected.push_back(finish_time[1].second);
    int last_song = finish_time[1].first;  
    for (size_t i = 2; i < finish_time.size(); i++) {
        if (init[finish_time[i].second] >= last_song) {
            selected.push_back(finish_time[i].second);
            last_song = finish_time[i].first;
        }
    }
    return selected;
}

int main() {
    //Canciones                1  2  3  4
    vector<int> init     = {0, 1, 2, 1, 7};
    vector<int> duration = {0, 5, 4, 1, 2};
    vector<int> selected = select_songs(init, duration);
    cout << "Selected songs: {";
    for (int i : selected) {
        cout << i << " ";
    }
    cout << "}" << endl;
    return 0;
}