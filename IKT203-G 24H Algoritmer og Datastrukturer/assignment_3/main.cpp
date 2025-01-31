#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

// Function to swap two elements
template <typename T>
void swapElements(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Function to partition the array using a random pivot
template <typename T>
int randomizedPartition(std::vector<T>& arr, int low, int high) {
    // Generate a random pivot index between low and high
    int pivotIndex = low + rand() % (high - low + 1);
    // Swap the pivot with the last element
    swapElements(arr[pivotIndex], arr[high]);
    T pivot = arr[high];

    int i = low - 1; // Index of smaller element

    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swapElements(arr[i], arr[j]);
        }
    }
    swapElements(arr[i + 1], arr[high]);
    return (i + 1);
}

// Randomized Quick Sort function
template <typename T>
void randomizedQuickSort(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = randomizedPartition(arr, low, high);

        // Separately sort elements before and after partition
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

// Function to display the array
template <typename T>
void displayArray(const std::vector<T>& arr) {
    std::cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i != arr.size() -1)
            std::cout << ", ";
    }
    std::cout << "]\n";
}

// Function to validate and convert input to double
bool getInputElement(const std::string& input, double& element) {
    std::istringstream iss(input);
    iss >> element;
    // Check if the entire input was consumed and no error occurred
    return !iss.fail() && iss.eof();
}

int main() {
    srand(time(0));

    std::cout << "Randomized Quick Sort Implementation\n";
    std::cout << "Enter elements (integers or floating-point) separated by spaces:\n";

    std::vector<double> arr;
    std::string inputLine;

    // Read a full line of input
    std::getline(std::cin, inputLine);
    std::istringstream iss(inputLine);
    std::string token;
    double number;

    // Parse each token and convert to double
    while (iss >> token) {
        if (!getInputElement(token, number)) {
            std::cerr << "Error: Invalid input \"" << token << "\".\n";
            return 1;
        }
        arr.push_back(number);
    }

    if (arr.empty()) {
        std::cout << "The array is empty. Nothing to sort.\n";
        return 0;
    }

    std::cout << "Unsorted Array: ";
    displayArray(arr);

    // Sort the array using Randomized Quick Sort
    randomizedQuickSort(arr, 0, arr.size() - 1);

    std::cout << "The sorted array is: ";
    displayArray(arr);

    return 0;
}
