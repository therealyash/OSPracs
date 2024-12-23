#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int disk_size = 200;


void CSCAN(vector<int> arr, int head)
{
    int seek_count = 0;
    int distance, cur_track;
    vector<int> left, right;
    vector<int> seek_sequence;

    left.push_back(0);
    right.push_back(disk_size - 1);

    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < head)
            left.push_back(arr[i]);
        if (arr[i] > head)
            right.push_back(arr[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int i = 0; i < right.size(); i++) {
        cur_track = right[i];
        seek_sequence.push_back(cur_track);

        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }

    head = 0;
    seek_count += (disk_size - 1); 

    for (int i = 0; i < left.size(); i++) {
        cur_track = left[i];
        seek_sequence.push_back(cur_track);
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }

    cout << "Total number of seek operations = "
         << seek_count << endl;

    cout << "Seek Sequence is:" << endl;
    for (int i = 0; i < seek_sequence.size(); i++) {
        cout << seek_sequence[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n, head;

    cout << "Enter the number of requests: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the requests (space-separated): ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter the initial position of the head: ";
    cin >> head;

    CSCAN(arr, head);

    return 0;
}