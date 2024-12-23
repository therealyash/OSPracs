#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

void calculateTimes(vector<Process>& processes, int quantum) {
    queue<int> readyQueue;
    vector<int> ganttChart;
    int currentTime = 0;
    int n = processes.size();
    int completed = 0;
    vector<bool> inQueue(n, false);
    
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && !inQueue[i]) {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }

        if (!readyQueue.empty()) {
            int currentProcessIndex = readyQueue.front();
            readyQueue.pop();
            ganttChart.push_back(processes[currentProcessIndex].id);

            if (processes[currentProcessIndex].remainingTime > quantum) {
                currentTime += quantum;
                processes[currentProcessIndex].remainingTime -= quantum;
            } else {
                currentTime += processes[currentProcessIndex].remainingTime;
                processes[currentProcessIndex].remainingTime = 0;
                completed++;
                processes[currentProcessIndex].turnaroundTime = currentTime - processes[currentProcessIndex].arrivalTime;
                processes[currentProcessIndex].waitingTime = processes[currentProcessIndex].turnaroundTime - processes[currentProcessIndex].burstTime;
            }

            for (int i = 0; i < n; i++) {
                if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && !inQueue[i]) {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }

            if (processes[currentProcessIndex].remainingTime > 0) {
                readyQueue.push(currentProcessIndex);
            }
        } else {
            currentTime++;
        }
    }

    cout << "\nGantt Chart: ";
    for (int id : ganttChart) {
        cout << "P" << id << " ";
    }
    cout << endl;
}

void printTimes(const vector<Process>& processes) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int n = processes.size();

    cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (const Process& p : processes) {
        cout << "P" << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime
             << "\t\t" << p.waitingTime << "\t\t" << p.turnaroundTime << endl;
        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
    }

    double avgWaitingTime = (double)totalWaitingTime / n;
    double avgTurnaroundTime = (double)totalTurnaroundTime / n;

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
}

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time of process P" << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time of process P" << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }

    cout << "Enter time quantum: ";
    cin >> quantum;

    calculateTimes(processes, quantum);
    printTimes(processes);

    return 0;
}