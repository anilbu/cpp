## Container Adapters

Bir container'i member olarak kullanan soyut veri yapisini implement eden adaptorlerdir. 

> :information_source: 
> **Abstract Data Type** (ADT) ile implementasyondan bagimsiz bir veri yapisi kastediliyor. 

|                       | ADT                                | default       |  header   |
| --------------------- | ---------------------------------- | ------------- | :-------: |
| `std::stack`          | LIFO                               | `std::deque`  | `<stack>` |
| `std::queue`          | FIFO                               | `std::deque`  | `<queue>` |
| `std::priority_queue` | Onceligi yuksek olanin ilk ciktigi | `std::vector` | `<queue>` |

Kendi interface'leri var ancak, member olarak kullandiklari container'lara cagri yaparlar. Bu nedenle adaptor olarak isimlendirilir.

> :triangular_flag_on_post: 
> Underlying container secilirken kullanima gore trade-off goz onune alinarak secilir.

