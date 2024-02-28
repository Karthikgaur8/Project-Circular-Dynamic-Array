
#include <iostream>
#include <stdexcept>
#include <climits>
#include <cstdlib>

/*To do: 
1) Develop edge test cases to break the project
2) change from Typename T to elmtype
*/


template <typename T> 
class CircularDynamicArray {
private:
    T* array;
    int _capacity;
    int size;
    int front;
    int back;

  void resize(int new_capacity) {
    T* new_array = new T[new_capacity];
    int current = front;
    int newIndex = 0;

    // Copy elements from the current array to the new array
    for (int i = 0; i < size; ++i) {
        // Ensure proper wrapping around the array
        current = (front + i) % _capacity;

        // Copy non-sentinel elements to the new array
        if (array[current] != -1) {
            new_array[newIndex++] = array[current];
        }
    }

    delete[] array; // Free memory of the old array
    array = new_array; // Update to the new array
    _capacity = new_capacity; // Update capacity
    front = 0; // Reset front to start of the resized array
    back = newIndex - 1; // Update back to reflect the new size
    size = newIndex; // Update size to reflect the new size after dropping sentinel elements
}

  
   

    

public:
    CircularDynamicArray(): _capacity(2), size(0), front(0), back(-1){
        array= new T[_capacity];
    }
    
    CircularDynamicArray(int initial_capacity) : _capacity(initial_capacity), size(initial_capacity), front(0), back(initial_capacity-1) {
        array = new T[_capacity];
    }

    ~CircularDynamicArray() {
        delete[] array;
    }
//copy constructor
    CircularDynamicArray(const CircularDynamicArray& other) {
    _capacity = other._capacity;
    size = other.size;
    front = other.front;
    back = other.back;
    array = new T[_capacity];
    for (int i = 0; i < size; ++i) {
        array[(front +i)%_capacity] = other.array[(front +i)%_capacity]; // array[i]= other.array[i];
                                                                        //since its circular dynamic doesn't start at index 0 necessarily
    }
}

//copy assignment operator
CircularDynamicArray& operator=(const CircularDynamicArray& other) {
    if (this != &other) {
        delete[] array;
        _capacity = other._capacity;
        size = other.size;
        front = other.front;
        back = other.back;
        array = new T[_capacity];
        for (int i = 0; i < size; ++i) {
           array[(front +i)%_capacity] = other.array[(front +i)%_capacity]; // array[i] = other.array[i];
        }
    }
    return *this;
}

int f ()const{
    return front;
}
int b() const {
    return back;
}

//need to redo the add/del based on circular dynamic array (nature discussed in class)

//when added at end, back moves to point at the newly added object
    void addEnd(T item) {
    if (size == _capacity) resize(_capacity * 2);
    back = (front + size - 1) % _capacity; // Update back to point to the last element
    back = (back + 1) % _capacity; // Move back to the next circular index
    array[back] = item; // Insert item at the new back position
    ++size;
}

//front when added moves ahead to accomodate the item
    void addFront(T item) {
        if (size == _capacity) resize(_capacity * 2); /*resizing if needed*/
        front = (front - 1 + _capacity) % _capacity; /*change front? */
        array[front] = item;
        ++size;
    }

  
  
    void delEnd() {
    if (size == 0) throw std::out_of_range("Array is empty");
    back = (back - 1 + _capacity) % _capacity; // Move back pointer
    --size;
    if (size > 0 && size <= _capacity / 4) resize(_capacity / 2); // Resize if array is 25% full
}

void delFront() {
    if (size == 0) throw std::out_of_range("Array is empty");
    front = (front + 1) % _capacity; // Move front pointer
    --size;
    if (size > 0 && size <= _capacity / 4) resize(_capacity / 2); // Resize if array is 25% full
}

    
    

  T& operator[](int i) {
    if (i < 0 || i >= size) {
        std::cout << "Error: Index out of bounds" << std::endl;
        // You can choose to return a default value or throw an exception here
        // For simplicity, let's return a default value for now
        // You may consider throwing an exception instead for more robust error handling
        static T default_value; // Default value for elmtype (assuming it's default constructible)
        return default_value;
    } else {
        int currentIndex = (front + i) % _capacity;
        return array[currentIndex];
    }
}


   
   
