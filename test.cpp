/*
 * Copyright (c) 2026 MarchBeta2087
 *
 * SPDX-License-Identifier: MIT
 * 
 * pow2_utils 测试程序。
 * 
 * Test program of pow2_utils.
 * 
 */
#include <stdio.h>
#include "pow2_utils.hpp"

void pow2_test_u8(unsigned char n){
    const bool ispow2 = pow2::checkpow2(n);
    const int exp = pow2::get_power_of_exp2(n);
    printf("%u, ", n);
    printf(pow2::checkpow2(n) ? "true, ": "false, ");
    printf("%d\n", exp);
}

void pow2_test_u16(unsigned short n){
    const bool ispow2 = pow2::checkpow2(n);
    const int exp = pow2::get_power_of_exp2(n);
    printf("%u, ", n);
    printf(pow2::checkpow2(n) ? "true, ": "false, ");
    printf("%d\n", exp);
}

void pow2_test_u32(unsigned int n){
    const bool ispow2 = pow2::checkpow2(n);
    const int exp = pow2::get_power_of_exp2(n);
    printf("%u, ", n);
    printf(pow2::checkpow2(n) ? "true, ": "false, ");
    printf("%d\n", exp);
}

void pow2_test_u64(unsigned long long n){
    const bool ispow2 = pow2::checkpow2(n);
    const int exp = pow2::get_power_of_exp2(n);
    printf("%llu, ", n);
    printf(pow2::checkpow2(n) ? "true, ": "false, ");
    printf("%d\n", exp);
}

int main() {
    printf("\n=== Test u8 ===\n");

    for(unsigned char i = 0; i <= 9; i++){
        pow2_test_u8(i);
    }

    for(unsigned char i = 16; i <= 0x80; i <<= 1){
        if(i == 0){
            break;
        }
        pow2_test_u8(i - 1);
        pow2_test_u8(i);
        pow2_test_u8(i + 1);
    }

    printf("\n=== Test u16 ===\n");

    for(unsigned short i = 0; i <= 9; i++){
        pow2_test_u16(i);
    }

    for(unsigned short i = 16; i <= 0x8000; i <<= 1){
        if(i == 0){
            break;
        }
        pow2_test_u16(i - 1);
        pow2_test_u16(i);
        pow2_test_u16(i + 1);
    }

    

    printf("\n=== Test u32 ===\n");

    for(unsigned int i = 0; i <= 9; i++){
        pow2_test_u32(i);
    }

    for(unsigned int i = 16; i <= 0x80000000; i <<= 1){
        if(i == 0){
            break;
        }
        pow2_test_u32(i - 1);
        pow2_test_u32(i);
        pow2_test_u32(i + 1);
    }

    printf("\n=== Test u64 ===\n");

    for(unsigned long long i = 0; i <= 9; i++){
        pow2_test_u64(i);
    }

    for(unsigned long long i = 16; i <= 0x8000000000000000; i <<= 1){
        if(i == 0){
            break;
        }
        pow2_test_u64(i - 1);
        pow2_test_u64(i);
        pow2_test_u64(i + 1);
    }

    return 0;
}