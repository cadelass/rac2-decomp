/* GPT-6.1 Sol high, USA v1.01, game -O2 -G8 -ffunction-sections.
 * Best check: 1260/1260 bytes, 0/16 places; first difference +0x80.
 * Indexed traversal restores the retail 0x140 frame and three distinct
 * position induction pointers. Separate per-case object pointers restore
 * the moby/tie/shrub allocations; splitting the average into += then *=
 * restores the f20/f21 allocation and floating call schedule.
 * Retail keeps constant 1 in s7 and spills the third position cursor;
 * this draft keeps that cursor in s7 and rematerializes the constant.
 * Periodic activation also differs: retail reloads period and conditionally
 * clears an initially true flag, while this draft emits a boolean sltiu.
 * Clamp constant allocation and some setup ordering still differ.
 * A declared volatile period field with a local guard snapshot adds redundant
 * andi instructions and is worse (1268 bytes); it is not retained here.
 * -fno-cse-follow-jumps does not help; -fno-expensive-optimizations does not
 * fix the flag or cursor allocation. The sentinel-period switch is 1252 bytes.
 * Next: recover the activation flag's real lifetime before further allocation
 * trials. All required declarations are included; no linked build attempted.
 */
#include "common.h"
typedef int V4TI_F36d8a248 __attribute__((mode(TI)));
typedef union { float f[4]; V4TI_F36d8a248 q; } B1320Vec;
extern void func_00283698(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_0029FC20(void *, int, void *);
extern void func_002833F0(void *, void *);
extern void func_00283678(void *, void *);
extern void func_00283738(void *, void *, void *);
extern int func_L00_00323338(void *, void *, int, void *, void *, void *, void *);
extern int func_002A7820(int, int);
extern int D_L00_001B1EB8;
extern short *D_L00_001FA920[];
extern char *D_L00_001B1E9C;
extern int D_L00_001A9018;
extern short **D_L00_001A9014 __attribute__((sda));
extern char *D_L00_001B251C;
extern int D_L00_001A9020 __attribute__((sda));
extern short **D_L00_001A901C;
extern char *D_L00_001B2400;
typedef struct {
    char transform[48];
    float position[4];
    void *offset;
    void *attachment;
    short index;
    unsigned char end, joint, type, copy_matrix, period, phase;
} B1320Entry;
extern void func_00282B50(void *, void *, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CA8(void *, void *, void *);
extern void func_00283658(void *, void *);
extern void func_002AB6D8(void *, void *);
extern void func_002A0F48(void *);
extern void func_L00_0036AE00(int, int);
extern float func_00282DF0(void *);
extern int func_002EF250(float);
extern void func_00282D60(void *, void *, float);
extern int D_L00_001B19C8 __attribute__((sda));
extern char *D_L00_001B23F8;
extern char *D_L00_0021EA20[];
void func_L00_00323958(char *object, B1320Entry *entries)
{
    char matrix[64] __attribute__((aligned(16)));
    char temp[64] __attribute__((aligned(16)));
    char rotation[64] __attribute__((aligned(16)));
    unsigned int i;
    float x, y;
    int sx, sy, active;
    if (!entries->end) return;
    if (entries->copy_matrix) func_00282B50(matrix, object + 0xC0, 48);
    else func_002833F0(matrix, object + 0xF0);
    qcopy_nc(matrix + 48, object + 0x10);
    *(int *)(matrix + 60) = 0;
    i = 0;
    do {
        if (entries[i].attachment) {
            func_0029FC20(entries[i].attachment, entries[i].joint, temp);
            func_00283678(matrix, temp);
        }
        switch (entries[i].type) {
        case 0:
            func_00283098(temp, entries[i].position, matrix);
            func_00282CC0(D_L00_001B1E9C + entries[i].index * 256 + 0x10, matrix + 48, temp);
            if (entries[i].offset) func_00282CC0(D_L00_001B1E9C + entries[i].index * 256 + 0x10, D_L00_001B1E9C + entries[i].index * 256 + 0x10, (char *)entries[i].offset + 0x10);
            break;
        case 1:
            func_00283098(temp, entries[i].position, matrix);
            func_00282CA8(D_L00_001B251C + entries[i].index * 64 + 0x30, matrix + 48, temp);
            break;
        case 2:
            func_00283098(temp, entries[i].position, matrix);
            func_00282CA8(D_L00_001B2400 + entries[i].index * 64 + 0x30, matrix + 48, temp);
            break;
        }
        switch (entries[i].type) {
        case 0: {
            char *item;
            item = D_L00_001B1E9C + entries[i].index * 256;
            if (!*(int *)(item + 0x24)) func_002833F0(item + 0xC0, item + 0xF0);
            func_00283738(item + 0xC0, matrix, &entries[i]);
            if (entries[i].offset) {
                func_002833F0(temp + 16, entries[i].offset);
                func_00283738(item + 0xC0, item + 0xC0, temp + 16);
            }
            if (!*(int *)(item + 0x24)) {
                func_00283658(rotation, item + 0xC0);
                func_002AB6D8(rotation, item + 0xF0);
            }
            break;
        }
        case 1: {
            char *item;
            item = D_L00_001B251C + entries[i].index * 64;
            func_00283738(item, matrix, &entries[i]);
            if (entries[i].offset) {
                func_002833F0(temp + 16, entries[i].offset);
                func_00283738(item, item, temp + 16);
            }
            break;
        }
        case 2:
            func_00283738(D_L00_001B2400 + entries[i].index * 64, matrix, &entries[i]);
            break;
        }
        switch (entries[i].type) {
        case 0: {
            char *item;
            item = D_L00_001B1E9C + entries[i].index * 256;
            if (*(int *)(item + 0x24)) func_002A0F48(item);
            break;
        }
        case 1:
            active = 0;
            if (entries[i].period == 0) active = 1;
            else if (entries[i].period != 255) {
                active = D_L00_001B19C8 % entries[i].period;
                active = active == entries[i].phase ? 1 : 0;
            }
            func_L00_0036AE00(entries[i].index, active);
            break;
        case 2: {
            char *item, *data;
            item = D_L00_001B2400 + entries[i].index * 64;
            data = D_L00_001B23F8 + entries[i].index * 32;
            x = func_00282DF0(item);
            x += func_00282DF0(item + 0x10);
            x *= 0.5f;
            y = func_00282DF0(item + 0x20);
            sx = func_002EF250(x * 4096.0f);
            sy = func_002EF250(y * 4096.0f);
            if (sy > 65536) sy = 65536;
            if (sx > 65536) sx = 65536;
            *(int *)(item + 0x2C) = sx | (sy << 16);
            func_00283098(data, D_L00_0021EA20[(unsigned char)data[0x1A]], item);
            func_00282D60(data, data, *(float *)(item + 0x3C));
            func_00282CC0(data, data, item + 0x30);
            break;
        }
        }
    } while (entries[i++].end != 1);
}
