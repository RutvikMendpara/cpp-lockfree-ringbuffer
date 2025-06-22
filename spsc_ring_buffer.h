#pragma once

#include <atomic>

class SPSCQueue {
public:
    bool put(int item);
    bool get(int& value);

    int capacity() const { return m_size - 1; }
    bool debugIsEmpty() const;
    bool debugIsFull() const;

private:
    static constexpr int m_size = 1024;
    static_assert((m_size& (m_size - 1)) == 0, "m_size must be power of two");

    int m_buffer[m_size];

    std::atomic<int> m_write_index{ 0 };
    std::atomic<int> m_read_index{ 0 };
};