# Set-associative Cache Emulator

## Parameter
`Cache(unsigned long size_kb, int _way)`

## How to use

```
# set parameters (cache size, the number of ways) before building
$ make

$ cat input
0x2c4cc0
0x258740
0x1e6040
0x6dd00
0x2bcec0
0x3604c0
0x1e7600
0x1427c0
0x495980
0x3a6300
0x4fa600
...

$ ./cache_sim < input
n_hit: 3265, n_miss: 78655, sum: 81920
hit_rate: 0.03986
```

# Useful Websites

http://www.hardwaresecrets.com/how-the-cache-memory-works/8/

https://www.cs.umd.edu/class/sum2003/cmsc311/Notes/Memory/set.html