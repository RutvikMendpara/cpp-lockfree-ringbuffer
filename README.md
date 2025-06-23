# Lock free SPSC Ring Buffer (Single Producer Single Consumer Ring Buffer)

## Overview:
- Lock free SPSC ring buffer using `std::atomic`.
- Optimized for high throughput communication between exactly **one producer and one consumer thread**.
- Uses a fixed size circular buffer with **power of two capacity** to enable bitmasking instead of modulo.

## Key Properties:
- Non blocking `put()` and `get()` operations (no locks or mutexes).
- Thread safe only under strict SPSC usage.
- Efficient wrapping using bitmask `(index  & (size - 1))`, requires m_size to be power of two.

## Memory Ordering:
- `put()`:
	- Uses `memory_order_relaxed` to read `write_index`.
	- Uses `memory_order_acquire` to read `read_index` (consumer progress).
	- Uses `memory_order_release` to publish `write_index` (after writing data).
- `get()`:
	- Uses `memory_order_relaxed` to read `read_index`.
	- Uses `memory_order_acquire` to read `write_index` (producer progress).
	- Uses `memory_order_release` to publish `read_index` (after consuming data).

## Limitations:
- **SPSC-only:** exactly one thread must produce, and exactly one must consume. Anything else = undefined behavior.
- Effective capacity is `m_size - 1` (one slot is reserved to differentiate full vs empty).
- No dynamic resizing . Fixed buffer at construction.
– No blocking or sleep, uses busy spin loops for contention handling.

## Usage Example:
```
SPSCQueue q;
q.put(42);
int value;
if (q.get(value)) { 
/* use value */ 
}
```


---

### Benchmark Results (10M ops)
> **Benchmarked on**: AMD Ryzen 5 3550H, 16GB RAM, Windows 11, 10M ops per run.

| Run | `std::queue` + `std::mutex` | `SPSCQueue` |
| --- | --------------------------- | ----------- |
| 1   | 10317 ms                    | 1631 ms     |
| 2   | 10753 ms                    | 1412 ms     |
| 3   | 11679 ms                    | 1514 ms     |
| 4   | 10266 ms                    | 1342 ms     |
| 5   | 10627 ms                    | 1261 ms     |

**Average speedup**: \~7–8x faster under SPSC conditions.