    int length() const {
        return size; //returns size of the array
    }

    
    int capacity() const {
    return _capacity; // Returns the current capacity of the array
}

void clear() {
    delete[] array; // Deletes the existing array
    _capacity = 2; // Resets capacity to 2
    size = 0; // Resets size to 0
    array = new T [_capacity]; // Allocates a new array with capacity 2
}



int partition(T* arr, int low, int high) {
    // Choose a random pivot element within the range [low, high]
    int randomIndex = low + rand() % (high - low + 1);
    T pivot = arr[randomIndex]; // Pivot element
    int i = low; // Index of smaller element

    for (int j = low; j <= high; j++) {
        // If the current element is smaller than the pivot
        if (j != randomIndex && arr[j] <= pivot) {
            std::swap(arr[i], arr[j]);
            i++; // Increment index of smaller element
        }
    }
    std::swap(arr[i], arr[randomIndex]);
    return i;
}

T QSelect(T* arr, int low, int high, int k) {
    if (k >= 1 && k <= high - low + 1) {
        int index = partition(arr, low, high);
        int length = index - low + 1; // Length of the left partition

        if (length == k) // If pivot is the kth smallest element
            return arr[index]; // return arr[index];

        if (length > k) // If kth smallest element is in the left partition
            return QSelect(arr, low, index - 1, k);

        // If kth smallest element is in the right partition
        return QSelect(arr, index + 1, high, k - length);
    }

    // Return an invalid value to indicate out-of-bounds k
    throw std::out_of_range("k is out of bounds");
}

T QSelect(int k) {
    T* copyArray = new T[size];
    for (int i = 0; i < size; ++i) {
        copyArray[i] = array[(front + i) % _capacity];
    }

    T result = QSelect(copyArray, 0, size - 1, k);
    delete[] copyArray;
    return result;
}






void Sort() {
    if (size <= 1) {
        // Array is already sorted or empty
        return;
    }

    // Create a temporary array to hold the sorted elements
    T* sortedArray = new T[size];
    int currentIndex = front;

    // Copy elements from the circular array to the temporary array
    for (int i = 0; i < size; ++i) {
        sortedArray[i] = array[currentIndex];
        currentIndex = (currentIndex + 1) % _capacity; // Move to the next circular index
    }

    // Sort the temporary array using a stable sorting algorithm (e.g., merge sort)
    mergeSort(sortedArray, 0, size - 1);

    // Copy the sorted elements back to the circular array
    currentIndex = front;
    for (int i = 0; i < size; ++i) {
        array[currentIndex] = sortedArray[i];
        currentIndex = (currentIndex + 1) % _capacity; // Move to the next circular index
    }

    // Free memory allocated for the temporary array
    delete[] sortedArray;
}

void merge(T* array, int low, int mid, int high) {
    int leftSize = mid - low + 1;
    int rightSize = high - mid;

    // Create temporary arrays for left and right halves
    T* leftArray = new T[leftSize];
    T* rightArray = new T[rightSize];

    // Copy data to temporary arrays
    int leftIndex = 0, rightIndex = 0;
    for (int i = low; i <= mid; ++i) {
        leftArray[leftIndex++] = array[i];
    }
    for (int i = mid + 1; i <= high; ++i) {
        rightArray[rightIndex++] = array[i];
    }

    // Merge the two sorted arrays into the original array
    int i = 0, j = 0, k = low;
    while (i < leftSize && j < rightSize) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            ++i;
        } else {
            array[k] = rightArray[j];
            ++j;
        }
        k = (k + 1) % _capacity; // Move to the next circular index
    }

    // Copy remaining elements of leftArray, if any
    while (i < leftSize) {
        array[k] = leftArray[i];
        ++i;
        k = (k + 1) % _capacity; // Move to the next circular index
    }

    // Copy remaining elements of rightArray, if any
    while (j < rightSize) {
        array[k] = rightArray[j];
        ++j;
        k = (k + 1) % _capacity; // Move to the next circular index
    }

    // Free memory allocated for temporary arrays
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(T* array, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(array, low, mid);      // Sort the left half
        mergeSort(array, mid + 1, high); // Sort the right half
        merge(array, low, mid, high);    // Merge the sorted halves
    }
}









int linearSearch(int e) {
    for (int i = 0; i < size; i++) {
        if (array[(front + i)%_capacity] == e) return i; //gets me to the user's index
    }
    return -1; // Element not found
}

int binSearch(int e) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (array[mid] == e) return mid; // Element found
        else if (array[mid] < e) low = mid + 1;
        else high = mid - 1;
    }
    return -1; // Element not found
}


};
