# Python3 program for implementation of RR scheduling with Gantt Chart

# Function to find the waiting time for all processes
def findWaitingTime(processes, n, bt, wt, quantum):
    rem_bt = [0] * n  # Remaining burst time
    gantt_chart = []  # To store the Gantt chart sequence
    times = []        # To store the times at each step

    # Copy the burst time into rem_bt[]
    for i in range(n):
        rem_bt[i] = bt[i]
    t = 0  # Current time

    # Keep traversing processes in round-robin manner until all are done
    while True:
        done = True

        for i in range(n):
            if rem_bt[i] > 0:
                done = False  # There is a pending process

                if rem_bt[i] > quantum:
                    t += quantum
                    rem_bt[i] -= quantum
                    gantt_chart.append(f"P{processes[i]}")
                    times.append(t)
                else:
                    t += rem_bt[i]
                    wt[i] = t - bt[i]
                    rem_bt[i] = 0
                    gantt_chart.append(f"P{processes[i]}")
                    times.append(t)

        if done:
            break

    return gantt_chart, times

# Function to calculate turn around time
def findTurnAroundTime(processes, n, bt, wt, tat):
    for i in range(n):
        tat[i] = bt[i] + wt[i]

# Function to calculate average waiting and turn-around times and Gantt chart
def findavgTime(processes, n, bt, quantum):
    wt = [0] * n
    tat = [0] * n

    # Find waiting time of all processes
    gantt_chart, times = findWaitingTime(processes, n, bt, wt, quantum)

    # Find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat)

    # Display processes along with all details
    print("Processes    Burst Time     Waiting Time    Turn-Around Time")
    total_wt = 0
    total_tat = 0
    for i in range(n):
        total_wt += wt[i]
        total_tat += tat[i]
        print(f" {processes[i]} \t\t {bt[i]} \t\t {wt[i]} \t\t {tat[i]}")

    print("\nAverage waiting time = %.5f" % (total_wt / n))
    print("Average turn around time = %.5f" % (total_tat / n))

    # Display Gantt chart
    print("\nGantt Chart:")
    print(" | ".join(gantt_chart))
    print(" ".join(["---"] * len(gantt_chart)))
    print(" " + "   ".join(map(str, [0] + times)))

# Driver code
if __name__ == "__main__":
    # Process id's
    proc = [1, 2, 3]
    n = 3

    # Burst time of all processes
    burst_time = [10, 5, 8]

    # Time quantum
    quantum = 2
    findavgTime(proc, n, burst_time, quantum)
