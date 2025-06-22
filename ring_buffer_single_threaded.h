#pragma once

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
