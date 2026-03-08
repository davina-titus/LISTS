#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "circvector.h"

using namespace std;
using namespace testing;

TEST(CircVector, defEmptySize) {
  CircVector<int> cv;
  EXPECT_THAT(cv.empty(), Eq(true));
  EXPECT_THAT(cv.size(), Eq((size_t)0));
}

TEST(CircVector, capConstructor) {
  CircVector<int> cv(5);
  EXPECT_THAT(cv.empty(), Eq(true));
  EXPECT_THAT(cv.get_capacity(), Eq((size_t)5));
}

TEST(CircVector, EmptyFAfterPush) {
  CircVector<int> cv;
  cv.push_back(1);
  EXPECT_THAT(cv.empty(), Eq(false));
}

TEST(CircVector, SizeIncPushBack) {
  CircVector<int> cv;
  cv.push_back(1);
  EXPECT_THAT(cv.size(), Eq((size_t)1));
  cv.push_back(2);
  EXPECT_THAT(cv.size(), Eq((size_t)2));
}

TEST(CircVectorCore, PushBackOrder) {
  CircVector<int> cv;
  cv.push_back(10);
  cv.push_back(20);
  cv.push_back(30);
  EXPECT_THAT(cv.at(0), Eq(10));
  EXPECT_THAT(cv.at(1), Eq(20));
  EXPECT_THAT(cv.at(2), Eq(30));
}

TEST(CircVectorCore, PushFrontOrder) {
  CircVector<int> cv;
  cv.push_front(3);
  cv.push_front(2);
  cv.push_front(1);
  EXPECT_THAT(cv.at(0), Eq(1));
  EXPECT_THAT(cv.at(1), Eq(2));
  EXPECT_THAT(cv.at(2), Eq(3));
}

TEST(CircVectorCore, PushFrontZero) {
  CircVector<int> cv(4);
  cv.push_back(10);
  cv.push_back(20);
  cv.push_front(5);
  EXPECT_THAT(cv.size(), Eq((size_t)3));
  EXPECT_THAT(cv.at(0), Eq(5));
  EXPECT_THAT(cv.at(1), Eq(10));
  EXPECT_THAT(cv.at(2), Eq(20));
}

TEST(CircVectorCore, PushBackWrap) {
  CircVector<int> cv(4);
  cv.push_front(3);
  cv.push_front(2);
  cv.push_back(4);
  cv.push_back(5);
  EXPECT_THAT(cv.size(), Eq((size_t)4));
  EXPECT_THAT(cv.at(0), Eq(2));
  EXPECT_THAT(cv.at(1), Eq(3));
  EXPECT_THAT(cv.at(2), Eq(4));
  EXPECT_THAT(cv.at(3), Eq(5));
}

TEST(CircVectorCore, PopBackWrap) {
  CircVector<int> cv(4);
  cv.push_front(3);
  cv.push_front(2);
  cv.push_back(4);
  cv.push_back(5);
  EXPECT_THAT(cv.pop_back(), Eq(5));
  EXPECT_THAT(cv.pop_back(), Eq(4));
}

TEST(CircVectorCore, PushBackResz) {
  CircVector<int> cv(2);
  cv.push_back(1);
  cv.push_back(2);
  cv.push_back(3);
  cv.push_back(4);
  EXPECT_THAT(cv.size(), Eq((size_t)4));
  EXPECT_THAT(cv.at(0), Eq(1));
  EXPECT_THAT(cv.at(1), Eq(2));
  EXPECT_THAT(cv.at(2), Eq(3));
  EXPECT_THAT(cv.at(3), Eq(4));
}

TEST(CircVectorCore, PushFrontResz) {
  CircVector<int> cv(2);
  cv.push_front(3);
  cv.push_front(2);
  cv.push_front(1);
  cv.push_front(0);
  EXPECT_THAT(cv.size(), Eq((size_t)4));
  EXPECT_THAT(cv.at(0), Eq(0));
  EXPECT_THAT(cv.at(1), Eq(1));
  EXPECT_THAT(cv.at(2), Eq(2));
  EXPECT_THAT(cv.at(3), Eq(3));
}

TEST(CircVectorCore, popFront) {
  CircVector<int> cv;
  cv.push_back(1);
  cv.push_back(2);
  EXPECT_THAT(cv.pop_front(), Eq(1));
  EXPECT_THAT(cv.size(), Eq((size_t)1));
}

TEST(CircVectorCore, popFrontEmpty) {
  CircVector<int> cv;
  EXPECT_THROW(cv.pop_front(), runtime_error);
}

TEST(CircVectorCore, popBack) {
  CircVector<int> cv;
  cv.push_back(1);
  cv.push_back(2);
  EXPECT_THAT(cv.pop_back(), Eq(2));
  EXPECT_THAT(cv.size(), Eq((size_t)1));
}

