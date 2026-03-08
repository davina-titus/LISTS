#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node* next;

    Node(T data) {
      this->data = data;
      this->next = nullptr;
    }

    Node(T data, Node* next) {
      this->data = data;
      this->next = next;
    }
  };

  size_t list_size;
  Node* list_front;

 public:
  /**
   * Default constructor. Creates an empty `LinkedList`.
   */
  LinkedList() {
    list_size = 0;
    list_front = nullptr;
  }

  /**
   * Returns whether the `LinkedList` is empty (i.e. whether its
   * size is 0).
   */
  bool empty() const {
    return list_size == 0;
  }

  /**
   * Returns the number of elements in the `LinkedList`.
   */
  size_t size() const {
    return list_size;
  }

  /**
   * Adds the given `T` to the front of the `LinkedList`.
   */
  void push_front(T data) {
    list_front = new Node(data, list_front);
    list_size++;
  }

  /**
   * Adds the given `T` to the back of the `LinkedList`.
   */
  void push_back(T data) {
    Node* newNode = new Node(data);
    if (list_front == nullptr) {
      list_front = newNode;
    } else {
      Node* curr = list_front;
      while (curr->next != nullptr) {
        curr = curr->next;
      }
      curr->next = newNode;
    }
    list_size++;
  }

  /**
   * Removes the element at the front of the `LinkedList`.
   *
   * If the `LinkedList` is empty, throws a `runtime_error`.
   */
  T pop_front() {
    if (list_size == 0) throw runtime_error("pop_front on empty list");
    T val = list_front->data;
    Node* old = list_front;
    list_front = list_front->next;
    delete old;
    list_size--;
    return val;
  }

  /**
   * Removes the element at the back of the `LinkedList`.
   *
   * If the `LinkedList` is empty, throws a `runtime_error`.
   */
  T pop_back() {
    if (list_size == 0) throw runtime_error("pop_back on empty list");
    T val;
    if (list_front->next == nullptr) {
      val = list_front->data;
      delete list_front;
      list_front = nullptr;
    } else {
      Node* curr = list_front;
      while (curr->next->next != nullptr) {
        curr = curr->next;
      }
      val = curr->next->data;
      delete curr->next;
      curr->next = nullptr;
    }
    list_size--;
    return val;
  }

  /**
   * Empties the `LinkedList`, releasing all allocated memory, and resetting
   * member variables appropriately.
   */
  void clear() {
    while (list_front != nullptr) {
      Node* old = list_front;
      list_front = list_front->next;
      delete old;
    }
    list_size = 0;
  }

  /**
   * Destructor. Clears all allocated memory.
   */
  ~LinkedList() {
    clear();
  }

  /**
   * Returns the element at the given index in the `LinkedList`.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  T& at(size_t index) const {
    if (index >= list_size) throw out_of_range("index out of range");
    Node* curr = list_front;
    for (size_t i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr->data;
  }

  /**
   * Copy constructor. Creates a deep copy of the given `LinkedList`.
   *
   * Must run in O(N) time.
   */
  LinkedList(const LinkedList& other) {
    list_size = 0;
    list_front = nullptr;
    Node* curr = other.list_front;

    Node* head = nullptr;
    while (curr != nullptr) {
      Node* newNode = new Node(curr->data);
      if (head == nullptr) {
        list_front = newNode;
      } else {
        head->next = newNode;
      }
      head = newNode;
      list_size++;
      curr = curr->next;
    }
  }

  /**
   * Assignment operator. Sets the current `LinkedList` to a deep copy of the
   * given `LinkedList`.
   *
   * Must run in O(N) time.
   */
  LinkedList& operator=(const LinkedList& other) {
    if (this == &other) return *this;
    clear();
    Node* curr = other.list_front;
    Node* head = nullptr;
    while (curr != nullptr) {
      Node* newNode = new Node(curr->data);
      if (head == nullptr) {
        list_front = newNode;
      } else {
        head->next = newNode;
      }
      head = newNode;
      list_size++;
      curr = curr->next;
    }
    return *this;
  }

  /**
   * Converts the `LinkedList` to a string. Formatted like `[0, 1, 2, 3, 4]`
   * (without the backticks -- hover the function name to see). Runs in O(N)
   * time.
   */
  string to_string() const {
    ostringstream oss;
    oss << "[";
    Node* curr = list_front;
    while (curr != nullptr) {
      oss << curr->data;
      if (curr->next != nullptr) oss << ", ";
      curr = curr->next;
    }
    oss << "]";
    return oss.str();
  }

  /**
   * Searches the `LinkedList` for the first matching element, and returns its
   * index. If no match is found, returns "-1".
   */
  size_t find(const T& data) {
    Node* curr = list_front;
    size_t idx = 0;
    while (curr != nullptr) {
      if (curr->data == data) return idx;
      curr = curr->next;
      idx++;
    }
    return (size_t)-1;
  }

  /**
   * Removes the last occurrence of the given value from the `LinkedList`.
   *
   * For example, if a list was `[0, 1, 2, 1, 0, 1, 8]`, then a call to
   * `remove_last(1)` should change the list to be [0, 1, 2, 1, 0, 8]`.
   *
   * If the given value is not found on the `LinkedList`, throws an
   * `invalid_argument` exception.
   */
  void remove_last(const T& value) {
    Node* lastPrev = nullptr;
    Node* last = nullptr;

    Node* prev = nullptr;
    Node* curr = list_front;

    while (curr != nullptr) {
      if (curr->data == value) {
        lastPrev = prev;
        last = curr;
      }
      prev = curr;
      curr = curr->next;
    }

    if (last == nullptr) throw invalid_argument("value not found");

    if (lastPrev == nullptr) {
      list_front = last->next;
    } else {
      lastPrev->next = last->next;
    }
    delete last;
    list_size--;
  }

  /**
   * Inserts the given `T` as a new element in the `LinkedList` before
   * the element currently stored in the given index. If the index is not
   * a current valid index in the list, throws `out_of_range`.
   */
  void insert_before(size_t index, T elem) {
    if (index >= list_size) throw out_of_range("index out of range");

    if (index == 0) {
      push_front(elem);
      return;
    }
    Node* curr = list_front;

    for (size_t i = 0; i < index - 1; i++) {
      curr = curr->next;
    }

    Node* newNode = new Node(elem, curr->next);
    curr->next = newNode;
    list_size++;
  }

  /**
   * Remove every other element (alternating) from the
   * `LinkedList`, starting at index 1. Must run in O(N).
   *
   * For example, if a list was `[0, 1, 2, 3, 4]`, removing every other element
   * would change the list to `[0, 2, 4]`.
   */
  void remove_every_other() {
    if (list_front == nullptr) return;

    Node* keep = list_front;

    while (keep != nullptr && keep->next != nullptr) {
      Node* toDel = keep->next;
      keep->next = toDel->next;
      delete toDel;
      list_size--;
      keep = keep->next;
    }
  }

  /**
   * Returns a pointer to the node at the front of the `LinkedList`. For
   * autograder testing purposes only.
   */
  void* front() const {
    return this->list_front;
  }
};