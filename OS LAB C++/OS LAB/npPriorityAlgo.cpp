#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <climits>

using namespace std;

struct Process
{
    int id;
    int burstTime;
    int arrivalTime;
    int priority;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
    int remainingTime; // For Round-Robin
};

bool compareArrivalPriority(Process a, Process b)
{
    if (a.arrivalTime == b.arrivalTime)
        return a.priority < b.priority;
    return a.arrivalTime < b.arrivalTime;
}

void calculateTimes(vector<Process> &processes, int quantum)
{
    int n = processes.size();
    int currentTime = 0;
    int completedProcesses = 0;
    float totalWaitingTime = 0, totalTurnAroundTime = 0;
    vector<int> ganttChart;

    while (completedProcesses < n)
    {
        int idx = -1;
        int highestPriority = INT_MAX;

        // Select the process with the highest priority that has arrived
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
            {
                if (processes[i].priority < highestPriority)
                {
                    highestPriority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            // If processes with same priority, apply Round-Robin on them
            vector<int> samePriorityProcesses;
            for (int i = 0; i < n; i++)
            {
                if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && processes[i].priority == processes[idx].priority)
                {
                    samePriorityProcesses.push_back(i);
                }
            }

            if (samePriorityProcesses.size() > 1)
            {
                queue<int> rrQueue;
                for (int pid : samePriorityProcesses)
                    rrQueue.push(pid);

                while (!rrQueue.empty())
                {
                    int pid = rrQueue.front();
                    rrQueue.pop();
                    ganttChart.push_back(processes[pid].id);

                    if (processes[pid].remainingTime > quantum)
                    {
                        currentTime += quantum;
                        processes[pid].remainingTime -= quantum;
                        for (int i = 0; i < n; i++)
                        {
                            if (i != pid && processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
                            {
                                processes[i].waitingTime += quantum;
                            }
                        }
                        rrQueue.push(pid);
                    }
                    else
                    {
                        currentTime += processes[pid].remainingTime;
                        processes[pid].waitingTime = currentTime - processes[pid].arrivalTime - processes[pid].burstTime;
                        processes[pid].turnAroundTime = currentTime - processes[pid].arrivalTime;
                        processes[pid].completionTime = currentTime;
                        processes[pid].remainingTime = 0;
                        totalWaitingTime += processes[pid].waitingTime;
                        totalTurnAroundTime += processes[pid].turnAroundTime;
                        completedProcesses++;
                    }
                }
            }
            else
            {
                ganttChart.push_back(processes[idx].id);
                currentTime += processes[idx].remainingTime;
                processes[idx].waitingTime = currentTime - processes[idx].arrivalTime - processes[idx].burstTime;

                processes[idx].turnAroundTime = currentTime - processes[idx].arrivalTime;
                processes[idx].completionTime = currentTime;
                processes[idx].remainingTime = 0;
                totalWaitingTime += processes[idx].waitingTime;
                totalTurnAroundTime += processes[idx].turnAroundTime;
                completedProcesses++;
            }
        }
        else
        {
            currentTime++;
        }
    }

    cout << "\nGantt Chart:\n";
    for (int pid : ganttChart)
        cout << "| P" << pid << " ";
    cout << "|\n\n";

    cout << "Process\tArrival\tBurst\tPriority\tWaiting\tTurnaround\tCompletion\n";
    for (auto &p : processes)
    {
        cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.priority << "\t\t" << p.waitingTime << "\t\t" << p.turnAroundTime << "\t\t"
             << p.completionTime << endl;
    }

    cout << "\nAverage Waiting Time: " << totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << totalTurnAroundTime / n << endl;
}

int main()
{
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> processes(n);

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Enter arrival time, burst time, and priority for process " << processes[i].id << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnAroundTime = 0;
        processes[i].completionTime = 0;
    }

    cout << "Enter time quantum for Round-Robin scheduling: ";
    cin >> quantum;

    sort(processes.begin(), processes.end(), compareArrivalPriority);
    calculateTimes(processes, quantum);

    return 0;
}