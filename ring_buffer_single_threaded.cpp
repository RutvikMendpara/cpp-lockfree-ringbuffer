#include "ring_buffer_single_threaded.h"

	int RingBuffer::put(int item) {
		if (isFull()) {
			return 0;
		}
		m_buffer[m_write_index] = item;
		m_write_index = (m_write_index + 1) % m_size;
		return 1;
	}

	int RingBuffer::get(int& value) {
		if (m_read_index == m_write_index) return 0; // buffer is empty
		value = m_buffer[m_read_index];
		m_read_index = (m_read_index + 1) % m_size;
		return 1;
	}

	int RingBuffer::capacity() const { return m_size - 1;  }//  note: only (N - 1) elements can be stored at a given time
	int RingBuffer::isEmpty() const { return m_read_index == m_write_index; }
	bool RingBuffer::isFull() const {
		return (m_write_index + 1) % m_size == m_read_index;
	}


