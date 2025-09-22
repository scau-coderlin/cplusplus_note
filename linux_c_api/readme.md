# 学习链接
https://www.bilibili.com/video/BV18p4y167Md/?share_source=copy_web&vd_source=d3c3ec7afde55359bf8b5ca5786f3221

# 相关知识
## 查看进程返回值
```sh
echo $? # 返回上一个进程的返回值
```

## errno相关
1. 定义所在头文件
```sh
/usr/include/asm-generic/errno-base.h
/usr/include/asm-generic/errno.h
```
2. 查看errno函数
```c
#include <string.h>

/// @brief 根据错误码，返回对应的错误描述字符串
/// @return 成功返回对应的错误码描述，失败返回 "Unknown error nnn"
/// @note Before glibc 2.32, strerror() is not MT-Safe.
char *strerror(int errnum);
```


# I/O
> 一切实现的基础

