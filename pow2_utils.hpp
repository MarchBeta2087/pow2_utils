/*
 * Copyright (c) 2026 MarchBeta2087
 *
 * SPDX-License-Identifier: MIT
 * 
 * pow2_utils: 判断一个数是否为 2 的幂，以及判断一个数是 2 的多少次幂。
 * 
 * pow2_utils: Determines whether a number is a power of 2, and determines how many times a number is a power of 2.
 * 
 */
#ifndef POW2_UTILS_HPP
#define POW2_UTILS_HPP

#include <type_traits>

// 1. 特性检测：处理 C++20 <bit> 库
#if defined(__cpp_lib_bitops) && __cpp_lib_bitops >= 201907L
    #include <bit>
    #define HAS_BIT_LIB 1
#else
    #define HAS_BIT_LIB 0
#endif

// 2. 特性检测：处理 constexpr 限制
// C++11 的 constexpr 非常严格（只能有一条 return 语句）
// C++14 之后放宽了限制
#if __cplusplus >= 201402L
    #define POW2_CONSTEXPR14 constexpr
#else
    #define POW2_CONSTEXPR14 inline
#endif

// 3. 编译器内置函数支持 (Intrinsics)
#ifdef _MSC_VER
    #include <intrin.h>
#endif

namespace pow2 {

/**
 * @brief 检查是否为 2 的幂
 */
template<typename T>
constexpr bool checkpow2(T n) noexcept {
    static_assert(std::is_integral<T>::value && std::is_unsigned<T>::value, 
                  "Only unsigned types are supported");
    
#if HAS_BIT_LIB
    return std::has_single_bit(n);
#else
    // C++11 兼容写法：必须是单条 return 表达式
    return (n != 0) && ((n & (n - 1)) == 0);
#endif
}

/**
 * @brief 内部实现：获取 2 的幂次数 (n 必须已验证为 2 的幂且 > 0)
 */
namespace detail {
    // 针对旧版编译器的软件回退方案 (C++11 兼容)
    template<typename T>
    constexpr int log2_fallback(T n, int res) noexcept {
        return n <= 1 ? res : log2_fallback(n >> 1, res + 1);
    }

    // 处理各编译器内置指令
    template<typename T>
    inline int countr_zero_impl(T n) noexcept {
#if HAS_BIT_LIB
        return std::countr_zero(n);
#elif defined(__GNUC__) || defined(__clang__)
        if (sizeof(T) <= sizeof(unsigned int)) 
            return __builtin_ctz(static_cast<unsigned int>(n));
        else 
            return __builtin_ctzll(static_cast<unsigned long long>(n));
#elif defined(_MSC_VER)
        unsigned long index;
        #if defined(_M_X64) || defined(_M_ARM64)
            if (sizeof(T) <= sizeof(unsigned long)) {
                _BitScanForward(&index, static_cast<unsigned long>(n));
            } else {
                _BitScanForward64(&index, static_cast<unsigned __int64>(n));
            }
        #else
            if (sizeof(T) <= sizeof(unsigned long) || (n & 0xFFFFFFFF)) {
                _BitScanForward(&index, static_cast<unsigned long>(n));
            } else {
                _BitScanForward(&index, static_cast<unsigned long>(n >> 32));
                index += 32;
            }
        #endif
        return static_cast<int>(index);
#else
        return log2_fallback(n, 0);
#endif
    }
}

/**
 * @brief 获取 2 的幂次数。若不是 2 的幂，返回 -1
 */
template<typename T>
POW2_CONSTEXPR14 int get_power_of_exp2(T n) noexcept {
    static_assert(std::is_integral<T>::value && std::is_unsigned<T>::value, 
                  "Only unsigned types are supported");

    // 1. 验证合法性
    if (!checkpow2(n)) return -1;

    // 2. 如果是 C++20 且在常量折叠上下文，可以直接用 std::countr_zero
    // 否则在运行时使用优化指令
#if HAS_BIT_LIB
    return std::countr_zero(n);
#else
    // 对于 C++11/14/17，如果是常量表达式，编译器通常能优化简单循环
    // 如果是运行时，我们调用内置指令
    return detail::countr_zero_impl(n);
#endif
}

} // namespace pow2

#endif