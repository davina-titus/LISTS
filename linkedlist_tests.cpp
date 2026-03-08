#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "linkedlist.h"

using namespace std;
using namespace testing;

TEST(LinkedListCore, DefEmptySz) {
  LinkedList<int> ll;
  EXPECT_THAT(ll.empty(), Eq(true));
  EXPECT_THAT(ll.size(), Eq((size_t)0));
}

TEST(LinkedListCore, pushFrontSzInc) {
  LinkedList<int> ll;
  ll.push_front(1);
  EXPECT_THAT(ll.size(), Eq((size_t)1));
  EXPECT_THAT(ll.empty(), Eq(false));
  ll.push_front(2);
  EXPECT_THAT(ll.size(), Eq((size_t)2));
}

TEST(LinkedListCore, PushFronde) {
  LinkedList<int> ll;
  ll.push_front(1);
  ll.push_front(2);
  ll.push_front(3);
  EXPECT_THAT(ll.at(0), Eq(3));
  EXPECT_THAT(ll.at(1), Eq(2));
  EXPECT_THAT(ll.at(2), Eq(1));
}

TEST(LinkedListCore, PushBackSzInc) {
  LinkedList<int> ll;
  ll.push_back(10);
  EXPECT_THAT(ll.size(), Eq((size_t)1));
  ll.push_back(20);
  EXPECT_THAT(ll.size(), Eq((size_t)2));
}

TEST(LinkedListCore, PushBackde) {
  LinkedList<int> ll;
  ll.push_back(10);
  ll.push_back(20);
  ll.push_back(30);
  EXPECT_THAT(ll.at(0), Eq(10));
  EXPECT_THAT(ll.at(1), Eq(20));
  EXPECT_THAT(ll.at(2), Eq(30));
}

TEST(LinkedListCore, PushBEmpty) {
  LinkedList<int> ll;
  ll.push_back(99);
  EXPECT_THAT(ll.size(), Eq((size_t)1));
  EXPECT_THAT(ll.at(0), Eq(99));
}

TEST(LinkedListCore, PopFront) {
  LinkedList<int> ll;
  ll.push_front(1);
  ll.push_front(2);
  EXPECT_THAT(ll.pop_front(), Eq(2));
  EXPECT_THAT(ll.size(), Eq((size_t)1));
  EXPECT_THAT(ll.pop_front(), Eq(1));
  EXPECT_THAT(ll.size(), Eq((size_t)0));
  EXPECT_THAT(ll.empty(), Eq(true));
}

TEST(LinkedListCore, PopFrontEmpty) {
  LinkedList<int> ll;
  EXPECT_THROW(ll.pop_front(), runtime_error);
}

TEST(LinkedListCore, PopBack) {
  LinkedList<int> ll;
  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(3);
  EXPECT_THAT(ll.pop_back(), Eq(3));
  EXPECT_THAT(ll.size(), Eq((size_t)2));
  EXPECT_THAT(ll.pop_back(), Eq(2));
  EXPECT_THAT(ll.pop_back(), Eq(1));
  EXPECT_THAT(ll.size(), Eq((size_t)0));
}

TEST(LinkedListCore, PopBackEmpty) {
  LinkedList<int> ll;
  EXPECT_THROW(ll.pop_back(), runtime_error);
}

TEST(LinkedListCore, PopBackOne) {
  LinkedList<int> ll;
  ll.push_back(42);
  EXPECT_THAT(ll.pop_back(), Eq(42));
  EXPECT_THAT(ll.size(), Eq((size_t)0));
  EXPECT_THAT(ll.empty(), Eq(true));
}

TEST(LinkedListCore, ValidIdx) {
  LinkedList<int> ll;
  ll.push_back(10);
  ll.push_back(20);
  ll.push_back(30);
  EXPECT_THAT(ll.at(0), Eq(10));
  EXPECT_THAT(ll.at(1), Eq(20));
  EXPECT_THAT(ll.at(2), Eq(30));
}

