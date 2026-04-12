#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class CircVector {
 private:
  T* data;
  size_t vec_size;
  size_t capacity;
  size_t front_idx;

 
  size_t wrap(size_t idx) const {
    return idx % capacity;
  }

  void resize() {
    size_t newCap = capacity * 2;
    T* newData = new T[newCap];

    for (size_t i = 0; i < vec_size; i++) {
      newData[i] = at(i);
    }
    delete[] data;
    data = newData;
    capacity = newCap;
    front_idx = 0;
  }

 public:
  /**
   * Default constructor. Creates an empty `CircVector` with capacity 10.
   */
  CircVector() {
    vec_size = 0;
    front_idx = 0;
    capacity = 10;
    data = new T[capacity];
  }

  /**
   * Creates an empty `CircVector` with given capacity. Capacity must exceed 0.
   */
  CircVector(size_t capacity) {
    this->capacity = capacity;
    vec_size = 0;
    front_idx = 0;
    data = new T[capacity];
  }

  /**
   * Returns whether the `CircVector` is empty (i.e. whether its
   * size is 0).
   */
  bool empty() const {
    return vec_size == 0;
  }

  /**
   * Returns the number of elements in the `CircVector`.
   */
  size_t size() const {
    return vec_size;
  }

  /**
   * Adds the given `T` to the front of the `CircVector`.
   */

  void push_front(T elem) {
    if (vec_size == capacity) resize();

    front_idx = wrap(front_idx + capacity - 1);
    data[front_idx] = elem;
    vec_size++;
  }

  /**
   * Adds the given `T` to the back of the `CircVector`.
   */
  void push_back(T elem) {
    if (vec_size == capacity) resize();
    data[wrap(front_idx + vec_size)] = elem;
    vec_size++;
  }

  /**
   * Removes the element at the front of the `CircVector`.
   *
   * If the `CircVector` is empty, throws a `runtime_error`.
   */
  T pop_front() {
    if (vec_size == 0) throw runtime_error("pop_front on empty");
    T val = data[front_idx];
    front_idx = wrap(front_idx + 1);
    vec_size--;
    return val;
  }

  /**
   * Removes the element at the back of the `CircVector`.
   *
   * If the `CircVector` is empty, throws a `runtime_error`.
   */
  T pop_back() {
    if (vec_size == 0) throw runtime_error("pop_back on empty");
    T val = at(vec_size - 1);
    vec_size--;
    return val;
  }

  /**
   * Removes all elements from the `CircVector`.
   */
  void clear() {
    front_idx = 0;
    vec_size = 0;
  }

  /**
   * Destructor. Clears all allocated memory.
   */
  ~CircVector() {
    delete[] data;
  }

  /**
   * Returns the element at the given index in the `CircVector`.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  T& at(size_t index) const {
    if (index >= vec_size) throw out_of_range("index out of range");
    return data[wrap(front_idx + index)];
  }

  /**
   * Copy constructor. Creates a deep copy of the given `CircVector`.
   *
   * Must run in O(N) time.
   */
  CircVector(const CircVector& other) {
    capacity = other.capacity;
    vec_size = other.vec_size;
    front_idx = 0;
    data = new T[capacity];
    for (size_t i = 0; i < vec_size; i++) {
      data[i] = other.at(i);
    }
  }

  /**
   * Assignment operator. Sets the current `CircVector` to a deep copy of the
   * given `CircVector`.
   *
   * Must run in O(N) time.
   */
  CircVector& operator=(const CircVector& other) {
    if (this == &other) return *this;
    delete[] data;
    capacity = other.capacity;
    vec_size = other.vec_size;
    front_idx = 0;
    data = new T[capacity];
    for (size_t i = 0; i < vec_size; i++) {
      data[i] = other.at(i);
    }
    return *this;
  }

  /**
   * Converts the `CircVector` to a string. Formatted like `[0, 1, 2, 3, 4]`
   * (without the backticks -- hover the function name to see). Runs in O(N)
   * time.
   */
  string to_string() const {
    ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < vec_size; i++) {
      oss << at(i);
      if (i + 1 < vec_size) oss << ", ";
    }
    oss << "]";
    return oss.str();
  }

  /**
   * Searches the `CircVector` for the first matching element, and returns its
   * index in the `CircVector`. If no match is found, returns "-1".
   */
  size_t find(const T& target) {
    for (size_t i = 0; i < vec_size; i++) {
      if (at(i) == target) return i;
    }
    return (size_t)-1;
  }

  /**
   * Removes the last occurrence of the given `value` from the `CircVector`.
   *
   * For example, if a list was `[0, 1, 2, 1, 0, 1, 8]`, then a call to
   * `remove_last(1)` should change the list to be [0, 1, 2, 1, 0, 8]`.
   *
   * If the given value is not found on the `CircVector`, throws an
   * `invalid_argument` exception.
   */
  void remove_last(const T& value) {
    bool found = false;
    size_t lastIdx = 0;
    for (size_t i = 0; i < vec_size; i++) {
      if (at(i) == value) {
        lastIdx = i;
        found = true;
      }
    }
    if (!found) throw invalid_argument("value not found");

    for (size_t i = lastIdx; i + 1 < vec_size; i++) {
      at(i) = at(i + 1);
    }
    vec_size--;
  }

  /**
   * Inserts the given `T` as a new element in the `CircVector` before
   * the element currently stored in the given index. If the index is not
   * a current valid index in the list, throws `out_of_range`.
   */
  void insert_before(size_t index, T elem) {
    if (index >= vec_size) throw out_of_range("index out of range");
    if (vec_size == capacity) resize();

    vec_size++;
    for (size_t i = vec_size - 1; i > index; i--) {
      at(i) = at(i - 1);
    }
    at(index) = elem;
  }

  /**
   * Remove every other element (alternating) from the
   * `CircVector`, starting at index 1. Must run in O(N). May not reallocate.
   *
   * For example, if a list was `[0, 1, 2, 3, 4]`, removing every other element
   * would change the list to `[0, 2, 4]`.
   */
  void remove_every_other() {
    size_t newSize = 0;
    for (size_t i = 0; i < vec_size; i++) {
      if (i % 2 == 0) {
        // keep: compacting in-place from position 0
        at(newSize) = at(i);
        newSize++;
      }
    }
    vec_size = newSize;
  }

  /**
   * Returns a pointer to the underlying memory managed by the `CircVec`.
   * For autograder testing purposes only.
   */
  T* get_data() const {
    return this->data;
  }

  /**
   * Returns the capacity of the underlying memory managed by the `CircVec`. For
   * autograder testing purposes only.
   */
  size_t get_capacity() const {
    return this->capacity;
  }
};
