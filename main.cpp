#include <iostream>
#include <thread>
#include "ring_buffer_single_threaded.h"
#include "spsc_ring_buffer.h"

SPSCQueue spsc_q;

void producer() {
	for (int i = 0; i < 1500; ++i) {
		while (!spsc_q.put(i)) {
			// busy-wait
		}
	}
}


void consumer() {
	int val;
	for (int i = 0; i < 1500; ++i) {
		while (!spsc_q.get(val)) {
			// busy-wait
		}
		std::cout << val << "\n";
	}
}


int main() {

	std::thread prod(producer);
	std::thread cons(consumer);

	prod.join();
	cons.join();

	std::cout << "Test complete\n";


	return 0;
}