TEST(LinkedListCore, BadIdx) {
  LinkedList<int> ll;
  EXPECT_THROW(ll.at(0), out_of_range);
  ll.push_back(1);
  EXPECT_THROW(ll.at(1), out_of_range);
  EXPECT_THROW(ll.at(100), out_of_range);
}

TEST(LinkedListCore, ClearResetsSz) {
  LinkedList<int> ll;
  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(3);
  ll.clear();
  EXPECT_THAT(ll.size(), Eq((size_t)0));
  EXPECT_THAT(ll.empty(), Eq(true));
}

TEST(LinkedListCore, clearPush) {
  LinkedList<int> ll;
  ll.push_back(1);
  ll.clear();
  ll.push_back(5);
  EXPECT_THAT(ll.size(), Eq((size_t)1));
  EXPECT_THAT(ll.at(0), Eq(5));
}

TEST(LinkedListCore, PushFrontPreserve) {
  LinkedList<int> ll;
  ll.push_back(1);
  ll.push_back(2);
  ll.push_front(0);
  EXPECT_THAT(ll.size(), Eq((size_t)3));
  EXPECT_THAT(ll.at(0), Eq(0));
  EXPECT_THAT(ll.at(1), Eq(1));
  EXPECT_THAT(ll.at(2), Eq(2));
}

TEST(LinkedListCore, PushPop) {
  LinkedList<int> ll;
  ll.push_back(1);
  ll.push_back(2);
  ll.push_front(0);
  EXPECT_THAT(ll.pop_front(), Eq(0));
  EXPECT_THAT(ll.pop_back(), Eq(2));
  EXPECT_THAT(ll.size(), Eq((size_t)1));
}

// aug

TEST(LinkedListAugmented, StringEmpty) {
  LinkedList<int> ll;
  EXPECT_THAT(ll.to_string(), StrEq("[]"));
}

TEST(LinkedListAugmented, StringMultiple) {
  LinkedList<int> ll;
  ll.push_back(0);
  ll.push_back(1);
  ll.push_back(2);
  EXPECT_THAT(ll.to_string(), StrEq("[0, 1, 2]"));
}

TEST(LinkedListAugmented, FindFound) {
  LinkedList<int> ll;
  ll.push_back(10);
  ll.push_back(20);
  ll.push_back(30);
  EXPECT_THAT(ll.find(10), Eq((size_t)0));
  EXPECT_THAT(ll.find(20), Eq((size_t)1));
  EXPECT_THAT(ll.find(30), Eq((size_t)2));
}

TEST(LinkedListAugmented, FindNotFound) {
  LinkedList<int> ll;
  ll.push_back(10);
  EXPECT_THAT(ll.find(99), Eq((size_t)-1));
}

TEST(LinkedListAugmented, FindEmptyList) {
  LinkedList<int> ll;
  EXPECT_THAT(ll.find(5), Eq((size_t)-1));
}

TEST(LinkedListAugmented, CopyConstructor) {
  LinkedList<int> ll;
  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(3);
  LinkedList<int> copy(ll);
  EXPECT_THAT(copy.size(), Eq((size_t)3));
  EXPECT_THAT(copy.at(0), Eq(1));
  EXPECT_THAT(copy.at(1), Eq(2));
  EXPECT_THAT(copy.at(2), Eq(3));
}

TEST(LinkedListAugmented, CopyConstructorEmpty) {
  LinkedList<int> ll;
  LinkedList<int> copy(ll);
  EXPECT_THAT(copy.size(), Eq((size_t)0));
  EXPECT_THAT(copy.empty(), Eq(true));
}

TEST(LinkedListAugmented, Assign) {
  LinkedList<int> ll;
  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(3);
  LinkedList<int> other;
  other = ll;
  EXPECT_THAT(other.size(), Eq((size_t)3));
  EXPECT_THAT(other.at(0), Eq(1));
  EXPECT_THAT(other.at(1), Eq(2));
  EXPECT_THAT(other.at(2), Eq(3));
}

