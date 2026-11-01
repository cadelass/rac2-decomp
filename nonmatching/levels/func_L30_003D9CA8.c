/* Tier: opus-1, 29 October 2026 (v2/c02). USA v1.01: 460/436 bytes, 0/1 places.
 * Profile: own unit, -O2 -G8 -ffunction-sections -Wa,-G64 (e.g. L30_003D9CA8-g8.c;
 * -Wa,-G64 makes the 64-byte sda table D_L30_001B09B0 $gp-relative, and plain -G8 keeps
 * D_L30_001B9DC0 split into %hi/%lo as retail does).
 * Every instruction agrees except the 0x90-byte aggregate copy `f.packet = *source`:
 * this cc1 expands it through block_move_loop with ld/sd (4 ld + 4 sd per 32-byte step,
 * then ld/ld/sd/sd for the 16-byte leftover); retail has the same loop with lq/sq
 * (lq a2; lq a3; sq a2; sq a3; addiu v0; bne v0,a1; addiu v1, then lq a1 / sq a1): the
 * same registers (src v0, dst v1, end a1, scratches a2/a3, leftover a1, the zero in t1),
 * so 6 extra words in total. The prologue, FP registers and the rest match word for word.
 * Cause: output_block_move in config/mips/mips.c of gnu-ee-binutils-gcc-1.1 has no TImode
 * case (only ld/sd for align >= 8, ldl/ldr, lw, ...); retail's compiler used lq/sq for a
 * 16-byte aligned block. Unblock: a compiler recipe adding an R5900 `bytes >= 16 &&
 * align >= 16` lq/sq (TImode) case ahead of the ld/sd case, qualified on other
 * 16-aligned structure copies; no C wording reaches it.
 * Explicit TImode loop drafts (sol-high, 444 bytes; sol-low, 416 bytes) lose the
 * register roles: local-alloc gives the block-local quadword temporaries $v0/$v1 before
 * global-alloc places the pointers, where retail's scratches are assigned last.
 * Reusing the packet pointer (source = &f.packet) gives retail's $s5 role.
 */
#include "common.h"

typedef unsigned int DrawQuad __attribute__((mode(TI)));
typedef union { DrawQuad q; float f[4]; } DrawVec;
typedef struct { DrawVec v[9]; } DrawPacket;

extern DrawVec D_L30_001B09B0[4] __attribute__((sda));
extern DrawVec D_L30_001B9DC0;
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, int, int);

void func_L30_003D9CA8(DrawVec *position, DrawPacket *source, float scale, float offset) {
    struct { DrawPacket packet; DrawVec up, side, forward, normal, point, temp; } f;
    int i;
    f.packet = *source;
    source = &f.packet;
    f.up.q = 0; f.up.f[2] = 1; f.up.f[3] = 1;
    qcopy(&f.point, position);
    func_00282CF0(&f.side, &D_L30_001B9DC0, &f.point);
    func_00282F20(&f.side, &f.side, 1.0f);
    func_00282DD8(&f.forward, &f.side, &f.up);
    func_00282F20(&f.forward, &f.forward, 1.0f);
    func_00282DD8(&f.normal, &f.forward, &f.side);
    func_00282D30(&f.temp, &f.side, offset);
    func_00282CC0(&f.point, &f.point, &f.temp);
    for (i = 0; i < 4; i++) {
        func_00282D30(&f.packet.v[i], &D_L30_001B09B0[i], scale);
        func_002830C0(&f.packet.v[i], &f.packet.v[i], &f.side);
    }
    func_00280B90(source, 0, 0);
}
