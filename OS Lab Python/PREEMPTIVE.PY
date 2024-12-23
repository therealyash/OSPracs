from collections import deque
from operator import itemgetter


class Process:
    def __init__(self, pid, burst_time, arrival_time, priority):
        self.pid = pid
        self.burst_time = burst_time
        self.arrival_time = arrival_time
        self.priority = priority
        self.remaining_time = burst_time
        self.completion_time = 0
        self.waiting_time = 0
        self.turnaround_time = 0


def compare_by_arrival_and_priority(process):
    return process.arrival_time, process.priority


def preemptive_priority_scheduling(processes):
    time = 0
    completed_processes = 0
    n = len(processes)
    gantt_chart = []
    total_waiting_time = 0
    total_turnaround_time = 0

    processes.sort(key=compare_by_arrival_and_priority)

    while completed_processes < n:
        available_processes = [process for process in processes if
                               process.arrival_time <= time and process.remaining_time > 0]

        if not available_processes:
            gantt_chart.append((-1, time))
            time += 1
            continue

        available_processes.sort(key=lambda p: (p.priority, p.arrival_time))

        current_process = available_processes[0]
        same_priority_processes = [process for process in available_processes if
                                   process.priority == current_process.priority]

        if len(same_priority_processes) > 1:
            time_quantum = 1
            while same_priority_processes:
                for process in same_priority_processes:
                    gantt_chart.append((process.pid, time))
                    process.remaining_time -= time_quantum
                    time += time_quantum

                    if process.remaining_time <= 0:
                        process.completion_time = time
                        completed_processes += 1
                        process.turnaround_time = process.completion_time - process.arrival_time
                        process.waiting_time = process.turnaround_time - process.burst_time
                        total_waiting_time += process.waiting_time
                        total_turnaround_time += process.turnaround_time

                    if completed_processes == n:
                        break
                if completed_processes == n:
                    break
        else:
            gantt_chart.append((current_process.pid, time))
            current_process.remaining_time -= 1
            time += 1

            if current_process.remaining_time == 0:
                current_process.completion_time = time
                completed_processes += 1
                current_process.turnaround_time = current_process.completion_time - current_process.arrival_time
                current_process.waiting_time = current_process.turnaround_time - current_process.burst_time
                total_waiting_time += current_process.waiting_time
                total_turnaround_time += current_process.turnaround_time

    print("\nGantt Chart:")

    # Print process IDs at the top of the Gantt chart
    print(" |", end=" ")
    for entry in gantt_chart:
        if entry[0] == -1:
            print("Idle", end=" | ")
        else:
            print(f"P{entry[0]}", end=" | ")
    print()

    # Print the times below the process IDs
    time = 0
    print("  ", end="")
    for entry in gantt_chart:
        if entry[0] == -1:
            print("    ", end=" ")  # Adjust spacing for Idle
        else:
            print(f"{time: <4}", end="")  # Print time, formatted for alignment
            time += 1  # Increment time for each step in Gantt chart
    print("\n")

    # Print process details
    print("Process\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time")
    for process in processes:
        print(
            f"P{process.pid}\t{process.arrival_time}\t\t{process.burst_time}\t\t{process.priority}\t\t{process.waiting_time}\t\t{process.turnaround_time}")

    print(f"\nAverage Waiting Time: {total_waiting_time / n:.2f}")
    print(f"Average Turnaround Time: {total_turnaround_time / n:.2f}")


def main():
    num_processes = int(input("Enter number of processes: "))
    processes = []

    for i in range(num_processes):
        burst_time = int(input(f"Enter Burst Time for Process {i + 1}: "))
        arrival_time = int(input(f"Enter Arrival Time for Process {i + 1}: "))
        priority = int(input(f"Enter Priority for Process {i + 1} (lower number = higher priority): "))
        processes.append(Process(i + 1, burst_time, arrival_time, priority))

    preemptive_priority_scheduling(processes)


if __name__ == "__main__":
    main()
