# pow2_utils

## 简体中文/Simplified Chinese

pow2_utils: 判断一个数是否为 2 的幂，以及判断一个数是 2 的多少次幂。

调用`pow2_utils.hpp`，使用这些函数，让你的开发更加便捷：

`pow2::checkpow2`: 判断一个数是否为 2 的幂。

`pow2::get_power_of_exp2`: 判断一个数是 2 的多少次幂。如果这个数不是 2 的幂，返回 -1。

各编译器的**最低支持版本**如下：

### 基础要求（C++11 模式）

代码依赖 `constexpr`（C++11）、`noexcept` 和 `<type_traits>`，因此最低需要：

| 编译器 | 最低版本 | 说明 |
| -------- | --------- | ------ |
| **GCC** | **4.6+** | 4.6 引入基本 `constexpr` 支持，推荐 **4.8.1+**（完整 C++11 支持） |
| **Clang** | **3.1+** | 3.1 实现 C++11，推荐 **3.3+**（完整支持） |
| **MSVC** | **2015 (19.0)** | 首个支持 `constexpr` 和 `noexcept` 的版本，避免 2013 及更早版本 |

### 优化路径版本要求

#### 1. C++14 扩展 constexpr（放宽限制）

代码中 `POW2_CONSTEXPR14` 宏在 C++14 下启用更宽松的 `constexpr`：

- **GCC**: 5.0+
- **Clang**: 3.4+
- **MSVC**: 2015 Update 2+ 或 **2017+**（推荐）

#### 2. C++20 `<bit>` 库（最优路径）

使用 `std::has_single_bit` 和 `std::countr_zero`：

- **GCC**: **11.0+**（libstdc++ 需完整支持）
- **Clang**: **14.0+**（需配合 libc++ 或 libstdc++-11+）
- **MSVC**: **2019 16.8+** 或 **2022**

#### 3. 编译器内置函数（Intrinsics）

| 特性 | 编译器 | 最低版本 |
| ------ | -------- | --------- |
| `__builtin_ctz`/`ctzll` | GCC | 3.4+（实际上任何现代版本） |
| `__builtin_ctz`/`ctzll` | Clang | 3.0+（兼容 GCC 内置函数） |
| `_BitScanForward` | MSVC | 2005 (8.0)+ |
| `_BitScanForward64` | MSVC | 2005+（**需 x64/ARM64 目标架构**） |

### 兼容性总结

C++11 Fallback（全功能）: GCC 4.6+ / Clang 3.1+ / MSVC 2015+
C++14 优化:               GCC 5+   / Clang 3.4+ / MSVC 2017+
C++20 最优:               GCC 11+  / Clang 14+  / MSVC 2019 16.8+

### 注意事项

1. **MSVC 32 位编译**：`_BitScanForward64` 在 x86 架构下不可用，代码中通过 `n >> 32` 分两次处理回退
2. **constexpr 上下文**：即使在 C++11 下，编译器通常仍能在编译期计算简单递归（`log2_fallback`），但循环体限制为单条 return 语句
3. **C++20 检测**：依赖 `__cpp_lib_bitops >= 201907L`，若编译器支持 C++20 但标准库过旧（如旧版 libstdc++），将回退到内置函数或软件实现

---

## 英语/English

pow2_utils: Determines whether a number is a power of 2, and determines how many times a number is a power of 2.

Call `pow2_utils.hpp` and use these functions to make your development easier:

`pow2::checkpow2`: Determines if a number is a power of 2.

`pow2::get_power_of_exp2`: Determines what power of 2 a number is. Returns -1 if the number is not a power of 2.

**The minimum supported versions** for each compiler are as follows:

### Basic Requirements (C++11 Mode)

The code depends on `constexpr` (C++11), `noexcept`, and `<type_traits>`, therefore the minimum required versions are:

| Compiler | Minimum Version | Description |

| -------- | --------- | ------ |

| **GCC** | **4.6+** | Version 4.6 introduces basic `constexpr` support; version 4.8.1+ is recommended (full C++11 support) |

| **Clang** | **3.1+** | Version 3.1 implements C++11; version 3.3+ is recommended (full support) |

| **MSVC** | **2015 (19.0)** | The first version to support `constexpr` and `noexcept`, avoiding versions 2013 and earlier |

### Optimization Path Version Requirements

#### 1. C++14 Extensions constexpr (Relaxed Restrictions)

The macro `POW2_CONSTEXPR14` in the code enables a more relaxed `constexpr` in C++14:

- **GCC**: 5.0+

- **Clang**: 3.4+

- **MSVC**: 2015 Update 2+ or **2017+** (Recommended)

#### 2. C++20 `<bit>` Library (Optimal Path)

Using `std::has_single_bit` and `std::countr_zero`:

- **GCC**: **11.0+** (requires full support from libstdc++)

- **Clang**: **14.0+** (requires libc++ or libstdc++-11+)

- **MSVC**: **2019 16.8+** or **2022**

#### 3. Compiler Intrinsics

| Features | Compiler | Minimum Version |

| ------ | -------- | --------- |

| `__builtin_ctz`/`ctzll` | GCC | 3.4+ (virtually any modern version) |

| `__builtin_ctz`/`ctzll` | Clang | 3.0+ (compatible with GCC intrinsics) |

| `_BitScanForward` | MSVC | 2005 (8.0)+ |

| `_BitScanForward64` | MSVC | 2005+ (**Requires x64/ARM64 target architecture**) |

### Compatibility Summary

C++11 Fallback (Full-featured): GCC 4.6+ / Clang 3.1+ / MSVC 2015+

C++14 Optimized: GCC 5+ / Clang 3.4+ / MSVC 2017+

C++20 Optimal: GCC 11+ / Clang 14+ / MSVC 2019 16.8+

### Notes

1. **MSVC 32-bit compilation**: `_BitScanForward64` is not available on x86 architecture. The code handles the fallback twice using `n >> 32`.

2. **constexpr context**: Even in C++11, the compiler can usually still compute simple recursion (`log2_fallback`) at compile time, but the loop body is limited to a single return statement.

3. **C++20 detection**: Depends on `__cpp_lib_bitops >= 201907L`. If the compiler supports C++20 but the standard library is outdated (such as an older version of libstdc++), it will fall back to built-in functions or software implementations.
