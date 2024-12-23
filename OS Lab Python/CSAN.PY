def CSCAN(arr, head, disk_size=200):
    seek_count = 0
    distance = 0
    cur_track = 0
    left = [0]
    right = [disk_size - 1]
    seek_sequence = []

    # Split the requests into left and right of the head
    for i in arr:
        if i < head:
            left.append(i)
        elif i > head:
            right.append(i)

    # Sort left and right arrays
    left.sort()
    right.sort()

    # Traverse the right side
    for i in right:
        cur_track = i
        seek_sequence.append(cur_track)
        distance = abs(cur_track - head)
        seek_count += distance
        head = cur_track

    # Move head to the beginning (0)
    head = 0
    seek_count += (disk_size - 1)  # The head moves from the end of the disk to the start

    # Traverse the left side
    for i in left:
        cur_track = i
        seek_sequence.append(cur_track)
        distance = abs(cur_track - head)
        seek_count += distance
        head = cur_track

    print(f"Total number of seek operations = {seek_count}")
    print("Seek Sequence is:")
    print(" ".join(map(str, seek_sequence)))


def main():
    n = int(input("Enter the number of requests: "))
    arr = list(map(int, input("Enter the requests (space-separated): ").split()))
    head = int(input("Enter the initial position of the head: "))
    CSCAN(arr, head)

if __name__ == "__main__":
    main()
