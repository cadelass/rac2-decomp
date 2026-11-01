/* func_002E3BD8, Claude Opus 5.5 (opus-1 tier), USA v1.01.
 * Best: 632/628 bytes, 0/28 places (check.py); one extra instruction.
 * Twin of func_002E3998 (same body, func_002E3FA0 as renderer, then the
 * TEST_1/ZBUF_1 writes, which match).
 * Upstream compiler, -O2 -G8 -ffunction-sections (a <file>-g8.c unit).
 * Everything else matches, including the VLA prologue, the DMA packet (no
 * volatile needed: the stores are written as *(int *)(D_001B22A8 + n), whose
 * NOP_EXPR address is not MEM_IN_STRUCT, so every store kills the cursor load
 * as in retail; strict aliasing is off), the bank toggles and the prefetch.
 * Only the render block differs: retail loads offset2 straight into $a3 and
 * adds it from there (lh a3,0x2C(s0); addu s1,a0,a3); this C loads it into
 * $v0 and copies it to $a3 (+1 insn), so offset1/offset0 take v0/t0 -> t0/t1
 * and the two pointer adds swap.
 * Cause (dumps, tools/regalloc.py): haifa sched1 issues the a3 argument copy
 * as soon as offset2 is loaded (t=6), while first = base + offset2 waits for
 * the base load (t=8); offset2 then outlives the copy, so local-alloc cannot
 * tie it to $a3. No C order changes that: first/second before/after, separate
 * load expression, short/long/int types, const-free reorder, pointers after
 * the call all tie or get worse. -fno-schedule-insns gives the a3 tie and the
 * exact size but breaks the packet and loop scheduling (47 lines differ);
 * the rc2 profile (-mno-split-addresses) is worse (596 bytes).
 * Chunk records are 32 bytes from obj+16 (vec4 sphere for func_002E4388,
 * then data/count/mode/offset0..2/packed); the ChunkView view from
 * obj + i*32 keeps retail's single base register (a Chunk array access adds
 * a separate +16 or swaps s3/s4). No linked build run.
 */
#include "common.h"

typedef struct {
    float sphere[4];
    int data;
    short count;
    short mode;
    short offset0;
    short offset1;
    short offset2;
    unsigned short packed;
} Chunk;

typedef struct {
    int count;
    int mode;
    int pad[2];
    Chunk chunks[1];
} ChunkList;

/* Chunk I's fields, viewed from obj + I * 32 (the header and chunk I-1's tail lead). */
typedef struct {
    char leading[32];
    int data;
    short count;
    short mode;
    short offset0;
    short offset1;
    short offset2;
    unsigned short packed;
} ChunkView;

#define CHUNK(obj, i) ((ChunkView *)((char *)(obj) + (i) * 32))

extern char *D_001B22A8;
extern int D_001ABDE0 __attribute__((sda));
extern char *D_001ABDD8[2] __attribute__((sda));
extern char D_00139370[];
extern char D_00139300[];
extern int D_001A72E0;

extern void func_002E4388(void *, int, void *);
extern void func_0029CF58(int, int, void *);
extern void func_0029CF78(void);
extern int func_002E3E54(void *, void *, int, int);
extern void func_002E40C8(int, void *, void *, void *);
extern void func_002E3FA0(int, void *, void *, void *);
extern void func_002FC560(unsigned int, unsigned long long);

void func_002E3BD8(void *object)
{
    ChunkList *list = object;
    char *obj = object;
    int count = list->count;
    unsigned char flags[count];
    int i;

    if (count == 0)
        return;
    func_002E4388(obj + 16, count, flags);
    *(int *)(D_001B22A8 + 0) = 0x30000007;
    *(char **)(D_001B22A8 + 4) = D_00139300;
    *(int *)(D_001B22A8 + 8) = 0;
    *(int *)(D_001B22A8 + 12) = 0x50000007;
    D_001B22A8 = D_001B22A8 + 16;
    D_001ABDE0 = 1 - D_001ABDE0;
    if (flags[0] == 1)
        func_0029CF58(list->chunks[0].data, (short)list->chunks[0].packed >> 4, D_001ABDD8[D_001ABDE0]);
    for (i = 0; i < list->count; i++) {
        int next;
        char *base;
        char *first;
        char *second;
        int size;

        if (flags[i] == 1)
            func_0029CF78();
        next = i + 1;
        {
            int total = list->count;

            D_001ABDE0 = 1 - D_001ABDE0;
            if (next < total && flags[next] == 1) {
                ChunkView *chunk = CHUNK(obj, next);

                func_0029CF58(chunk->data, (short)chunk->packed >> 4, D_001ABDD8[D_001ABDE0]);
            }
        }
        if (flags[i] == 1) {
            ChunkView *chunk = CHUNK(obj, i);

            base = D_001ABDD8[1 - D_001ABDE0];
            second = base + chunk->offset1;
            size = chunk->offset2;
            first = base + size;
            if (!func_002E3E54(base + chunk->offset0, (void *)0x70002000, chunk->count, size))
                func_002E3FA0(chunk->mode, first, second, (void *)0x70002000);
        }
    }
    func_002FC560(0x47, 0x3180B);
    func_002FC560(0x4E, (((long long)(D_001A72E0 >> 13) | 0x1000000) | (1LL << 32)));
}
