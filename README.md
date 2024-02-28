# Project Circular Dynamic Array

#### Circular Dynamic Array

This project implements a circular dynamic array data structure in C++, which allows for dynamic resizing and efficient element access in a circular manner. The circular dynamic array is capable of storing elements of any data type.

---

#### Features

- **Dynamic Resizing**: The array dynamically resizes itself to accommodate new elements when its capacity is reached, ensuring efficient memory utilization.
  
- **Circular Access**: Elements can be added or removed from both ends of the array, and the array maintains a circular structure to enable efficient access and manipulation of elements.

- **Copy Constructor and Copy Assignment Operator**: The circular dynamic array supports proper copying of elements using a copy constructor and a copy assignment operator, ensuring that changes made to one instance do not affect others.

- **Element Access and Modification**: Elements can be accessed and modified using index-based access operators, allowing for easy retrieval and manipulation of array elements.

- **Sorting Algorithms**: The circular dynamic array supports sorting operations using stable sorting algorithms such as merge sort, ensuring that elements are arranged in ascending order.

- **Search Operations**: The array supports linear and binary search operations for efficiently locating elements within the array.

---

#### Usage

1. **Include Header File**: Include the header file `CircularDynamicArray.h` in your C++ source code to use the circular dynamic array data structure.
   
   ```cpp
   #include "CircularDynamicArray.h"
   ```

2. **Instantiate Array**: Create an instance of the `CircularDynamicArray` class, specifying the data type of elements to be stored in the array.
   
   ```cpp
   CircularDynamicArray<int> dynamicArray;
   ```

3. **Add and Remove Elements**: Use the `addEnd`, `addFront`, `delEnd`, and `delFront` methods to add or remove elements from the array.
   
   ```cpp
   dynamicArray.addEnd(10);
   dynamicArray.addFront(20);
   dynamicArray.delEnd();
   dynamicArray.delFront();
   ```

4. **Access Elements**: Access elements using index-based access operators (`[]`) or retrieve the front and back indices using the `f` and `b` methods, respectively.
   
   ```cpp
   int element = dynamicArray[0];
   int frontIndex = dynamicArray.f();
   int backIndex = dynamicArray.b();
   ```

5. **Sort and Search**: Perform sorting and search operations using the `Sort`, `linearSearch`, and `binSearch` methods.
   
   ```cpp
   dynamicArray.Sort();
   int index = dynamicArray.linearSearch(5);
   int sortedIndex = dynamicArray.binSearch(10);
   ```

6. **Additional Operations**: Perform other operations such as obtaining the length and capacity of the array, clearing the array, and selecting the k-th smallest element using the `length`, `capacity`, `clear`, and `QSelect` methods, respectively.

---

#### Contributions

Contributions to this project are welcome! If you find any bugs or have suggestions for improvements, please feel free to open an issue or submit a pull request on GitHub.

---

#### Contact

For any questions or inquiries, please contact Karthik Gaur at karthikgaur16@gmail.com.

---