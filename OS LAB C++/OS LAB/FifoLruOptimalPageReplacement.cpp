#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>

using namespace std;

// Function to simulate FIFO page replacement
int fifoPageReplacement(vector<int> pages, int capacity) {
    vector<int> memory;
    int pageFaults = 0;

    for (int page : pages) {
        if (find(memory.begin(), memory.end(), page) == memory.end()) {
            pageFaults++;
            if (memory.size() == capacity) {
                memory.erase(memory.begin());
            }
            memory.push_back(page);
        }
    }
    return pageFaults;
}

// Function to simulate LRU page replacement
int lruPageReplacement(vector<int> pages, int capacity) {
    unordered_map<int, int> pageMap; // Page -> Last used index
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        if (pageMap.find(pages[i]) == pageMap.end() || pageMap[pages[i]] < 0) {
            pageFaults++;
            if (pageMap.size() == capacity) {
                // Find the least recently used page
                int lruPage = -1, lruIndex = INT_MAX;
                for (auto &[page, lastUsed] : pageMap) {
                    if (lastUsed >= 0 && lastUsed < lruIndex) {
                        lruIndex = lastUsed;
                        lruPage = page;
                    }
                }
                pageMap.erase(lruPage);
            }
        }
        pageMap[pages[i]] = i;
    }
    return pageFaults;
}

// Function to simulate Optimal page replacement
int optimalPageReplacement(vector<int> pages, int capacity) {
    vector<int> memory;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        if (find(memory.begin(), memory.end(), pages[i]) == memory.end()) {
            pageFaults++;
            if (memory.size() == capacity) {
                // Find the page not used for the longest time
                int farthest = i, pageToReplace = -1;
                for (int page : memory) {
                    auto it = find(pages.begin() + i + 1, pages.end(), page);
                    if (it == pages.end()) {
                        pageToReplace = page;
                        break;
                    }
                    if (it - pages.begin() > farthest) {
                        farthest = it - pages.begin();
                        pageToReplace = page;
                    }
                }
                auto it = find(memory.begin(), memory.end(), pageToReplace);
                if (it != memory.end()) {
                    memory.erase(it);
                }
            }
            memory.push_back(pages[i]);
        }
    }
    return pageFaults;
}

int main() {
    int capacity, n;
    cout << "Enter number of frames: ";
    cin >> capacity;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter the page reference string: ";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    cout << "\n1. FIFO\n2. LRU\n3. Optimal\nChoose the algorithm: ";
    int choice;
    cin >> choice;

    int pageFaults = 0;
    switch (choice) {
        case 1:
            pageFaults = fifoPageReplacement(pages, capacity);
            cout << "FIFO Page Faults: " << pageFaults << endl;
            break;
        case 2:
            pageFaults = lruPageReplacement(pages, capacity);
            cout << "LRU Page Faults: " << pageFaults << endl;
            break;
        case 3:
            pageFaults = optimalPageReplacement(pages, capacity);
            cout << "Optimal Page Faults: " << pageFaults << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
    }

    return 0;
}