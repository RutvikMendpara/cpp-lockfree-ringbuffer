#include <iostream>
#include "ring_buffer_single_threaded.h"

int main() {
	/*
		Single-threaded ring buffer.
		Not thread-safe. Not lock-free.
		Capacity is (N - 1) due to reserved slot for full/empty distinction.
		Writes are rejected when full; reads are rejected when empty.
		Indexing is always in bounds - no overflow risk by design.
	*/

	RingBuffer q;
	std::cout << "q.isEmpty() " << q.isEmpty() << std::endl;
	for (int i = 0; i < 5; ++i) {
		std::cout << "put(" << i << ") => " << q.put(i) << "\n";
	}

	std::cout << "q.capacity() " << q.capacity() << std::endl;
	std::cout << "q.isEmpty() " << q.isEmpty() << std::endl;
	int val;
	while (q.get(val)) {
		std::cout << "get: " << val << "\n";
	}

	std::cout << "q.isEmpty() " << q.isEmpty() << std::endl;
	return 0;
}