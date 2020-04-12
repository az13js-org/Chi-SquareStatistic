# C语言计算卡方统计量

我写了个demo，直接用gcc编译就能看到效果

    gcc pearson.c main.c -O3 -o main && ./main

这个程序是利用卡方统计量来检测随机数生成独立性。

    i: 10328, s: 7.129658, believe: 0.990000
    i: 10329, s: 7.181652, believe: 0.990000
    i: 10330, s: 7.233819, believe: 0.990000
    i: 10331, s: 7.286161, believe: 0.990000
    i: 10332, s: 7.338636, believe: 0.990000
    i: 10343, s: 7.382905, believe: 0.990000
    i: 10344, s: 7.435702, believe: 0.990000
    i: 10345, s: 7.488712, believe: 0.990000
    i: 10346, s: 7.541874, believe: 0.990000
    i: 10347, s: 7.595210, believe: 0.990000
    i: 10348, s: 7.648779, believe: 0.990000

事实证明，种子为1的时候，生成随机数10000个随机数进行测试，无法通过卡方检测。

## 使用方法说明

1. 包含头文件`#include "pearson.h"`。
2. 声明计算使用的专门的结构体：`struct pear_data *pear_data;`。
3. 声明两个变量，`char *a`和`char *b`为一维的数组，长度一致填充0和非0的数据进去。这里的`0x00`和非`0x00`的数值会被统计为事件发生与否的两个状态。
4. `pear_data = pear_create_from_chars_reffer(len, a, b);`从定义的数组`a`和`b`创建带数据结构体`pear_data`。
5. `double seq = pear_get_chi_square(pear_data);`计算得到结果。
6. 用`pear_believe(seq)`映射得到置信度，用`pear_free(pear_data)`清空结构体。

```C
    struct pear_data *pear_data;
    char *a, *b;
    a = (char*)calloc(len, sizeof (char));
    b = (char*)calloc(len, sizeof (char));
    for (int i = 0; i < 10; i++) {
        a[i] = rand() & 0x01;
        b[i] = rand() & 0x01;
    }
    pear_data = pear_create_from_chars_reffer(len, a, b);
    seq = pear_get_chi_square(pear_data);
    pear_free(pear_data);
    free(a);
    free(b);
```
