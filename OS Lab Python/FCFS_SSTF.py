# Function to simulate FCFS disk scheduling
def fcfs(requests, head):
    seek_operations = 0
    current_position = head

    print(f"\nFCFS Order: {current_position} ", end="")
    for request in requests:
        seek_operations += abs(request - current_position)
        current_position = request
        print(f"-> {current_position} ", end="")

    print(f"\nTotal Seek Time (FCFS): {seek_operations}")
    return seek_operations


# Function to simulate SSTF disk scheduling
def sstf(requests, head):
    seek_operations = 0
    current_position = head
    visited = [False] * len(requests)

    print(f"\nSSTF Order: {current_position} ", end="")
    for _ in range(len(requests)):
        closest_distance = float('inf')
        closest_index = -1

        for j in range(len(requests)):
            if not visited[j]:
                distance = abs(requests[j] - current_position)
                if distance < closest_distance:
                    closest_distance = distance
                    closest_index = j

        if closest_index != -1:
            seek_operations += closest_distance
            current_position = requests[closest_index]
            visited[closest_index] = True
            print(f"-> {current_position} ", end="")

    print(f"\nTotal Seek Time (SSTF): {seek_operations}")
    return seek_operations


def main():
    head = int(input("Enter the initial position of the disk head: "))
    num_requests = int(input("Enter the number of disk requests: "))

    requests = []
    print("Enter the disk requests:")
    for _ in range(num_requests):
        requests.append(int(input()))

    print("\n=== Disk Scheduling Algorithms ===")
    fcfs_seek = fcfs(requests, head)
    sstf_seek = sstf(requests, head)

    print("\nSummary:")
    print(f"Total Seek Time (FCFS): {fcfs_seek}")
    print(f"Total Seek Time (SSTF): {sstf_seek}")


if __name__ == "__main__":
    main()
