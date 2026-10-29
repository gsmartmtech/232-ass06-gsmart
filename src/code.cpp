// ============================================================
// CSCI 232 Assignment 06 – Doubly Linked List vs. std::list
// Student Implementation
// ============================================================

#include "code.hpp"
#include <algorithm>
#include <iostream>

// Uncomment the author block below and fill in your name:

std::string AUTHOR_NAME       = "Garrett Smart";
std::string AUTHOR_AUTHORSHIP = "I acknowledge that I have worked on this assignment independently, except where explicitly noted and referenced. Any collaboration or use of external resources has been properly cited. I am fully aware of the consequences of academic dishonesty and agree to abide by the university's academic integrity policy.";

// ============================================================
// PART 1: Class DoubleNode
// ============================================================

/// Constructor: initialize ALL THREE fields with a member initializer list.
/// value <- newValue, prevPtr <- nullptr, nextPtr <- nullptr.
DoubleNode::DoubleNode(NodeValue newValue)
{
    // TODO: move the initialization of all three fields into an initializer list
    this->value = newValue;
    this->nextPtr = nullptr;
    this->prevPtr = nullptr;   
}

/// Const getter: return the stored value.
NodeValue DoubleNode::getValue() const
{
    // TODO: return the value field
    return NodeValue{this->value};
}

/// Const getter: return the previous node (or nullptr).
DoubleNode *DoubleNode::getPrev() const
{
    // TODO: return the prevPtr field
    if (this != nullptr)
    {
        return prevPtr;
    }
    else
    {
        return nullptr;
    }
}

/// Const getter: return the next node (or nullptr).
DoubleNode *DoubleNode::getNext() const
{
    // TODO: return the nextPtr field
    if (this != nullptr)
    {
        return nextPtr;
    }
    else
    {
        return nullptr;
    }
}

/// Setter: store newPrevPtr in prevPtr.
void DoubleNode::setPrev(DoubleNode *newPrevPtr)
{
    // TODO: assign the field
    prevPtr = newPrevPtr;
}

/// Setter: store newNextPtr in nextPtr.
void DoubleNode::setNext(DoubleNode *newNextPtr)
{
    // TODO: assign the field
    nextPtr = newNextPtr;
}

// ============================================================
// PART 2: Class DoublyLinkedList
// ============================================================

/// Empty list: headPtr = nullptr, tailPtr = nullptr, count = 0.
DoublyLinkedList::DoublyLinkedList()
{
    // TODO: initialize all three fields (use an initializer list)
    this->headPtr = nullptr;
    tailPtr = nullptr;
    count = 0;
}

/// RAII: delete ALL nodes. Save the next pointer BEFORE delete.
DoublyLinkedList::~DoublyLinkedList()
{
    // TODO: walk through the list and delete every node
    while (this->count > 0)
    {
      DoubleNode *nodeToDelete = this->headPtr->getNext();
      // node contains prevPtr and nextPtr, don't need to deal with prevPtr as we are deleting whole list in order
      this->headPtr->setNext(nodeToDelete->getNext());
      delete nodeToDelete;
      count -= 1;
    }
}

/// Unlink the first node and RETURN it (do not delete it).
/// Fix headPtr, tailPtr, count. Clear the node's own prevPtr and nextPtr.
/// Return nullptr if the list is empty.
DoubleNode *DoublyLinkedList::detachFirst()
{
    // TODO: implement
    if (this->headPtr == nullptr)
    {
        return nullptr;
    }
    else
    {
        DoubleNode *detachedNode = this->headPtr;
        this->headPtr = detachedNode->getNext();
        this->headPtr->setPrev(nullptr);
        detachedNode->setNext(nullptr);
        detachedNode->setPrev(nullptr);
        this->count -= 1;
        return detachedNode;
    }
}

/// Unlink the last node and RETURN it (do not delete it).
/// Use the tail's prev link. Return nullptr if the list is empty.
DoubleNode *DoublyLinkedList::detachLast()
{
    // TODO: implement
    DoubleNode * currentPtr = this->headPtr;
    if (this->headPtr == nullptr)
    {
        return nullptr;
    }
    else
    {
        while (currentPtr->getNext() != nullptr)
        {
            currentPtr = currentPtr->getNext();
        }
        if (this->headPtr->getNext() != nullptr)
        {
            currentPtr->getPrev()->setNext(nullptr);
            this->tailPtr = currentPtr->getPrev();
        }
        else
        {
            this->headPtr = nullptr;
            this->tailPtr = nullptr;
        }
        currentPtr->setNext(nullptr);
        currentPtr->setPrev(nullptr);
        this->count -= 1;
        return currentPtr;
    }
}

