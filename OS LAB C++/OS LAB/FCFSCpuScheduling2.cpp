#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Process {
public:

    string id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
};

class FCFS {
private:
    vector<Process> processes;
    int n;

public:
    void inputProcesses() {
        cout << "Enter the number of processes: ";
        cin >> n;
        processes.resize(n);

        for (int i = 0; i < n; ++i) {
            cout << "Enter process ID for process " << i + 1 << ": ";
            cin >> processes[i].id;
            cout << "Enter arrival time for process " << processes[i].id << ": ";
            cin >> processes[i].arrivalTime;
            cout << "Enter burst time for process " << processes[i].id << ": ";
            cin >> processes[i].burstTime;
        }
    }

    void calculateFCFS() {
        processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;
        for (int i = 1; i < n; ++i) {
            processes[i].completionTime = max(processes[i - 1].completionTime, processes[i].arrivalTime) + processes[i].burstTime;
        }

        for (int i = 0; i < n; ++i) {
            processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
            processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        }
    }

    void displayResults() {
        cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
        double totalWaitingTime = 0, totalTurnaroundTime = 0;
        for (const auto& process : processes) {
            cout << process.id << "\t" << process.arrivalTime << "\t\t"
                 << process.burstTime << "\t\t" << process.waitingTime << "\t\t"
                 << process.turnaroundTime << endl;
            totalWaitingTime += process.waitingTime;
            totalTurnaroundTime += process.turnaroundTime;
        }

        double avgWaitingTime = totalWaitingTime / n;
        double avgTurnaroundTime = totalTurnaroundTime / n;

        cout << fixed << setprecision(2);
        cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
        cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
    }

    void printGanttChart() {
        cout << "Gantt Chart:\n";
        for (const auto& process : processes) {
            cout << " " << process.id;
        }
        cout << endl;

        cout << "0";
        for (const auto& process : processes) {
            cout << " -> " << process.completionTime;
        }
        cout << endl;
    }
};

int main() {
    FCFS scheduler;
    scheduler.inputProcesses();
    scheduler.calculateFCFS();
    scheduler.displayResults();
    scheduler.printGanttChart();
    return 0;
}
