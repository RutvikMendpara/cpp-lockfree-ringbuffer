#pragma once
/*
        Single-threaded ring buffer.
        Not thread-safe. Not lock-free.
        Capacity is (N - 1) due to reserved slot for full/empty distinction.
        Writes are rejected when full; reads are rejected when empty.
        Indexing is always in bounds - no overflow risk by design.
*/

class RingBuffer {
public:
    int put(int item);
    int get(int& value);

    int capacity() const;
    int isEmpty() const;
    bool isFull() const;

private:
    static constexpr int m_size = 10;
    int m_buffer[m_size];
    int m_write_index = 0;
    int m_read_index = 0;
};