/// Find the FIRST node equal to value and unlink it (head, tail, only node
/// or middle node). Return nullptr if not found. Reuse detachFirst/detachLast.
DoubleNode *DoublyLinkedList::detachValue(NodeValue value)
{
    // TODO: implement
    DoubleNode * currentPtr = this->headPtr;
    if (this->headPtr->getNext() == nullptr)
    {
        return nullptr;
    }
    else
    {
        while (currentPtr != nullptr)
        {
            if (currentPtr->getValue() == value)
            {
                currentPtr->getPrev()->setNext(currentPtr->getNext());
                currentPtr->getNext()->setPrev(currentPtr->getPrev());
                currentPtr->setNext(nullptr);
                currentPtr->setPrev(nullptr);
                this->count -= 1;
                return currentPtr;
            }
            currentPtr = currentPtr->getNext();
        }
    }
}

/// Create a node with new and link it in front. Handle the empty list.
void DoublyLinkedList::pushFrontValue(NodeValue value)
{
    // TODO: implement
    DoubleNode * newNode = new DoubleNode(value);
    if (this->headPtr == nullptr)
    {
        this->headPtr = newNode;
        this->tailPtr = newNode;
        this->count += 1;
    }
    else
    {
        this->headPtr->getNext()->setPrev(newNode);
        newNode->setNext(this->headPtr->getNext());
        this->headPtr->setNext(newNode);
        this->count += 1;
    }
}

/// Create a node with new and link it at the end. Handle the empty list.
void DoublyLinkedList::pushBackValue(NodeValue value)
{
    // TODO: implement
    DoubleNode * newNode = new DoubleNode(value);
    if (this->headPtr == nullptr)
    {
        this->headPtr = newNode;
        this->tailPtr = newNode;
        this->count += 1;
    }
    else
    {
        this->tailPtr->setNext(newNode);
        newNode->setPrev(this->tailPtr);
        this->tailPtr = newNode;
        this->count += 1;
    }
}

/// Detach the first node, read its value, delete the node, return the value.
/// Empty list -> std::nullopt.
std::optional<NodeValue> DoublyLinkedList::popFrontValue()
{
    // TODO: implement
    if (this->headPtr->getNext() != nullptr)
    {
        DoubleNode * detachedNode = this->detachFirst();
        std::variant valToReturn = detachedNode->getValue();
        delete detachedNode;
        this->count -= 1;
        return valToReturn;


    }
    else
    {
        return std::nullopt;
    }
}

/// Detach the last node, read its value, delete the node, return the value.
/// Empty list -> std::nullopt.
std::optional<NodeValue> DoublyLinkedList::popBackValue()
{
    if (this->tailPtr != nullptr)
    {
        DoubleNode * detachedNode = this->detachLast();
        std::variant valToReturn = detachedNode->getValue();
        delete detachedNode;
        this->count -= 1;
        return valToReturn;
    }
    else
    {
        return std::nullopt;
    }
}

/// Remove the FIRST node equal to value and free it.
/// Return true if something was removed.
bool DoublyLinkedList::deleteValue(NodeValue value)
{
    // TODO: implement
    DoubleNode * nodeToDelete = this->detachValue(value);
    if (nodeToDelete != nullptr)
    {
        delete nodeToDelete;
        return true;
    }
    else
    {
        return false;
    }
}

/// Return true if any node holds value.
bool DoublyLinkedList::containsValue(NodeValue value) const
{
    // TODO: implement
    DoubleNode * currentPtr = this->headPtr;
    while (currentPtr != nullptr)
    {
        if (currentPtr->getValue() == value)
        {
            return true;
        }
        currentPtr = currentPtr->getNext();
    }
    return false;
}

