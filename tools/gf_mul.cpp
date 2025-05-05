#include <iostream>
#include <array>
#include <cstdint>

uint8_t gf_mul(uint8_t a, uint8_t b)
{
    uint8_t p = 0;
    for (int i = 0; i < 8; i++)
    {
        if (b & 1)
        {
            p ^= a;
        }
        bool high_bit_set = (a & 0x80);
        a <<= 1;
        if (high_bit_set)
        {
            a ^= 0x1B; // AES 的有限域多项式
        }
        b >>= 1;
    }
    return p;
}
uint8_t mul(uint8_t a,uint8_t b)
{
	uint8_t data[8],dat;
	data[0] = a;
	data[1] = data[0] << 1;
	if((data[0] & 0x80) == 0x80) data[1] ^= 0x1b;
	data[2] = data[1] << 1;
	if((data[1] & 0x80) == 0x80) data[2] ^= 0x1b;
	data[3] = data[2] << 1;
	if((data[2] & 0x80) == 0x80) data[3] ^= 0x1b;
	data[4] = data[3] << 1;
	if((data[3] & 0x80) == 0x80) data[4] ^= 0x1b;
	data[5] = data[4] << 1;
	if((data[4] & 0x80) == 0x80) data[5] ^= 0x1b;
	data[6] = data[5] << 1;
	if((data[5] & 0x80) == 0x80) data[6] ^= 0x1b;
	data[7] = data[6] << 1;
	if((data[6] & 0x80) == 0x80) data[7] ^= 0x1b;
	
	dat = 0x00;
	if((b & 0x01) == 0x01) dat ^= data[0];
	if((b & 0x02) == 0x02) dat ^= data[1];
	if((b & 0x04) == 0x04) dat ^= data[2];
	if((b & 0x08) == 0x08) dat ^= data[3];
	if((b & 0x10) == 0x10) dat ^= data[4];
	if((b & 0x20) == 0x20) dat ^= data[5];
	if((b & 0x40) == 0x40) dat ^= data[6];
	if((b & 0x80) == 0x80) dat ^= data[7];
	
	return dat;
}

int main()
{

    // for (int a = 0; a < 256; ++a)
    // for (int b = 0; b < 256; ++b)
    //     if (gf_mul(a, b) != mul(a, b))
    //         printf("diff: a=%02x b=%02x\n", a, b);
    // AES S 盒（TBox01），和优化后的查表（TBox02 和 TBox03）
    uint8_t Box02[256];
    uint8_t Box03[256];
    //printf("const uint8_t Box01[256] = {\n");
    int i;
    for (i = 0; i < 256; ++i)
    {
        Box02[i] = gf_mul(i, 0x02);
        Box03[i] = gf_mul(i, 0x03);
    }
    // 输出结果
    printf("const uint8_t Box02[256] = {\n");
    for (int i = 0; i < 256; ++i)
    {
        if (i != 255)
            printf("    0x%02X,%s", Box02[i], (i + 1) % 16 == 0 ? "\n" : " ");
        else
            printf("    0x%02X\n", Box02[i]);
    }
    printf("};\n");
    printf("const uint8_t Box03[256] = {\n");
    for (int i = 0; i < 256; ++i)
    {
        if (i != 255)
            printf("    0x%02X,%s", Box03[i], (i + 1) % 16 == 0 ? "\n" : " ");
        else
            printf("    0x%02X\n", Box03[i]);
    }
    printf("};\n");
    return 0;
}
// g++ gf_mul.cpp -o gf_mul
// ./gf_mul > gf_mul.txt