TEST(LinkedListAugmented, AssignEmpty) {
  LinkedList<int> ll;
  LinkedList<int> other;
  other.push_back(5);
  other = ll;
  EXPECT_THAT(other.size(), Eq((size_t)0));
  EXPECT_THAT(other.empty(), Eq(true));
}

TEST(LinkedListAugmented, AssignSelf) {
  LinkedList<int> ll;
  ll.push_back(1);
  ll.push_back(2);
  LinkedList<int>& ref = ll;
  ll = ref;
  EXPECT_THAT(ll.size(), Eq((size_t)2));
  EXPECT_THAT(ll.at(0), Eq(1));
}

TEST(LinkedListAugmented, RemoveLastBasic) {
  LinkedList<int> ll;
  ll.push_back(0);
  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(1);
  ll.push_back(0);
  ll.push_back(1);
  ll.push_back(8);
  ll.remove_last(1);
  EXPECT_THAT(ll.size(), Eq((size_t)6));
  EXPECT_THAT(ll.to_string(), StrEq("[0, 1, 2, 1, 0, 8]"));
}

TEST(LinkedListAugmented, RemoveLastNotFound) {
  LinkedList<int> ll;
  ll.push_back(1);
  EXPECT_THROW(ll.remove_last(99), invalid_argument);
}

TEST(LinkedListAugmented, RemoveLastOnlyOccurrence) {
  LinkedList<int> ll;
  ll.push_back(5);
  ll.remove_last(5);
  EXPECT_THAT(ll.size(), Eq((size_t)0));
  EXPECT_THAT(ll.empty(), Eq(true));
}

// extras

TEST(LinkedListExtras, InsertBefore) {
  LinkedList<int> ll;
  ll.push_back(0);
  ll.push_back(2);
  ll.push_back(4);
  ll.insert_before(1, 1);
  EXPECT_THAT(ll.size(), Eq((size_t)4));
  EXPECT_THAT(ll.at(0), Eq(0));
  EXPECT_THAT(ll.at(1), Eq(1));
  EXPECT_THAT(ll.at(2), Eq(2));
  EXPECT_THAT(ll.at(3), Eq(4));
}

TEST(LinkedListExtras, InsertBefLast) {
  LinkedList<int> ll;
  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(3);
  ll.insert_before(2, 99);
  EXPECT_THAT(ll.size(), Eq((size_t)4));
  EXPECT_THAT(ll.at(2), Eq(99));
  EXPECT_THAT(ll.at(3), Eq(3));
}

TEST(LinkedListExtras, InsertBefBadIdx) {
  LinkedList<int> ll;
  ll.push_back(1);
  EXPECT_THROW(ll.insert_before(1, 5), out_of_range);
  EXPECT_THROW(ll.insert_before(100, 5), out_of_range);
}

TEST(LinkedListExtras, RemoveEveryOther) {
  LinkedList<int> ll;
  for (int i = 0; i < 5; i++) ll.push_back(i);
  ll.remove_every_other();
  EXPECT_THAT(ll.size(), Eq((size_t)3));
  EXPECT_THAT(ll.at(0), Eq(0));
  EXPECT_THAT(ll.at(1), Eq(2));
  EXPECT_THAT(ll.at(2), Eq(4));
}

TEST(LinkedListExtras, RemoveOtherEmpty) {
  LinkedList<int> ll;
  ll.remove_every_other();
  EXPECT_THAT(ll.size(), Eq((size_t)0));
}

TEST(LinkedListExtras, RemoveOtherOdd) {
  LinkedList<int> ll;
  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(3);
  ll.remove_every_other();
  EXPECT_THAT(ll.size(), Eq((size_t)2));
  EXPECT_THAT(ll.at(0), Eq(1));
  EXPECT_THAT(ll.at(1), Eq(3));
}

TEST(LinkedListExtras, RemoveOtherUpdate) {
  LinkedList<int> ll;
  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(3);
  ll.push_back(4);
  ll.push_back(5);
  ll.remove_every_other();
  EXPECT_THAT(ll.size(), Eq((size_t)3));
}