/// Print values head -> tail with std::visit (each followed by a space,
/// then a newline). Return the number of printed values.
int DoublyLinkedList::printForward() const
{
    // TODO: implement
    DoubleNode * currentPtr = this->headPtr;
    int count = 0;
    while (currentPtr != nullptr)
    {
        std::variant result = currentPtr->getValue();
        
        std::visit([](const auto& arg) 
        {
            std::cout << arg << ' \n';
        }, result);
        count += 1;
        currentPtr = currentPtr->getNext();
    }
    return count;
}

/// Print values tail -> head using prevPtr. Return the number of printed values.
int DoublyLinkedList::printBackward() const
{
    // TODO: implement

    DoubleNode * currentPtr = this->tailPtr;
    int count = 0;
    while (currentPtr != nullptr)
    {
        std::variant result = currentPtr->getValue();
        
        std::visit([](const auto& arg) 
        {
            std::cout << arg << ' \n';
        }, result);
        count += 1;
        currentPtr = currentPtr->getPrev();
    }
    return count;
}

/// Return count.
int DoublyLinkedList::length() const
{
    // TODO: implement
    return this->count;
}

// ===== BEGIN PART 3 (do not remove this marker) =====
// ============================================================
// PART 3: Class StdDoublyLinkedList
// ============================================================
// Only std::list methods, <algorithm>, iterators and std::visit.
// A loop is allowed ONLY for printing.

/// Which std::list method inserts at the front?
void StdDoublyLinkedList::pushFrontValue(NodeValue value)
{
    this->data.push_front(value);
}

/// Which std::list method inserts at the back?
void StdDoublyLinkedList::pushBackValue(NodeValue value)
{
    this->data.push_back(value);
}

/// Read the front element, remove it, return it. Empty -> std::nullopt.
std::optional<NodeValue> StdDoublyLinkedList::popFrontValue()
{
    // TODO: implement
    if (this->data.empty() != true)
    {
        NodeValue result = this->data.front();
        this->data.pop_front();
        return result;
    }
    else
    {
        return std::nullopt;
    }
}

/// Read the back element, remove it, return it. Empty -> std::nullopt.
std::optional<NodeValue> StdDoublyLinkedList::popBackValue()
{
    // TODO: implement
    if (this->data.empty() != true)
    {
        NodeValue result = this->data.back();
        this->data.pop_back();
        return result;
    }
    else
    {
        return std::nullopt;
    }
}

/// Remove only the FIRST element equal to value. Return true if removed.
bool StdDoublyLinkedList::deleteValue(NodeValue value)
{
    // TODO: implement
    auto result = std::find(this->data.begin(), this->data.end(), value);
    if (result != this->data.end())
    {
        this->data.erase(result);
        return true;
    }
    else
    {
        return false;
    }
}

/// Search without writing your own loop.
bool StdDoublyLinkedList::containsValue(NodeValue value) const
{
    // TODO: implement
    auto result = std::find(this->data.begin(), this->data.end(), value);
    if (result != this->data.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// Print head -> tail (same format as Part 2). Return the number of values.
int StdDoublyLinkedList::printForward() const
{
    // TODO: implement
    int count = 0;
    for (auto value : this->data)
    {

        if (std::holds_alternative<int>(value))
        {
            std::cout << std::get<int>(value) << std::endl;
        }
        else if (std::holds_alternative<double>(value))
        {
            std::cout << std::get<double>(value) << std::endl;
        }
        else if (std::holds_alternative<std::string>(value))
        {
            std::cout << std::get<std::string>(value) << std::endl;
        }
        count++;
    }
    return count;
}

/// Print tail -> head (same format as Part 2). Return the number of values.
int StdDoublyLinkedList::printBackward() const
{
    int count = 0;
    for (auto value : this->data.reverse())
    {

        if (std::holds_alternative<int>(value))
        {
            std::cout << std::get<int>(value) << std::endl;
        }
        else if (std::holds_alternative<double>(value))
        {
            std::cout << std::get<double>(value) << std::endl;
        }
        else if (std::holds_alternative<std::string>(value))
        {
            std::cout << std::get<std::string>(value) << std::endl;
        }
        count++;
    }
    return count;
}

/// size() returns size_t, length() returns int.
int StdDoublyLinkedList::length() const
{
    // TODO: implement
    return this->data.size();
}
// ===== END PART 3 (do not remove this marker) =====
