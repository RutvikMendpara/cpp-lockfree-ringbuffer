# initial_research_notes

- Circular buffer (ring buffer) is a fixed-size array-based data structure used to implement a queue (FIFO).
- It has two moving pointers: head (write) and tail (read).
- Pushing writes data at the head; popping reads data from the tail.
- When the buffer reaches the end, the pointers wrap around to the beginning.
- For performance, use `index & (size - 1)` instead of modulo, if the size is a power of 2.
- Common in real-time systems like audio/video processing and network pipelines.
- When the buffer is full, either:
  - Prevent new writes (standard queue behavior), or
  - Overwrite old data (only if intentional)
- Can be implemented as lock-free, depending on concurrency model.
- Supports multiple concurrency variants:
  - SPSC: Single Producer, Single Consumer (lock-free, simplest)
  - MPSC: Multiple Producers, Single Consumer
  - SPMC: Single Producer, Multiple Consumers
  - MPMC: Multiple Producers, Multiple Consumers
