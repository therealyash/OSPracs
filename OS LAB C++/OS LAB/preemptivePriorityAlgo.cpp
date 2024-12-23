#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

struct Process {
    int pid;
    int burstTime;
    int arrivalTime;
    int priority;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;

    Process(int p, int bt, int at, int pr)
        : pid(p), burstTime(bt), arrivalTime(at), priority(pr), 
          remainingTime(bt), completionTime(0), waitingTime(0), turnaroundTime(0) {}
};

bool compareByArrivalAndPriority(const Process& a, const Process& b) {
    if (a.arrivalTime == b.arrivalTime)
        return a.priority < b.priority; 
    return a.arrivalTime < b.arrivalTime;
}

void preemptivePriorityScheduling(vector<Process>& processes) {
    int time = 0, completedProcesses = 0, n = processes.size();
    vector<pair<int, int>> ganttChart;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

   
    sort(processes.begin(), processes.end(), compareByArrivalAndPriority);

    while (completedProcesses < n) {
        vector<Process*> availableProcesses;

        
        for (auto& process : processes) {
            if (process.arrivalTime <= time && process.remainingTime > 0) {
                availableProcesses.push_back(&process);
            }
        }

        if (availableProcesses.empty()) {
            ganttChart.push_back({-1, time}); 
            time++;
            continue;
        }

        
        sort(availableProcesses.begin(), availableProcesses.end(), [](Process* a, Process* b) {
            return a->priority < b->priority || (a->priority == b->priority && a->arrivalTime < b->arrivalTime);
        });
  
        Process* currentProcess = availableProcesses[0];
        vector<Process*> samePriorityProcesses;
       
        for (auto& process : availableProcesses) {
            if (process->priority == currentProcess->priority) {
                samePriorityProcesses.push_back(process);
            }
        }

        if (samePriorityProcesses.size() > 1) {
            
            int timeQuantum = 1;
            while (!samePriorityProcesses.empty()) {
                for (auto& process : samePriorityProcesses) {
                    ganttChart.push_back({process->pid, time});
                    process->remainingTime -= timeQuantum;
                    time += timeQuantum;

                    if (process->remainingTime <= 0) {
                        process->completionTime = time;
                        completedProcesses++;
                        process->turnaroundTime = process->completionTime - process->arrivalTime;
                        process->waitingTime = process->turnaroundTime - process->burstTime;
                        totalWaitingTime += process->waitingTime;
                        totalTurnaroundTime += process->turnaroundTime;
                    }
                    if (completedProcesses == n) break;
                }
                
                if (completedProcesses == n) break;
            }
        } else {
            
            ganttChart.push_back({currentProcess->pid, time});
            currentProcess->remainingTime--;
            time++;

            if (currentProcess->remainingTime == 0) {
                currentProcess->completionTime = time;
                completedProcesses++;
                currentProcess->turnaroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
                currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;
                totalWaitingTime += currentProcess->waitingTime;
                totalTurnaroundTime += currentProcess->turnaroundTime;
            }
        }
    }

    
    cout << "\nGantt Chart:\n";
    for (auto& entry : ganttChart) {
        if (entry.first == -1) cout << "Idle | ";
        else cout << "P" << entry.first << " | ";
    }
    cout << "\n";  
    cout << "\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n";
    for (auto& process : processes) {
        cout << "P" << process.pid << "\t" << process.arrivalTime << "\t\t" << process.burstTime
             << "\t\t" << process.priority << "\t\t" << process.waitingTime
             << "\t\t" << process.turnaroundTime << "\n";
    }

    
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << totalTurnaroundTime / n << endl;
}

int main() {
    int numProcesses;
    cout << "Enter number of processes: ";
    cin >> numProcesses;

    vector<Process> processes;
    for (int i = 0; i < numProcesses; i++) {
        int burstTime, arrivalTime, priority;
        cout << "Enter Burst Time for Process " << i + 1 << ": ";
        cin >> burstTime;
        cout << "Enter Arrival Time for Process " << i + 1 << ": ";
        cin >> arrivalTime;
        cout << "Enter Priority for Process " << i + 1 << " (lower number = higher priority): ";
        cin >> priority;
        processes.emplace_back(i + 1, burstTime, arrivalTime, priority);
    }
    preemptivePriorityScheduling(processes);
    return 0;
}