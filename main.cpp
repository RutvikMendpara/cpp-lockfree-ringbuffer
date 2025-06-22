#include <iostream>
#include <queue>
#include <mutex>
#include <atomic>
#include <chrono>
#include <thread>
#include "ring_buffer_single_threaded.h"
#include "spsc_ring_buffer.h"

// testing
void test_producer();
void test_consumer();
void testing_spsc_queue();

//benchmarking 
constexpr int N = 10'000'000;

// std::queue + mutex setup
std::queue<int> std_q;
std::mutex std_mtx;

// SPSC queue
SPSCQueue spsc_q;

void bench_std_queue() {
	std_q = {};
	auto start = std::chrono::high_resolution_clock::now();
		
	std::thread prod([] {
		for (int i = 0; i < N; ++i) {
			std::lock_guard<std::mutex> lock(std_mtx);
			std_q.push(i);
		}
		});

	std::thread cons([] {
		int cnt = 0;
		while (cnt < N) {
			std::lock_guard<std::mutex> lock(std_mtx);
			if (!std_q.empty()) {
				int val = std_q.front();
				std_q.pop();
				++cnt;
			}
		}
		});

	prod.join();
	cons.join();

	auto end = std::chrono::high_resolution_clock::now();
	auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "[std::queue + mutex] Time: " << dur.count() << " ms\n";
}

void bench_spsc_queue() {
	auto start = std::chrono::high_resolution_clock::now();

	std::thread prod([] {
		for (int i = 0; i < N; ++i) {
			while (!spsc_q.put(i)) {} // spin
		}
		});

	std::thread cons([] {
		int val, cnt = 0;
		while (cnt < N) {
			if (spsc_q.get(val)) ++cnt;
		}
		});

	prod.join();
	cons.join();

	auto end = std::chrono::high_resolution_clock::now();
	auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "[SPSC] Time: " << dur.count() << " ms\n";
}


int main() {
	for (int i = 0; i < 5; ++i) {
		std::cout << "--- Run " << (i + 1) << " ---\n";
		bench_std_queue();
		bench_spsc_queue();
		std::cout << "\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	
	return 0;
}

void test_producer() {
	for (int i = 0; i < 1500; ++i) {
		while (!spsc_q.put(i)) {
			// busy-wait
		}
	}
}

void test_consumer() {
	int val;
	for (int i = 0; i < 1500; ++i) {
		while (!spsc_q.get(val)) {
			// busy-wait
		}
		std::cout << val << "\n";
	}
}

void testing_spsc_queue()
{
	std::thread prod(test_producer);
	std::thread cons(test_consumer);

	prod.join();
	cons.join();

	std::cout << "Test complete\n";
}