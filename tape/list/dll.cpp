#pragma once

template<typename T>
void DLL<T>::copy(const DLL<T>& others)
{
    Node *csave=others.first;
    this->first = new Node(others.first->data, nullptr, nullptr);
    Node *cur=this->first;
    Node *nextBox = nullptr;
    while (csave->next != nullptr)
    {
        csave = csave->next;
        nextBox = new Node(csave->data, cur, nullptr);
        cur->next = nextBox;
        cur = cur->next;
    }
}

template<typename T>
void DLL<T>::destroy()
{
    Node *save = this->first;
    while (this->first != this->last)
    {
        this->first = this->first->next;
        delete save;
        save = this->first;
    }
    this->last = nullptr;
}

template<typename T>
DLL<T>::DLL()
{
    first = nullptr;
    last = nullptr;
}

template<typename T>   
DLL<T>::DLL(const DLL<T>& other)
{
    this->copy(other);
}

template<typename T>
DLL<T>& DLL<T>::operator=(const DLL<T>& others)
{
    if(this != &others)
    {
        this->destroy();
        this->copy(others);
    }
    return *this;
}

template <typename T>
T& DLL<T>::operator[](size_t i) {
    Node* curr = first;

    while (curr != nullptr && i-- > 0) {
        curr = curr->next;
    }

    return curr->data;
}

template <typename T>
const T& DLL<T>::operator[](size_t i) const {
    Node* curr = first;

    while (curr != nullptr && i-- > 0) {
        curr = curr->next;
    }

    return curr->data;
}

template<typename T>
DLL<T>::~DLL()
{
    Node *save = this->first;
    while (this->first != this->last)
    {
        this->first = this->first->next;
        delete save;
        save = this->first;
    }
    this->last = nullptr;
}

template<typename T>
void DLL<T>::print() const
{
    Node *cur = first;
    while(cur != nullptr)
    {
        std::cout << cur->data << " ~> ";
        cur = cur->next;
    }
    std::cout << std::endl;
}

template<typename T>
DLL<T>& DLL<T>::push(const T& _data)
{
    if(first == nullptr)
    {
        first = new Node(_data, first, nullptr);
        last = first;
        return *this;
    }

    Node *newElem = new Node(_data,nullptr,first);
    first = newElem;

    return *this;
}

template<typename T>
DLL<T>& DLL<T>::push_back(const T& _data)
{
    if(first == nullptr)
    {
        first = new Node(_data, first, nullptr);
        last = first;
        return *this;
    }
    Node *newElem = new Node(_data, last, nullptr);
    last->next = newElem;
    last = last->next;

    return *this;
}

template<typename T>
DLL<T>& DLL<T>::pop()
{
    if(first == nullptr)
    {
        throw std::out_of_range("Empty list");
    }
    if(first->next == nullptr)
    {
        delete first;
        first = nullptr;
        last = nullptr;
        return *this;
    }
    Node *save = first;
    first = first->next;
    delete save;

    return *this;
}

template<typename T>
DLL<T>& DLL<T>::pop_back()
{
    if(first == nullptr) //empty list
    {
        throw std::out_of_range("Empty list");
    }
    if(first->next == nullptr)
    {
        delete first;
        first = nullptr;
        last = nullptr;
        return *this;
    }
    Node *save = last;
    last = last->prev;
    last->next = nullptr;
    delete save;

    return *this;
}

template<typename T>
DLL<T>& DLL<T>::clear()
{
    while(this->first != nullptr)
    {
        this->pop();
    }

    return *this;
}

template<typename T>
DLL<T>& DLL<T>::insertAfter(size_t i,const T& new_data)
{
    Node *_new = new Node(new_data,nullptr,nullptr);
    Node * cur = this->first;
    
    while(cur!= nullptr && i>0)
    {
        i--;
        cur=cur->next;
    }
    if(cur==nullptr && i)
    {
        throw std::out_of_range("Index out of bounds");
    }

    _new->prev = cur;
    cur->next->prev = _new;
    _new->next = cur->next;
    cur->next = _new;

    return *this;
}

