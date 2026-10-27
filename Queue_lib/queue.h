#pragma once
#include <iostream>
#include <utility>

template <typename T>
class Queue {
private:
    T* data_;
    size_t size_;
    size_t front_;
    size_t back_;
    size_t count_;
public:
    Queue(size_t size = 0);
    Queue(const Queue<T>& other);
    Queue(Queue<T>&& other);
    ~Queue();

    inline size_t size()const noexcept { return size_; }
    inline size_t count()const noexcept { return count_; }
    inline const T& front()const { if (isEmpty()) { throw std::logic_error("empty queue"); }return data_[front_]; }
    inline const T& back()const{ if (isEmpty()) { throw std::logic_error("empty queue"); }return data_[back_]; }

    inline bool isFull()const noexcept { return (size_ == count_); }
    inline bool isEmpty()const noexcept { return (count_ == 0); }

    void push(const T& elem);
    T pop();

    template <typename type>
    friend void swap(Queue<type>& this_q, Queue<type>& other_q);

    Queue<T>& operator=(const Queue<T>& other)noexcept;
    Queue<T>& operator=(Queue<T>&& other)noexcept;
};

template <typename type>
void swap(Queue<type>& this_q, Queue<type>& other_q) {
    using std::swap;
    swap(this_q.size_, other_q.size_);
    swap(this_q.count_, other_q.count_);
    swap(this_q.front_, other_q.front_);
    swap(this_q.back_, other_q.back_);
    swap(this_q.data_, other_q.data_);
}

template <typename T>
Queue<T>::Queue(size_t size):size_(size),count_(0),front_(0),back_(0),data_(new T[size]) {}

template <typename T>
Queue<T>::Queue(const Queue<T>& other):size_(other.size_),count_(other.count_),front_(other.front_),back_(other.back_),data_(new T[other.size_]) {
    for (size_t i = 0;i < other.count_;++i) {
        this->data_[i] = other.data_[i];
    }
}

template <typename T>
Queue<T>::Queue(Queue<T>&& other): size_(0), count_(0), front_(0), back_(0), data_(nullptr) {
    swap((*this), other);
}

template <typename T>
Queue<T>::~Queue() {
    size_ = 0;count_ = 0;front_ = 0;back_ = 0;
    if (data_) { delete[] data_; }
    data_ = nullptr;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)noexcept {
    Queue tmp(other);
    swap((*this), tmp);
    return (*this);
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other)noexcept {
    swap((*this), other);
    return (*this);
}

template <typename T>
void  Queue<T>::push(const T& elem) {
    if (isFull()) { throw std::logic_error("queue full"); }
    data_[back_] = elem;
    back_ = (back_ + 1) % size_;
    count_++;
}

template <typename T>
T  Queue<T>::pop() {
    if (isEmpty()) { throw std::logic_error("queue empty"); }
    T res = data_[front_];
    front_ = (front_ + 1) % size_;
    count_--;
    return res;
}