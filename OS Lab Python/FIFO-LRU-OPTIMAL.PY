# Function to simulate FIFO page replacement
def fifo_page_replacement(pages, capacity):
    memory = []
    page_faults = 0

    for page in pages:
        if page not in memory:
            page_faults += 1
            if len(memory) == capacity:
                memory.pop(0)  # Remove the first element (FIFO)
            memory.append(page)
    
    return page_faults

# Function to simulate LRU page replacement
def lru_page_replacement(pages, capacity):
    page_map = {}  # Page -> Last used index
    page_faults = 0

    for i in range(len(pages)):
        if pages[i] not in page_map or page_map[pages[i]] < 0:
            page_faults += 1
            if len(page_map) == capacity:
                # Find the least recently used page
                lru_page, lru_index = -1, float('inf')
                for page, last_used in page_map.items():
                    if last_used >= 0 and last_used < lru_index:
                        lru_index = last_used
                        lru_page = page
                del page_map[lru_page]
        page_map[pages[i]] = i
    
    return page_faults

# Function to simulate Optimal page replacement
def optimal_page_replacement(pages, capacity):
    memory = []
    page_faults = 0

    for i in range(len(pages)):
        if pages[i] not in memory:
            page_faults += 1
            if len(memory) == capacity:
                # Find the page not used for the longest time
                farthest = i
                page_to_replace = -1
                for page in memory:
                    try:
                        next_use = pages.index(page, i + 1)
                    except ValueError:
                        next_use = float('inf')
                    
                    if next_use > farthest:
                        farthest = next_use
                        page_to_replace = page
                
                memory.remove(page_to_replace)
            memory.append(pages[i])
    
    return page_faults

def main():
    capacity = int(input("Enter number of frames: "))
    n = int(input("Enter number of pages: "))

    pages = list(map(int, input("Enter the page reference string: ").split()))

    print("\n1. FIFO\n2. LRU\n3. Optimal\nChoose the algorithm: ", end="")
    choice = int(input())

    if choice == 1:
        page_faults = fifo_page_replacement(pages, capacity)
        print(f"FIFO Page Faults: {page_faults}")
    elif choice == 2:
        page_faults = lru_page_replacement(pages, capacity)
        print(f"LRU Page Faults: {page_faults}")
    elif choice == 3:
        page_faults = optimal_page_replacement(pages, capacity)
        print(f"Optimal Page Faults: {page_faults}")
    else:
        print("Invalid choice.")

if __name__ == "__main__":
    main()
