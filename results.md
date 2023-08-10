# Benchmark

- First ECS: 1.000.000 iterations, 1000 entities, 2 systems, 15.841s
- With entity allocation queue: 1.000.000 iterations, 1000 entities, 2 systems, 13.249s 
- With entity allocation queue: 1.000.000 iterations, 2000 entities, 1000 of which "dormant", 2 systems, 16.755s
- Using hash tables: -, -, -, -, timeout
- Sparse Set: -, -, -, -, 11.387s
