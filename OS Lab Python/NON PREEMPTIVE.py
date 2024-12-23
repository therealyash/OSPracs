from queue import Queue

class Process:
    def __init__(self, pid, arrival_time, burst_time, priority):
        self.id = pid
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.priority = priority
        self.remaining_time = burst_time
        self.waiting_time = 0
        self.turn_around_time = 0
        self.completion_time = 0

def compare_arrival_priority(a, b):
    if a.arrival_time == b.arrival_time:
        return a.priority - b.priority
    return a.arrival_time - b.arrival_time

def calculate_times(processes, quantum):
    n = len(processes)
    current_time = 0
    completed_processes = 0
    total_waiting_time = 0
    total_turn_around_time = 0
    gantt_chart = []

    while completed_processes < n:
        idx = -1
        highest_priority = float('inf')

        for i in range(n):
            if processes[i].arrival_time <= current_time and processes[i].remaining_time > 0:
                if processes[i].priority < highest_priority:
                    highest_priority = processes[i].priority
                    idx = i

        if idx != -1:
            same_priority_processes = [i for i in range(n) if \
                                       processes[i].arrival_time <= current_time and \
                                       processes[i].remaining_time > 0 and \
                                       processes[i].priority == processes[idx].priority]

            if len(same_priority_processes) > 1:
                rr_queue = Queue()
                for pid in same_priority_processes:
                    rr_queue.put(pid)

                while not rr_queue.empty():
                    pid = rr_queue.get()
                    gantt_chart.append(processes[pid].id)

                    if processes[pid].remaining_time > quantum:
                        current_time += quantum
                        processes[pid].remaining_time -= quantum
                        for i in range(n):
                            if i != pid and processes[i].arrival_time <= current_time and processes[i].remaining_time > 0:
                                processes[i].waiting_time += quantum
                        rr_queue.put(pid)
                    else:
                        current_time += processes[pid].remaining_time
                        processes[pid].waiting_time = current_time - processes[pid].arrival_time - processes[pid].burst_time
                        processes[pid].turn_around_time = current_time - processes[pid].arrival_time
                        processes[pid].completion_time = current_time
                        processes[pid].remaining_time = 0
                        total_waiting_time += processes[pid].waiting_time
                        total_turn_around_time += processes[pid].turn_around_time
                        completed_processes += 1
            else:
                gantt_chart.append(processes[idx].id)
                current_time += processes[idx].remaining_time
                processes[idx].waiting_time = current_time - processes[idx].arrival_time - processes[idx].burst_time
                processes[idx].turn_around_time = current_time - processes[idx].arrival_time
                processes[idx].completion_time = current_time
                processes[idx].remaining_time = 0
                total_waiting_time += processes[idx].waiting_time
                total_turn_around_time += processes[idx].turn_around_time
                completed_processes += 1
        else:
            current_time += 1

    print("\nGantt Chart:")
    # Print the Gantt chart labels (P1, P2, ...)
    print(" | ", end="")
    for pid in gantt_chart:
        print(f"P{pid} | ", end="")
    print()

    # Print the corresponding time points directly below each process
    time = 0
    print("0", end="")
    for pid in gantt_chart:
        time += processes[pid - 1].burst_time  # Increment time by the burst time of each process
        print(f"   {time} ", end="")
    print()

    print("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\tCompletion")
    for p in processes:
        print(f"P{p.id}\t{p.arrival_time}\t{p.burst_time}\t{p.priority}\t\t{p.waiting_time}\t\t{p.turn_around_time}\t\t{p.completion_time}")

    print(f"\nAverage Waiting Time: {total_waiting_time / n}")
    print(f"Average Turnaround Time: {total_turn_around_time / n}")

def main():
    n = int(input("Enter number of processes: "))
    processes = []

    for i in range(n):
        arrival_time, burst_time, priority = map(int, input(f"Enter arrival time, burst time, and priority for process {i + 1}: ").split())
        processes.append(Process(i + 1, arrival_time, burst_time, priority))

    quantum = int(input("Enter time quantum for Round-Robin scheduling: "))

    processes.sort(key=lambda p: (p.arrival_time, p.priority))
    calculate_times(processes, quantum)

if __name__ == "__main__":
    main()
