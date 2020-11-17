# 索引数据结构

## 问题
1TB 数据量，4G 内存，4TB 硬盘存储空间。
数据格式为
```
key_size, key_data, value_size, value_data
```

## 思路
一个 kv 对至少 8B，则 1TB 至多 128G 个 kv 对，意味着索引文件大小远大于内存。因此将索引文件变成很多个小文件。

另外在建索引之后只需要进行读操作，所以哈希索引就能满足条件。而不用 B+ 树或者 LSM 树这样复杂的数据结构。

## 设计
1. 索引为一个哈希表，分区数 p 由 num_partitions 控制。每一个分区有若干个 IndexFile 文件。每个 IndexFile 的大小由 index_file_size 所控制。每个 IndexFile 里连续存放着 DataEntry。每个 DataEntry 与一个 kv 对一一对应，存储 kv 对的地址。
2. 在每一个 IndexFile 中，我加入了一个 BloomFilter，用于在查询 key 时能够减少读取文件内容的概率，加速访问。
3. 在 DataEntry 上，我存储 key 的一部分信息，尽可能通过 DataEntry 本身存储的内容来判断 key 值是否匹配，而不是通过指针间址访问原始的 kv 对。

## 代价分析
1. 建表：建表时，由于数据文件组织格式的原因，只能串行解析，需要生成至多 128G * 16Byte 的大小的文件，文件数量为 128G * 16B / index_file_size。(我认为 index file 的大小大概和内存大小除以分区数差不多。)
2. 查询：查询一个 key 值对应的 value。
   1. 生成 key 对应的哈希值，判断分区。此步代价取决于哈希函数的效率。
   2. 对于该分区的所有文件，遍历的判断 key 值是否对应 value。代价取决于一个分区的文件数量。
      1. 对于一个 index file 文件，先判断 bloom filter。代价取决于 bloom filter的假阳性的概率，可以通过增加一点 bloom filter所占有的内存空间，将假阳性的概率降到 0.1 以下。
      2. 如果 bloom filter 为真，则遍历的查询每个 DataEntry
         1. DataEntry 先通过存储的一部分 key 的信息，判断是否匹配。
         2. 如果部分匹配则间址查询原始的 kv 对。