template<typename T>
DLL<T>& DLL<T>::deleteAt(size_t i)
{
    Node * cur = this->first;
    if(i == 0)
    {
        this->first = first->next;
        first->prev = nullptr;
        delete cur;
        return *this;        
    }
    while(cur!= nullptr && i>0)
    {
        i--;
        cur=cur->next;
    }
    if(cur==nullptr && i)
    {
        throw std::out_of_range("Index out of bounds");
    }

    Node* toDel = cur;

    (cur->prev)->next = cur->next;
    (cur->next)->prev = cur->prev;
    delete toDel;
    return *this;
}

template <typename T>
void DLL<T>::reverse() {
    Node *crr = first;
    Node *save_next;

    // swapping
    while (crr != nullptr) {
        save_next = crr->prev;           // prev ---> next 
        crr->prev = crr->next;           // next ---> prev
        crr->next = save_next;

        crr = crr->prev;                 // crr ----> следващия елемент 
    }

    if (save_next != nullptr)
        first = save_next->prev;
}
template <typename T>
void DLL<T>::swap(Node *left, Node *right)
{
    if (left == nullptr || right == nullptr || first == last) 
        return;

    Node* beforeLeft = left->prev;
    Node* afterLeft = left->next;
    Node* beforeRight = right->prev;
    Node* afterRight = right->next;

    if (beforeLeft != nullptr) {
        std::swap(beforeLeft->next, beforeRight->next);
    } else {
        this->first = right;
    }

    if (afterRight != nullptr) {
        std::swap(afterLeft->next, afterRight->prev);
    } else {
        this->last = left;
    }

    std::swap(right->prev, left->prev);
    std::swap(right->next, left->next);
}


template<typename T>
size_t DLL<T>::size() const
{
    size_t cnt = 0;
    Node* cur = first;
    while (cur != nullptr)
    {
        cur = cur->next;
        cnt++;
    }
    return cnt;
}

template<typename T>
T& DLL<T>::getFirst() const
{
    return this->first->data;
}

template<typename T>
T& DLL<T>::getLast() const
{
    return this->last->data;
}

template<typename T>
bool DLL<T>::empty()
{
    return this->first==nullptr;
}
////////////////////
//Iterator methods//
////////////////////

template<typename T>
DLL<T>::Iterator::Iterator(Node *start)
{
    this->current = start;
}

template<typename T>
typename DLL<T>::Iterator DLL<T>::begin()
{
    return typename DLL<T>::Iterator(this->first);
}

template <typename T>
typename DLL<T>::Iterator DLL<T>::end()
{
    return typename DLL<T>::Iterator(nullptr);
}

template <typename T>
bool DLL<T>::Iterator::operator!= (const Iterator& other)
{
    return (current != other.current);
}

template <typename T>
T& DLL<T>::Iterator::operator*()
{
    return current->data;
}

template <typename T>
typename DLL<T>::Iterator& DLL<T>::Iterator::operator++()
{
    current = current->next;
    return *this;
}


////////////////////
//Reverse iterator//
////////////////////

template<typename T>
DLL<T>::ReverseIterator::ReverseIterator(Node *start)
{
    this->current = start;
}

template<typename T>
typename DLL<T>::ReverseIterator DLL<T>::rbegin()
{
    return typename DLL<T>::ReverseIterator(this->last);
}

template <typename T>
typename DLL<T>::ReverseIterator DLL<T>::rend()
{
    return typename DLL<T>::ReverseIterator(nullptr);
}

template <typename T>
bool DLL<T>::ReverseIterator::operator!= (const ReverseIterator& other)
{
    return (current != other.current);
}

template <typename T>
T& DLL<T>::ReverseIterator::operator*()
{
    return current->data;
}

template <typename T>
typename DLL<T>::ReverseIterator& DLL<T>::ReverseIterator::operator++()
{
    current = current->prev;
    return *this;
}










