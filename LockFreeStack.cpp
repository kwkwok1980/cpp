#include <iostream>
#include <utility>
#include <type_traits>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <unistd.h>

#include <array>
#include <iostream>
#include <string_view>
#include <mutex>
#include <thread>
#include <atomic>

template <typename T>
struct Node
{
    T value{};
    Node<T>* next{};
};

template <typename T>
struct StackHead
{
    std::uint64_t version{};
    Node<T>* node{};
};

template <typename T>
struct Stack
{
    std::atomic<StackHead<T>> m_Head{};

    void Push(const T& value)
    {
        StackHead<T> newHead{};
        newHead.node = new Node<T>();
        newHead.node->value = value;

        StackHead<T> oldHead = m_Head.load();
        do{
            newHead.version = oldHead.version + 1;
            newHead.node->next = oldHead.node;
        }
        while (!m_Head.compare_exchange_weak(oldHead, newHead));
    }

    bool Pop(T& value)
    {
        StackHead<T> newHead{};
        StackHead<T> oldHead = m_Head.load();
        do
        {
            if (oldHead.node == nullptr)
            {
                return false;
            }
            newHead.version = oldHead.version + 1;
            newHead.node = oldHead.node->next;
        }
        while(!m_Head.compare_exchange_weak(oldHead, newHead));

        value = oldHead.node->value;
        delete oldHead.node;
        return true;
    }

    StackHead<T> head{};
};

template <typename T>
struct S
{
    //std::uint64_t value = 0;
    Node<T>* m_Head{};
    char c;
};

std::atomic<int> a = 1;
std::atomic<S<int>> s;

int main()
{
    s.store(S<int>{});
    S<int> k {};
    s.compare_exchange_weak(k, S<int>{});
    //std::cout << s.load().value << std::endl;
    //Stack<int> stack{};
    //stack.Push(10);
    return 0;
}
