#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits> 

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

void getProcesses(vector<Process>& processes) {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    processes.resize(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time of process " << (i + 1) << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter CPU burst time of process " << (i + 1) << ": ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }
}

void srtfScheduling(vector<Process>& processes) {
    int n = processes.size();
    vector<int> ganttChart;
    int completed = 0, currentTime = 0;

    while (completed < n) {
        int idx = -1;
        int minRemainingTime = INT_MAX;

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime < minRemainingTime) {
                    minRemainingTime = processes[i].remainingTime;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            ganttChart.push_back(processes[idx].id);
            processes[idx].remainingTime--;

            if (processes[idx].remainingTime == 0) {
                completed++;
                int finishTime = currentTime + 1;
                processes[idx].turnaroundTime = finishTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            }
        }

        currentTime++;
    }
    cout << "Gantt Chart: ";
    for (int id : ganttChart) {
        cout << "P" << id << " ";
    }
    cout << endl;

    cout << "\nProcess\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        cout << "P" << process.id << "\t" << process.waitingTime << "\t\t" << process.turnaroundTime << endl;
    }

    double avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (const auto& process : processes) {
        avgWaitingTime += process.waitingTime;
        avgTurnaroundTime += process.turnaroundTime;
    }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
}

int main() {
    vector<Process> processes;
    getProcesses(processes);
    srtfScheduling(processes);
    return 0;
}