TEST(CircVectorCore, popBackEmpty) {
  CircVector<int> cv;
  EXPECT_THROW(cv.pop_back(), runtime_error);
}

TEST(CircVectorCore, PopDontAlter) {
  CircVector<int> cv;
  cv.push_back(1);
  cv.push_back(2);
  cv.pop_front();
  EXPECT_THAT(cv.size(), Eq((size_t)1));
  cv.pop_back();
  EXPECT_THAT(cv.size(), Eq((size_t)0));
  EXPECT_THAT(cv.empty(), Eq(true));
}

TEST(CircVectorCore, ValidIdx) {
  CircVector<int> cv;
  cv.push_back(5);
  cv.push_back(10);
  EXPECT_THAT(cv.at(0), Eq(5));
  EXPECT_THAT(cv.at(1), Eq(10));
}

TEST(CircVectorCore, OnBadIdx) {
  CircVector<int> cv;
  EXPECT_THROW(cv.at(0), out_of_range);
  cv.push_back(1);
  EXPECT_THROW(cv.at(1), out_of_range);
  EXPECT_THROW(cv.at(100), out_of_range);
}

TEST(CircVectorCore, ClearResetSZ) {
  CircVector<int> cv;
  cv.push_back(1);
  cv.push_back(2);
  cv.clear();
  EXPECT_THAT(cv.size(), Eq((size_t)0));
  EXPECT_THAT(cv.empty(), Eq(true));
}

TEST(CircVectorCore, clearPush) {
  CircVector<int> cv;
  cv.push_back(1);
  cv.clear();
  cv.push_back(5);
  EXPECT_THAT(cv.size(), Eq((size_t)1));
  EXPECT_THAT(cv.at(0), Eq(5));
}

TEST(CircVectorCore, PushPop) {
  CircVector<int> cv;
  cv.push_back(1);
  cv.push_back(2);
  cv.push_front(0);
  EXPECT_THAT(cv.pop_front(), Eq(0));
  EXPECT_THAT(cv.pop_back(), Eq(2));
  EXPECT_THAT(cv.size(), Eq((size_t)1));
}

// aug

TEST(CircVectorAug, StringEmpty) {
  CircVector<int> cv;
  EXPECT_THAT(cv.to_string(), StrEq("[]"));
}

TEST(CircVectorAugmented, StringOneElement) {
  CircVector<int> cv;
  cv.push_back(5);
  EXPECT_THAT(cv.to_string(), StrEq("[5]"));
}

TEST(CircVectorAugmented, StringMultiple) {
  CircVector<int> cv;
  cv.push_back(0);
  cv.push_back(1);
  cv.push_back(2);
  EXPECT_THAT(cv.to_string(), StrEq("[0, 1, 2]"));
}

TEST(CircVectorAugmented, FindFound) {
  CircVector<int> cv;
  cv.push_back(10);
  cv.push_back(20);
  cv.push_back(30);
  EXPECT_THAT(cv.find(10), Eq((size_t)0));
  EXPECT_THAT(cv.find(20), Eq((size_t)1));
  EXPECT_THAT(cv.find(30), Eq((size_t)2));
}

TEST(CircVectorAugmented, Findnotfound) {
  CircVector<int> cv;
  cv.push_back(10);
  EXPECT_THAT(cv.find(99), Eq((size_t)-1));
}

TEST(CircVectorAugmented, FindEmptyList) {
  CircVector<int> cv;
  EXPECT_THAT(cv.find(5), Eq((size_t)-1));
}

TEST(CircVectorAugmented, ReturnOneOcc) {
  CircVector<int> cv;
  cv.push_back(1);
  cv.push_back(2);
  cv.push_back(1);
  EXPECT_THAT(cv.find(1), Eq((size_t)0));
}

TEST(CircVectorAugmented, FindBadBoundsCheck) {
  CircVector<int> cv;
  cv.push_back(1);
  cv.push_back(2);
  cv.push_back(3);
  EXPECT_THAT(cv.find(3), Eq((size_t)2));
}

TEST(CircVectorAugmented, copyConstructor) {
  CircVector<int> cv;
  cv.push_back(1);
  cv.push_back(2);
  cv.push_back(3);
  CircVector<int> copy(cv);
  EXPECT_THAT(copy.size(), Eq((size_t)3));
  EXPECT_THAT(copy.at(0), Eq(1));
  EXPECT_THAT(copy.at(1), Eq(2));
  EXPECT_THAT(copy.at(2), Eq(3));
}

TEST(CircVectorAugmented, copyConstructorEmpty) {
  CircVector<int> cv;
  CircVector<int> copy(cv);
  EXPECT_THAT(copy.size(), Eq((size_t)0));
  EXPECT_THAT(copy.empty(), Eq(true));
}

