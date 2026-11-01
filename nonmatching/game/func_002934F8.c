/* GPT-6.1 Sol high, 2026-10-29: 916/916 bytes, 0/28 USA v1.01 places.
 * Default -O2 -G0 -ffunction-sections, pinned v2 worker toolchain.
 * qcopy from common.h reproduces the final map-transfer instructions exactly.
 * Explicit extra-group and part-slot pointers fix both address operand orders.
 * Compaction still hoists data+16 before its loop (retail constructs it after),
 * swaps entry/counter registers and adds alignment padding. Part-loop setup
 * and its inner counter initialization also differ. Passing final loop cursors
 * to the copy helper removes instructions (908 bytes), but does not match;
 * reloading entry->data instead produces an unwanted load. Typed Group fields,
 * integer address casts, and function-scope compaction cursors did not help.
 * qcopy_nc tied qcopy; the clobbering helper remains the conservative choice.
 * Needs common.h plus the local declarations below; no custom compiler flags.
 */
#include "common.h"
typedef unsigned char U8;
typedef unsigned int Q128 __attribute__((mode(TI)));
extern void func_0026FEB8(const char *, ...);
extern void func_00282B50(void *destination, void *source, int bytes);

extern const char D_001B9240[];
extern U8 D_001CE4E0[];
extern int D_001D0E00[];
extern Q128 D_001D1580[];
extern void func_002932B8(int *, char *, U8 *, int);

void func_002934F8(U8 *block, void *textures, U8 *map, int index)
{
    int compressed = block[0xB] != 0;
    int count;
    if (compressed) {
        int size;
        func_0026FEB8(D_001B9240, index);
        size = *(int *)(block + 0x2C);
        if (size > 0x3FC00) size = 0x3FC00;
        block[0xB] = 0;
        block[0x2C] = 0;
        *(short *)(block + 0x2E) = 0;
        block[0x2D] = size >> 10;
        D_001D0E00[D_001CE4E0[index]] = size;
    }
    count = block[4] + block[5] + block[6];
    if (block[0x2C]) {
        U8 *extra = block + block[0x2C] * 16;
        count += extra[1];
    }
    if (*(int *)block) {
        int packet_index;
        U8 *entry;
        *(int *)block = (int)block + *(int *)block;
        entry = *(U8 **)block;
        for (packet_index = 0; packet_index < count; ++packet_index, entry += 16) {
            U8 *data = (U8 *)(*(int *)(entry + 8) + (int)block);
            int first_two, all_three;
            *(U8 **)(entry + 8) = data;
            *(int *)entry += (int)block;
            first_two = block[4] + block[5];
            all_three = first_two + block[6];
            if (compressed && (packet_index < first_two || packet_index >= all_three)) {
                int j;
                unsigned short *destination = (unsigned short *)data;
                unsigned short *source = (unsigned short *)data;
                for (j = 7; j >= 0; --j) {
                    *destination++ = *source;
                    source += 2;
                }
                *(unsigned short *)(data + 0xE) = 0;
                *(unsigned short *)(data + 0xC) = *(unsigned short *)(data + 0x18) - 16;
                func_00282B50(data + 16, data + 32, (entry[0xC] - 2) * 16);
            }
        }
    }
    if (*(int *)(block + 0x10)) *(int *)(block + 0x10) = (int)block + *(int *)(block + 0x10);
    if (*(int *)(block + 0x14)) *(int *)(block + 0x14) = (int)block + *(int *)(block + 0x14);
    if (*(int *)(block + 0x18)) *(int *)(block + 0x18) = (int)block + *(int *)(block + 0x18);
    if (*(int *)(block + 0x1C)) {
        int n, relocation_index;
        *(int *)(block + 0x1C) = (int)block + *(int *)(block + 0x1C);
        n = **(int **)(block + 0x1C);
        for (relocation_index = 0; relocation_index < n; ++relocation_index)
            (*(int **)(block + 0x1C))[relocation_index + 1] += (int)block;
    }
    if (*(int *)(block + 0x20)) {
        U8 *entry;
        *(int *)(block + 0x20) = (int)block + *(int *)(block + 0x20);
        entry = *(U8 **)(block + 0x20);
        do {
            U8 *cursor = entry;
            *(int *)(entry + 0xC) += (int)block;
            if (*cursor != 255) {
                do {
                    *cursor = map[*cursor];
                    ++cursor;
                } while (*cursor != 255);
            }
            if (*(int *)(entry + 0xC) < 0) break;
            entry += 16;
        } while (1);
    }
    if (*(int *)(block + 0x28)) *(int *)(block + 0x28) = (int)block + *(int *)(block + 0x28);
    if (block[0xC]) {
        int part_index = 0;
        int *parts = (int *)(block + 0x48);
        do {
            U8 *part;
            int *slot = (int *)((char *)parts + part_index * 4);
            if (*slot) {
                part = block + *slot;
                *(U8 **)slot = part;
                if (*(int *)(part + 0x14)) *(int *)(part + 0x14) = (int)part + *(int *)(part + 0x14);
                if (part[0x10]) {
                    int j = 0;
                    int *p = (int *)(part + 0x1C);
                    do {
                        *p = (int)block + *p;
                        ++j;
                        ++p;
                    } while (j < part[0x10]);
                }
            }
            ++part_index;
        } while (part_index < block[0xC]);
    }
    if (index >= 0) qcopy(&D_001D1580[D_001CE4E0[index]], map);
    if (*(void **)block)
        func_002932B8(*(int **)block, textures, map, count);
}
