/* Claude Opus 5.5 (xhigh), v1709, 2026-10-31; retained near miss, not linked.
 * Unit: its own file, default profile -O2 -G0 -ffunction-sections (no -frac2-qcopy).
 * check.py: 1728/1728 bytes, 0/28 places (USA v1.01), first difference +0x30; 117 of
 * 432 instructions differ once relocations are masked, all register choices or local
 * scheduling. The frame and everything after +0x5C8 already agree.
 * BLOCKER, the compiler: retail's 0xE0-byte copy is `lq; lq; sq; sq; addiu; bne; addiu`
 * with `bne src,src+0xE0`, the shape of mips.c block_move_loop (32 bytes per pass,
 * final_src, NE). This tree's output_block_move has no lq/sq case and expand_block_move
 * clamps align to 8, so `saved.records[j] = D_00239BA0[j]` gives the ld/sd loop: 1760
 * bytes here. Its movstrsi_internal2 has four scratch registers; that wording makes this
 * compiler use $t8,$t9 as scratch, and retail's reload temporaries are exactly $t8,$t9.
 * Retail's temporaries $a0,$a3 ($a0,$a2 in the restore loop) would be the other two.
 * Hypothesis, not tested: with an align>=16 lq/sq case in output_block_move, the plain
 * struct assignment would replace both explicit copy loops below. No C copy reaches
 * retail: a C `lq`'s pseudo is allocated before src/end/dst, and the scheduler moves
 * `addiu src` ahead of the second `sq`, which is still waiting on its load.
 * Established, keep these: one local struct for flags, words, slots and records (separate
 * arrays give 1784 bytes with the natural copy); separate index variables per big loop
 * (a shared `i` stops PRE reusing i*4 and leaves the outer loop strength-reduced; with
 * them plain j++ gives retail's `j+1` before the copy and `j = next` after it); state
 * bytes as fields of D_001A79F8; D_001A7B94 as an array (its [1] store stays out of a
 * delay slot); D_001A7AF0 read MACRO_ADDR and written through SDATA ($gp in a delay slot);
 * the second kind test nested in `if (D_001A7B08)`; base-pointer locals for the
 * reg+offset accesses. The `(int)` sum only reproduces (plus off sp) for the explicit
 * loop and should go with it. Unaligned 64-byte state copy semantics are preserved.
 * All declarations are below; no linked build was run.
 */
#include "common.h"

typedef unsigned int QuadDE990 __attribute__((mode(TI)));
typedef union RecordDE990 {
    QuadDE990 data[14];
    struct {
        char pad0[4];
        unsigned char kind;
        char pad5[0x67];
        int value;
        char pad70[0x1e];
        unsigned short cost;
    } f;
} RecordDE990;
typedef struct StateDE990 {
    int f0[4];
    short f10;
    unsigned char f12;
    unsigned char f13;
    int f14;
    int f18, f1c;
    short f20, f22;
    int f24;
    char f28[0x12];
    unsigned char f3a, f3b;
    int f3c;
} StateDE990;
extern StateDE990 D_001A79F8 MACRO_ADDR;
extern int D_001A7AF0 MACRO_ADDR;
extern int D_001A7AF0_gp SDATA(D_001A7AF0);
extern unsigned char D_0018C958[];
extern unsigned char D_001A7AF8[] MACRO_ADDR;
extern int D_00139868[];
extern RecordDE990 D_00239BA0[];
extern unsigned char D_00139568[];
extern int D_00139688[];
extern unsigned char D_001A7A60[] MACRO_ADDR;
extern unsigned char D_001A7A40[] MACRO_ADDR;
extern unsigned char D_001A7A80[] MACRO_ADDR;
extern unsigned char D_001A7AB8[] MACRO_ADDR;
extern unsigned char D_0019B278[];
extern unsigned char D_001395B8[];
extern int D_001A73B8[] MACRO_ADDR;
extern unsigned char D_001A7B94[] MACRO_ADDR;
extern unsigned char D_001A7B08 MACRO_ADDR;
extern unsigned char D_00189E20[];
extern unsigned char D_001393E0[];
extern char D_001F2A40[];
extern void func_00282AB0(void *, void *, int);
extern void func_00282A60(void *, int, int);
extern void func_00298E08(void);
extern int func_00287FF8(int, int);
extern int func_00288870(RecordDE990 *, int, int);
extern void func_0029ADA0(char *);

