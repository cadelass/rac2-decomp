/* Claude Opus 5.5 (opus-1), 29 October 2026: retained near miss, not linked.
 * Profile: own unit, -O2 -G0 -ffunction-sections -mno-split-addresses.
 * USA v1.01: 516/520 bytes, 0/17 places. Aligned against retail, the only
 * difference is the phase load: retail `lui v0; addiu v0,v0,%lo; lwc1 f21,0(v0)`
 * (then `lw v0,0x30(sp)`), this body `lw v0,0x30(sp); l.s f21,D` (gas: lui at).
 * Fixed here: the 0xFF7F7F and 127.5f invariants now sit in the inner-loop
 * pre-header after `blez s6`, as in retail. loop.c (pass 1, inner loop, 54 real
 * insns) moves at most three movables with life 1: the threshold (60-61) drops
 * by 3 per move. Setting the base colour in its own local between the opacity
 * and the colour makes its life span the float-to-int call, so it qualifies
 * last; once moved into the pre-header it is used in another block after the
 * inner guard, so the outer loop cannot hoist it (scan_loop maybe_never rule).
 * The phase: a plain scalar global keeps `(mem (symbol_ref))` from expand, and
 * combine folds any `la` pseudo into floatsisf2's "m" alternative; volatile
 * loads to a GPR + mtc1. Measured: WITHOUT -mno-split-addresses, with the
 * viewport words as incomplete sda arrays read as [0] and the phase read
 * through `int *phaseSource = &D_L00_001AF5A8;` set at function entry, the
 * phase sequence is exactly retail's (the spilled pointer's constant is not a
 * valid split-mode address, so reload loads it with lui/addiu into v0 after the
 * frame-reload order retail shows), but the first viewport load then fills the
 * first jal slot as $gp (512 bytes). With -mno-split-addresses the same pointer
 * is folded back to the symbol ($at form). Retail needs both behaviours: reopen
 * with a declaration that keeps the viewport loads two-word macros in split
 * mode, or a no-split shape whose phase address survives reload.
 * RAC1 counterpart: draw_visibomb_outside_zone_overlay
 * (src/overlays/shared/gold_bolts_and_teleporters.c).
 */
#include "common.h"
extern int D_001A7340, D_001A7344, D_001A7348, D_001A734C;
extern int D_L00_001AF5A8;
extern float func_00283CE0(s32);
extern u64 func_0027C878(s32);
extern int func_00283CF0(float);
extern s32 func_002A77E0(s32);
extern void func_0027E018(int, int, int, int, int, int, int, int, s64, u64);
/* Tiles an alpha-blended texture over the current viewport. */
void func_L00_003A09F8(void *actor) {
    char *state = *(char **)((char *)actor + 0x68);
    u64 texture;
    int color;
    int columns, rows, row, column, nextRow;
    int u, v, x, y;
    float tick, limit, phase, opacity;
    int base;
    float scale[2];
    float pos[2];

    scale[0] = func_00283CE0(D_001A7348);
    scale[1] = func_00283CE0(D_001A734C);
    texture = func_0027C878(30);
    rows = D_001A7340 / 32 + 1;
    columns = D_001A7344 / 32 + 1;
    for (row = 0; row < rows; row++) {
        for (column = 0; column < columns; column++) {
            pos[0] = (float)(row << 5);
            pos[1] = (float)(column << 5);
            phase = (float)D_L00_001AF5A8;
            tick = func_00283CE0(*(int *)(state + 0x140));
            limit = func_00283CE0(90);
            opacity = (tick * 127.5f) / limit;
            base = 0x00FF7F7F;
            color = (func_00283CF0(opacity) << 24) + base;
            u = func_002A77E0(32);
            v = func_002A77E0(32);
            x = func_00283CF0(pos[0] - phase);
            y = func_00283CF0(pos[1] - phase);
            func_0027E018(x, y, 32, 32, u, v, 32, 32, color, texture);
        }
    }
}
