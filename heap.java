import java.util.Scanner;

public class HeapSortMenu {
    private int[] array;
    private int size;

    // Method to input array elements
    public void inputArray(Scanner sc) {
        System.out.print("Enter size of the array: ");
        size = sc.nextInt();
        array = new int[size];
        System.out.println("Enter " + size + " elements:");
        for (int i = 0; i < size; i++) {
            array[i] = sc.nextInt();
        }
    }

    // Heap Sort algorithm
    public void heapSort() {
        if (array == null) {
            System.out.println("Array not initialized. Please input array first.");
            return;
        }

        // Step 1: Build max heap
        for (int i = size / 2 - 1; i >= 0; i--)
            heapify(size, i);

        // Step 2: Extract elements from heap one by one
        for (int i = size - 1; i >= 0; i--) {
            swap(0, i);         // Move current root to end
            heapify(i, 0);      // Heapify reduced heap
        }

        System.out.println("Array has been sorted using Heap Sort.");
    }

    // Maintains max-heap property
    private void heapify(int heapSize, int rootIndex) {
        int largest = rootIndex;
        int left = 2 * rootIndex + 1;
        int right = 2 * rootIndex + 2;

        if (left < heapSize && array[left] > array[largest])
            largest = left;

        if (right < heapSize && array[right] > array[largest])
            largest = right;

        if (largest != rootIndex) {
            swap(rootIndex, largest);
            heapify(heapSize, largest);
        }
    }

    // Swap utility
    private void swap(int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    // Print array
    public void printArray() {
        if (array == null) {
            System.out.println("Array not initialized.");
            return;
        }

        System.out.print("Array: ");
        for (int num : array)
            System.out.print(num + " ");
        System.out.println();
    }

    // Main method with menu
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        HeapSortMenu hsm = new HeapSortMenu();
        int choice;

        do {
            System.out.println("\n--- Heap Sort Menu ---");
            System.out.println("1. Input Array");
            System.out.println("2. Display Array");
            System.out.println("3. Sort Using Heap Sort");
            System.out.println("4. Exit");
            System.out.print("Enter your choice: ");
            choice = sc.nextInt();

            switch (choice) {
                case 1:
                    hsm.inputArray(sc);
                    break;
                case 2:
                    hsm.printArray();
                    break;
                case 3:
                    hsm.heapSort();
                    break;
                case 4:
                    System.out.println("Exiting program.");
                    break;
                default:
                    System.out.println("Invalid choice. Try again.");
            }

        } while (choice != 4);

        sc.close();
    }
}