void func_002DE990(int selected)
{
    struct {
        int flags[56];
        int words[56];
        int slots[56];
        RecordDE990 records[56];
    } saved;
    int saved32[32];
    unsigned char saved56[56];
    int saved12[12];
    StateDE990 savedState;
    unsigned char savedBlock[112];
    RecordDE990 first, second;
    int resident, hadCard, i, j, k;
    unsigned char control;
    StateDE990 *gameState;
    unsigned char *card, *block, *slots;
    int *words;
    unsigned char *state, *hud;
    QuadDE990 *src, *dst, *end, a, b;
    card = D_0018C958;
    D_001A79F8.f12++;
    D_001A79F8.f3a = 1;
    D_001A79F8.f3b = 0;
    resident = D_001A7AF0;
    hadCard = *(unsigned short *)(card + 0x84);
    gameState = &D_001A79F8;
    savedState = *gameState;
    for (j = 0; j < 56; j++) {
        saved.flags[j] = D_001A7AF8[j];
        saved.words[j] = D_00139868[j];
        dst = (QuadDE990 *)(j * (int)sizeof(RecordDE990) + (int)&saved + 0x2A0);
        src = D_00239BA0[j].data;
        end = src + 14;
    copy1:
        a = src[0];
        b = src[1];
        dst[0] = a;
        dst[1] = b;
        src += 2;
        dst += 2;
        if (src != end) goto copy1;
        saved.slots[j] = D_00139568[j];
    }
    for (i = 0; i < 32; i++) saved32[i] = D_001A7A60[i];
    for (i = 0; i < 12; i++) saved12[i] = D_001A7A40[i];
    saved.flags[51] = 0;
    saved.flags[36] = 0;
    saved.flags[20] = 0;
    saved.flags[13] = 0;
    saved.flags[38] = 0;
    saved.flags[39] = 0;
    saved.flags[46] = 0;
    saved.flags[48] = 0;
    saved.flags[55] = 0;
    saved.flags[21] = 0;
    saved.flags[2] = 0;
    saved.flags[3] = 0;
    saved.flags[4] = 0;
    saved.flags[19] = 0;
    saved.flags[8] = 0;
    func_00282AB0(savedBlock, D_0019B278, 112);
    block = D_001395B8;
    control = block[0x90];
    for (i = 0; i < 56; i++) saved56[i] = D_001A7A80[i];
    func_00298E08();
    func_00282AB0(D_0019B278, savedBlock, 112);
    block = D_001395B8;
    block[0x90] = control;
    func_00282A60(D_001A7AB8, 0, 56);
    for (i = 0; i < 56; i++) D_001A7A80[i] = saved56[i];
    for (i = 7; i >= 0; i--) D_001A73B8[i] = 0;
    gameState = &D_001A79F8;
    *gameState = savedState;
    D_001A73B8[0] = 30;
    D_001A73B8[1] = 42;
    D_001A79F8.f22 = 0;
    D_001A79F8.f24 = 0;
    D_001A79F8.f18 = 0;
    D_001A79F8.f1c = 0;
    D_001A7B94[0] = 0;
    D_001A7B94[1] = 0;
    if (hadCard) {
        card = D_0018C958;
        if (*(unsigned short *)(card + 0x84) == 0)
            *(unsigned short *)(card + 0x84) = 1;
    }
    for (k = 0; k < 56; k++) {
        D_001A7AF8[k] = saved.flags[k];
        D_00139868[k] = saved.words[k];
        dst = D_00239BA0[k].data;
        src = (QuadDE990 *)(k * (int)sizeof(RecordDE990) + (int)&saved + 0x2A0);
        end = src + 14;
    copy2:
        a = src[0];
        b = src[1];
        dst[0] = a;
        dst[1] = b;
        src += 2;
        dst += 2;
        if (src != end) goto copy2;
        D_00139568[k] = saved.slots[k];
        D_00139688[k] = D_00239BA0[D_00139568[k]].f.cost;
    }
    for (i = 0; i < 32; i++) D_001A7A60[i] = saved32[i];
    for (i = 0; i < 12; i++) D_001A7A40[i] = saved12[i];
    D_001A7B94[1] = 0;
    D_001A7B94[0] = 0;
    func_00287FF8(10, 3);
    if (D_001A7B08) {
        slots = D_00139568;
        if (D_00239BA0[slots[0x10]].f.kind == 0)
            func_00287FF8(16, 2);
        else
            func_00287FF8(16, 3);
        slots = D_00139568;
        if (D_00239BA0[slots[0x10]].f.kind == 0) {
            func_00288870(&first, 16, 2);
            func_00288870(&second, 16, 0);
            words = D_00139868;
            words[16] = (float)first.f.value * (float)words[16] / (float)second.f.value;
        }
    }
    hud = D_00189E20;
    *(short *)(hud + 0x24fc) = 1;
    D_001A7AF0_gp = resident;
    if (selected >= 0) {
        state = D_001393E0;
        *(short *)(state + 0x18) = selected;
        *(int *)(state + selected * 28 + 0x30) = 0;
        func_0029ADA0(D_001F2A40);
        *(char **)(state + 0x174) = D_001F2A40;
        *(int *)(state + 0x148) = 0;
        if (*(int *)(state + 0x164) < 0) {
            *(int *)(state + 0x168) = 0;
            *(int *)(state + 0x164) = 19;
        }
    }
}
