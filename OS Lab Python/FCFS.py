class Process:
    def __init__(self, id, arrival_time, burst_time):
        self.id = id
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.waiting_time = 0
        self.turnaround_time = 0
        self.completion_time = 0


class FCFS:
    def __init__(self):
        self.processes = []

    def input_processes(self):
        n = int(input("Enter the number of processes: "))

        for i in range(n):
            id = input(f"Enter process ID for process {i + 1}: ")
            arrival_time = int(input(f"Enter arrival time for process {id}: "))
            burst_time = int(input(f"Enter burst time for process {id}: "))
            self.processes.append(Process(id, arrival_time, burst_time))

    def calculate_fcfs(self):
        self.processes.sort(key=lambda x: x.arrival_time)

        self.processes[0].completion_time = self.processes[0].arrival_time + self.processes[0].burst_time
        for i in range(1, len(self.processes)):
            self.processes[i].completion_time = max(
                self.processes[i - 1].completion_time, self.processes[i].arrival_time
            ) + self.processes[i].burst_time

        for process in self.processes:
            process.turnaround_time = process.completion_time - process.arrival_time
            process.waiting_time = process.turnaround_time - process.burst_time

    def display_results(self):
        print("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time")
        total_waiting_time = 0
        total_turnaround_time = 0

        for process in self.processes:
            print(
                f"{process.id}\t{process.arrival_time}\t\t{process.burst_time}\t\t{process.waiting_time}\t\t{process.turnaround_time}")
            total_waiting_time += process.waiting_time
            total_turnaround_time += process.turnaround_time

        avg_waiting_time = total_waiting_time / len(self.processes)
        avg_turnaround_time = total_turnaround_time / len(self.processes)

        print(f"\nAverage Waiting Time: {avg_waiting_time:.2f}")
        print(f"Average Turnaround Time: {avg_turnaround_time:.2f}")

    def print_gantt_chart(self):
        print("Gantt Chart:")
        # Print process labels (| P1 | P2 | ...)
        for process in self.processes:
            print(f"| {process.id} ", end="")
        print("|")

        # Print timeline below process labels
        print("0", end="")
        for process in self.processes:
            print(f"   {process.completion_time} ", end="")
        print()


if __name__ == "__main__":
    scheduler = FCFS()
    scheduler.input_processes()
    scheduler.calculate_fcfs()
    scheduler.display_results()
    scheduler.print_gantt_chart()
