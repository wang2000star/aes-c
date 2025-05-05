#pragma once

#include <iostream>
#include <array>
#include <cstring>
//#include <emmintrin.h> // SSE2

const size_t Nr = 10; // AES-128 轮数,Nr>=3
const size_t Nr_2 = Nr - 2; 
const size_t roundkey_size = 4 * (Nr + 1); // AES-128 密钥扩展后的密钥长度

void AES_key_expansion(const std::array<uint8_t, 16> &key);

void AES_round(std::array<uint8_t, 16> &x);
// AES_TBOX_H