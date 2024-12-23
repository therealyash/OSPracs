class Process:
    def __init__(self, id, arrival_time, burst_time):
        self.id = id
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.remaining_time = burst_time
        self.waiting_time = 0
        self.turnaround_time = 0


def get_processes():
    processes = []
    n = int(input("Enter number of processes: "))
    for i in range(n):
        arrival_time = int(input(f"Enter arrival time of process {i + 1}: "))
        burst_time = int(input(f"Enter CPU burst time of process {i + 1}: "))
        processes.append(Process(i + 1, arrival_time, burst_time))
    return processes


def srtf_scheduling(processes):
    n = len(processes)
    gantt_chart = []
    completed = 0
    current_time = 0

    while completed < n:
        idx = -1
        min_remaining_time = float('inf')

        for i in range(n):
            if processes[i].arrival_time <= current_time and processes[i].remaining_time > 0:
                if processes[i].remaining_time < min_remaining_time:
                    min_remaining_time = processes[i].remaining_time
                    idx = i

        if idx != -1:
            gantt_chart.append(processes[idx].id)
            processes[idx].remaining_time -= 1

            if processes[idx].remaining_time == 0:
                completed += 1
                finish_time = current_time + 1
                processes[idx].turnaround_time = finish_time - processes[idx].arrival_time
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time

        current_time += 1

    print("Gantt Chart: ", end="")
    print(" ".join(f"P{id}" for id in gantt_chart))

    print("\nProcess\tWaiting Time\tTurnaround Time")
    for process in processes:
        print(f"P{process.id}\t{process.waiting_time}\t\t{process.turnaround_time}")

    avg_waiting_time = sum(process.waiting_time for process in processes) / n
    avg_turnaround_time = sum(process.turnaround_time for process in processes) / n

    print(f"\nAverage Waiting Time: {avg_waiting_time:.2f}")
    print(f"Average Turnaround Time: {avg_turnaround_time:.2f}")


if __name__ == "__main__":
    processes = get_processes()
    srtf_scheduling(processes)
class Process:
    def __init__(self, id, arrival_time, burst_time):
        self.id = id
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.remaining_time = burst_time
        self.waiting_time = 0
        self.turnaround_time = 0


def get_processes():
    processes = []
    n = int(input("Enter number of processes: "))
    for i in range(n):
        arrival_time = int(input(f"Enter arrival time of process {i + 1}: "))
        burst_time = int(input(f"Enter CPU burst time of process {i + 1}: "))
        processes.append(Process(i + 1, arrival_time, burst_time))
    return processes


def srtf_scheduling(processes):
    n = len(processes)
    gantt_chart = []
    completed = 0
    current_time = 0

    while completed < n:
        idx = -1
        min_remaining_time = float('inf')

        for i in range(n):
            if processes[i].arrival_time <= current_time and processes[i].remaining_time > 0:
                if processes[i].remaining_time < min_remaining_time:
                    min_remaining_time = processes[i].remaining_time
                    idx = i

        if idx != -1:
            gantt_chart.append(processes[idx].id)
            processes[idx].remaining_time -= 1

            if processes[idx].remaining_time == 0:
                completed += 1
                finish_time = current_time + 1
                processes[idx].turnaround_time = finish_time - processes[idx].arrival_time
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time

        current_time += 1

    print("Gantt Chart: ", end="")
    print(" ".join(f"P{id}" for id in gantt_chart))

    print("\nProcess\tWaiting Time\tTurnaround Time")
    for process in processes:
        print(f"P{process.id}\t{process.waiting_time}\t\t{process.turnaround_time}")

    avg_waiting_time = sum(process.waiting_time for process in processes) / n
    avg_turnaround_time = sum(process.turnaround_time for process in processes) / n

    print(f"\nAverage Waiting Time: {avg_waiting_time:.2f}")
    print(f"Average Turnaround Time: {avg_turnaround_time:.2f}")


if __name__ == "__main__":
    processes = get_processes()
    srtf_scheduling(processes)
