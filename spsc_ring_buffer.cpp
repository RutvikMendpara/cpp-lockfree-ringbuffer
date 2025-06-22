#include "spsc_ring_buffer.h"

bool SPSCQueue::put(int item) {

	int write = m_write_index.load(std::memory_order_relaxed);
	int next = (write + 1) & (m_size - 1);
	
	if (next == m_read_index.load(std::memory_order_acquire)) return false; // full
	m_buffer[write] = item;
	m_write_index.store(next, std::memory_order_release);
	return true;
}


bool SPSCQueue::get(int& item) {
	int read = m_read_index.load(std::memory_order_relaxed);
	
	if (read == m_write_index.load(std::memory_order_acquire)) return false; //empty
	
	item = m_buffer[read];
	m_read_index.store((read + 1) & (m_size - 1), std::memory_order_release);
	return true;

}

bool SPSCQueue::debugIsEmpty() const {
	return m_read_index.load(std::memory_order_acquire) == 
		m_write_index.load(std::memory_order_acquire);
}

bool SPSCQueue::debugIsFull() const {
	return ((m_write_index.load(std::memory_order_acquire) + 1) & (m_size - 1)) ==
		m_read_index.load(std::memory_order_acquire);
}