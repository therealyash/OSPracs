def SCAN(requests, initial_position, disk_size):
    # Sort the disk requests
    requests.sort()
    
    left = []
    right = []
    
    # Split the requests into left and right of the initial position
    for req in requests:
        if req < initial_position:
            left.append(req)
        else:
            right.append(req)
    
    total_distance = 0
    current_position = initial_position
    
    # Traverse the left side (reverse the list to simulate scanning in reverse order)
    left.reverse()
    for req in left:
        total_distance += abs(current_position - req)
        current_position = req
    
    # Traverse the right side
    for req in right:
        total_distance += abs(current_position - req)
        current_position = req
    
    return total_distance

def main():
    n = int(input("Enter the number of disk requests: "))
    requests = list(map(int, input("Enter the disk requests (track numbers): ").split()))
    initial_position = int(input("Enter the initial disk arm position: "))
    disk_size = int(input("Enter the disk size (maximum track number): "))
    
    total_distance = SCAN(requests, initial_position, disk_size)
    
    print(f"Total seek distance (SCAN): {total_distance}")

if __name__ == "__main__":
    main()
