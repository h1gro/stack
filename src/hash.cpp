#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "../include/global.h"
#include "../include/hash.h"

uint_least32_t HashCalcs(void* buffer, int size)
{
    uint_least32_t crc_table[256];
    uint_least32_t crc;

    for (int i = 0; i < 256; i++)
    {
        crc = i;
        for (int j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;

        crc_table[i] = crc;
    };

    crc = 0xFFFFFFFFUL;

    while (size--)
        crc = crc_table[(crc ^ ((int*)buffer)[size]) & 0xFF] ^ (crc >> 8);

    return crc ^ 0xFFFFFFFFUL;
}
