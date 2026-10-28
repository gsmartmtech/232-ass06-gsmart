#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <iostream>

// ============================================================
// PART 2 Tests: DoublyLinkedList
// ============================================================

/// Create a DoublyLinkedList. Verify length() is 0 on a new list.
void test_new_list_is_empty(void)
{
    DoublyLinkedList dlList;
    TEST_ASSERT_EQUAL(0, dlList.length());
}

/// Create a DoublyLinkedList. Call pushFrontValue and pushBackValue.
/// Verify length() is 2.
void test_push_increases_length(void)
{
    DoublyLinkedList dlList;
    dlList.pushFrontValue(4);
    dlList.pushBackValue(5);
    TEST_ASSERT_EQUAL(2, dlList.length());
}

/// Create an EMPTY DoublyLinkedList.
/// Verify popFrontValue() and popBackValue() both have NO value (has_value() is false).
void test_pop_on_empty_list(void)
{
    DoublyLinkedList dlList;
    bool frontResult = dlList.popFrontValue().has_value();
    bool backResult = dlList.popBackValue().has_value();

    TEST_ASSERT_EQUAL(false, frontResult);
    TEST_ASSERT_EQUAL(false, backResult);
}

/// Push 1, 2, 3 with pushBackValue.
/// Verify popBackValue() gives 3, then popFrontValue() gives 1, then length() is 1.
void test_pop_order(void)
{
    DoublyLinkedList dlList;
    dlList.pushBackValue(1);
    dlList.pushBackValue(2);
    dlList.pushBackValue(3);

    std::optional<NodeValue> backResult = dlList.popBackValue();
    std::optional<NodeValue> frontResult = dlList.popFrontValue();

    TEST_ASSERT_EQUAL(3, std::get<int>(backResult.value()));
    TEST_ASSERT_EQUAL(1, std::get<int>(frontResult.value()));
}

/// Push one value, then call deleteValue with a value that is NOT in the list.
/// Verify it returns false and length() does not change.
void test_delete_value_not_found(void)
{
    DoublyLinkedList dlList;
    dlList.pushBackValue(1);

    TEST_ASSERT_EQUAL(nullptr, dlList.deleteValue(2));
}

/// Push 1, 2, 3 with pushBackValue. Call deleteValue(2).
/// Verify popBackValue() gives 3 and the next popBackValue() gives 1.
/// (popBackValue follows prevPtr: this fails if you forgot to repair the backward link.)
void test_delete_middle_keeps_links(void)
{
    DoublyLinkedList dlList;
    dlList.pushBackValue(1);
    dlList.pushBackValue(2);
    dlList.pushBackValue(3);

    dlList.deleteValue(2);
    std::optional<NodeValue> result1 = dlList.popBackValue();
    std::optional<NodeValue> result2 = dlList.popBackValue();

    TEST_ASSERT_EQUAL(3, std::get<int>(result1.value()));
    TEST_ASSERT_EQUAL(1, std::get<int>(result2.value()));
}

// ============================================================
// PART 3 Tests: StdDoublyLinkedList
// ============================================================

/// Push 1, 2, 1 with pushBackValue. Call deleteValue(NodeValue{1}).
/// Verify length() is 2 and popFrontValue() gives 2 (only the FIRST 1 was removed).
void test_std_delete_only_first(void)
{
    StdDoublyLinkedList list;
    list.pushBackValue(1);
    list.pushBackValue(2);
    list.pushBackValue(1);

    // is deleting both 1's, fix it
    list.deleteValue(1);

    std::optional<NodeValue> popResult = list.popFrontValue();

    TEST_ASSERT_EQUAL(2, list.length());
    TEST_ASSERT_EQUAL(2, std::get<int>(popResult.value()));
}

/// Create an EMPTY StdDoublyLinkedList.
/// Verify popFrontValue() and popBackValue() have NO value and do not crash.
void test_std_pop_on_empty_list(void)
{
    StdDoublyLinkedList list;

    std::optional<NodeValue> popFrontResult = list.popFrontValue();
    std::optional<NodeValue> popBackResult = list.popFrontValue();
    TEST_ASSERT_EQUAL(nullptr, std::get<int>(popFrontResult.value()));
    TEST_ASSERT_EQUAL(nullptr, std::get<int>(popBackResult.value()));
}
