
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int SCAN(vector<int>& requests, int initial_position, int disk_size) {
    sort(requests.begin(), requests.end());
    
    vector<int> left, right;
    for (int req : requests) {
        if (req < initial_position) left.push_back(req);
        else right.push_back(req);
    }
    
    int total_distance = 0;
    int current_position = initial_position;
    
    reverse(left.begin(), left.end()); 
    for (int req : left) {
        total_distance += abs(current_position - req);
        current_position = req;
    }
    
    for (int req : right) {
        total_distance += abs(current_position - req);
        current_position = req;
    }
    
    return total_distance;
}

int main() {
    int n, initial_position, disk_size;

    cout << "Enter the number of disk requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the disk requests (track numbers): ";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }

    cout << "Enter the initial disk arm position: ";
    cin >> initial_position;

    cout << "Enter the disk size (maximum track number): ";
    cin >> disk_size;

    int total_distance = SCAN(requests, initial_position, disk_size);
    
    cout << "Total seek distance (SCAN): " << total_distance << endl;
    return 0;
}