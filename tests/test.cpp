#include <iostream>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <aes-tbox.h>
#include <x86intrin.h>

int main()
{
    // 示例输入
    std::array<uint8_t, 16> plaintext = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    std::array<uint8_t, 16> ciphertext = {0}; // 初始化为全 0
    std::array<uint8_t, 16> key = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};

    // 密钥拓展
    unsigned long long start_cycles = __rdtsc();
    AES_key_expansion(key);
    unsigned long long end_cycles = __rdtsc();
    printf("aes cycles: %llu\n", end_cycles - start_cycles);
    double cpu_hz = 2.5e9; // 你的CPU主频，单位Hz（比如2.5GHz）
    unsigned long long cycles = end_cycles - start_cycles;
    double seconds = cycles / cpu_hz;
    // printf("aes latency: %.10f s\n", seconds);
    // printf("aes latency: %.10f ms\n", seconds*1000);
    printf("aes key expansion latency: %.3f us\n", seconds * 1000000);

    ciphertext = plaintext;
    // 测试单组延迟
    start_cycles = __rdtsc();
    AES_round(ciphertext);
    end_cycles = __rdtsc();
    printf("aes cycles: %llu\n", end_cycles - start_cycles);
    cycles = end_cycles - start_cycles;
    seconds = cycles / cpu_hz;
    printf("aes encryption latency: %.3f us\n", seconds * 1000000);

    int i;
    // // 输出ciphertext
    // std::cout << "ciphertext: ";
    // for (i = 0; i < 16; i++)
    // {
    //     std::cout << std::hex << static_cast<int>(ciphertext[i]) << " ";
    // }
    // std::cout << std::endl;

    // 测试吞吐量，单线程
    int max_num = 1024 * 1024 * 10;//160MiB
    auto start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < max_num; i++)
    {
        // AES 轮
        AES_round(ciphertext);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    // 计算吞吐量
    double throughput = 160 / elapsed.count();
    printf("aes time: %.3f s\n", elapsed.count());
    printf("aes throughput: %.3f MiB/s\n", throughput);
    printf("aes throughput: %.3f Gib/s\n", 8*throughput/1024);

    return 0;
}