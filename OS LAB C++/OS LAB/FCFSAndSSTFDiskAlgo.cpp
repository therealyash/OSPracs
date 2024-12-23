#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

int FCFS(const vector<int>& requests, int head) {
    int seek_operations = 0;
    int current_position = head;

    cout << "\nFCFS Order: " << current_position << " ";
    for (int request : requests) {
        seek_operations += abs(request - current_position);
        current_position = request;
        cout << "-> " << current_position << " ";
    }
    cout << "\nTotal Seek Time (FCFS): " << seek_operations << "\n";
    return seek_operations;
}

int SSTF(vector<int> requests, int head) {
    int seek_operations = 0;
    int current_position = head;
    vector<bool> visited(requests.size(), false);

    cout << "\nSSTF Order: " << current_position << " ";
    for (size_t i = 0; i < requests.size(); i++) {
        int closest_distance = INT_MAX;
        int closest_index = -1;

        for (size_t j = 0; j < requests.size(); j++) {
            if (!visited[j]) {
                int distance = abs(requests[j] - current_position);
                if (distance < closest_distance) {
                    closest_distance = distance;
                    closest_index = j;
                }
            }
        }

        if (closest_index != -1) {
            seek_operations += closest_distance;
            current_position = requests[closest_index];
            visited[closest_index] = true;
            cout << "-> " << current_position << " ";
        }
    }
    cout << "\nTotal Seek Time (SSTF): " << seek_operations << "\n";
    return seek_operations;
}

int main() {
    int num_requests, head;
    cout << "Enter the initial position of the disk head: ";
    cin >> head;

    cout << "Enter the number of disk requests: ";
    cin >> num_requests;

    vector<int> requests(num_requests);
    cout << "Enter the disk requests:\n";
    for (int i = 0; i < num_requests; i++) {
        cin >> requests[i];
    }

    cout << "\n=== Disk Scheduling Algorithms ===\n";
    int fcfs_seek = FCFS(requests, head);
    int sstf_seek = SSTF(requests, head);

    cout << "\nSummary:\n";
    cout << "Total Seek Time (FCFS): " << fcfs_seek << "\n";
    cout << "Total Seek Time (SSTF): " << sstf_seek << "\n";

    return 0;
}