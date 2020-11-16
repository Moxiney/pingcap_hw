# Bloom Filter

## Interface
``` 
// 在 filter 中加入一个新的键值
1. Insert(RawData*)
// 判断 filter 中是否存在一个键值
2. bool Operator(RawData*)
```

## Implement

### Insert
1. 生成 k 个属于 [0, m) 的哈希值，将对应的位置置为 1。

## Find
1. 生成 k 个属于 [0, m) 的哈希值，将对应的位置置为 1。
2. 判断是否包含该 Byte 数组。