TEST(CircVectorAugmented, Assign) {
  CircVector<int> cv;
  cv.push_back(1);
  cv.push_back(2);
  cv.push_back(3);
  CircVector<int> other;
  other = cv;
  EXPECT_THAT(other.size(), Eq((size_t)3));
  EXPECT_THAT(other.at(0), Eq(1));
  EXPECT_THAT(other.at(1), Eq(2));
  EXPECT_THAT(other.at(2), Eq(3));
}

TEST(CircVectorAugmented, AssignSelf) {
  CircVector<int> cv;
  cv.push_back(1);
  cv.push_back(2);
  CircVector<int>& ref = cv;
  cv = ref;
  EXPECT_THAT(cv.size(), Eq((size_t)2));
  EXPECT_THAT(cv.at(0), Eq(1));
}

TEST(CircVectorAugmented, RemoveLast) {
  CircVector<int> cv;
  cv.push_back(0);
  cv.push_back(1);
  cv.push_back(2);
  cv.push_back(1);
  cv.push_back(0);
  cv.push_back(1);
  cv.push_back(8);
  cv.remove_last(1);
  EXPECT_THAT(cv.size(), Eq((size_t)6));
  EXPECT_THAT(cv.to_string(), StrEq("[0, 1, 2, 1, 0, 8]"));
}

TEST(CircVectorAugmented, RemoveLNotFound) {
  CircVector<int> cv;
  cv.push_back(1);
  EXPECT_THROW(cv.remove_last(99), invalid_argument);
}

TEST(CircVectorAugmented, RemoveLastOcc) {
  CircVector<int> cv;
  cv.push_back(5);
  cv.remove_last(5);
  EXPECT_THAT(cv.size(), Eq((size_t)0));
  EXPECT_THAT(cv.empty(), Eq(true));
}

// extras

TEST(CircVectorExtras, InsertBefMiddle) {
  CircVector<int> cv;
  cv.push_back(0);
  cv.push_back(2);
  cv.push_back(4);
  cv.insert_before(1, 1);
  EXPECT_THAT(cv.at(1), Eq(1));
  EXPECT_THAT(cv.at(2), Eq(2));
}

TEST(CircVectorExtras, InsertBefSzupdate) {
  CircVector<int> cv;
  cv.push_back(1);
  cv.push_back(2);
  cv.insert_before(0, 0);
  EXPECT_THAT(cv.size(), Eq((size_t)3));
}

TEST(CircVectorExtras, InsertBefThrow) {
  CircVector<int> cv;
  cv.push_back(1);
  EXPECT_THROW(cv.insert_before(1, 99), out_of_range);
}

TEST(CircVectorExtras, InsertBefUpdatesSize) {
  CircVector<int> cv;
  cv.push_back(10);
  cv.push_back(20);
  cv.insert_before(0, 5);
  EXPECT_THAT(cv.at(0), Eq(5));
  EXPECT_THAT(cv.at(1), Eq(10));
  EXPECT_THAT(cv.at(2), Eq(20));
}

TEST(CircVectorExtras, InsertBefLast) {
  CircVector<int> cv;
  cv.push_back(1);
  cv.push_back(2);
  cv.push_back(3);
  cv.insert_before(2, 99);
  EXPECT_THAT(cv.size(), Eq((size_t)4));
  EXPECT_THAT(cv.at(2), Eq(99));
  EXPECT_THAT(cv.at(3), Eq(3));
}

TEST(CircVectorExtras, InsertBefResz) {
  CircVector<int> cv(2);
  cv.push_back(1);
  cv.push_back(2);
  cv.insert_before(0, 0);
  EXPECT_THAT(cv.size(), Eq((size_t)3));
  EXPECT_THAT(cv.at(0), Eq(0));
  EXPECT_THAT(cv.at(1), Eq(1));
  EXPECT_THAT(cv.at(2), Eq(2));
}

TEST(CircVectorExtras, RemoveEvery) {
  CircVector<int> cv;
  cv.push_back(0);
  cv.push_back(1);
  cv.push_back(2);
  cv.push_back(3);
  cv.push_back(4);
  cv.remove_every_other();
  EXPECT_THAT(cv.at(0), Eq(0));
  EXPECT_THAT(cv.at(1), Eq(2));
  EXPECT_THAT(cv.at(2), Eq(4));
}

TEST(CircVectorExtras, RemoveOtherSz) {
  CircVector<int> cv;
  cv.push_back(0);
  cv.push_back(1);
  cv.push_back(2);
  cv.push_back(3);
  cv.push_back(4);
  cv.remove_every_other();
  EXPECT_THAT(cv.size(), Eq((size_t)3));
}