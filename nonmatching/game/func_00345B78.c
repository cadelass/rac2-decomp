/* opus-1 (Claude Opus 5.5, xhigh), 31 October 2026: -O2 -G8 -ffunction-sections, own unit
 * (src/game/00345B78-g8.c). Exact bytes for USA v1.01: 28 of 28 places. PAL 0/28, v2.00 0/28:
 * not landed, since one C definition must match every release that carries the function.
 * Only four field offsets differ, in every place of both releases: 0x48C/0x490/0x494/0x498
 * here are 0x4FC/0x500/0x504/0x508 there. C cannot state both. The catalogues still carry
 * this name into both releases; docs/VERSIONS.md's route is tools/carry.py --demote, then
 * each release's own copy (PAL already catalogues func_00345F70 as func_PAL_003480C8).
 * What closed the earlier 472-byte form: func_002E5E58 returns int, so the call's $v0
 * output makes the next temporary avoid $v0 (local-alloc's fake_birth), and D_001A7AF8 is
 * sda, so its address is one unsplit la that cannot fill the zero-id test's delay slot,
 * which then takes li $a0,5 from the error path.
 */
#include "common.h"
typedef struct { u8 pad[6]; s16 index; u8 tail[2]; } InputEntry;
typedef struct { u8 pad[6]; s16 value; u8 tail[216]; } InputRecord;
extern InputEntry D_001AA7D8[];
extern u8 D_001A7AF8[] __attribute__((sda));
extern u8 D_00139568[];
extern InputRecord D_00239BA0[];
extern int D_001F288C[];
extern int D_001ADB10 __attribute__((sda));
extern int func_002E5E58(int, int, int);
void func_00345B78(char *o, int buttons) {
#define I(off) (*(int *)(o+(off)))
    int index;
    if (buttons & 0x1000) {
        func_002E5E58(3,0,0); I(0x48c)++; I(0x490)=1; I(0x498)=0;
    } else if (buttons & 0x4000) {
        func_002E5E58(3,0,0); I(0x48c)++; I(0x498)=1; I(0x490)=0;
    } else if (buttons & 0x8000) {
        func_002E5E58(3,0,0); if (--I(0x48c)<0) I(0x48c)=1;
    } else if (buttons & 0x2000) {
        func_002E5E58(3,0,0); if (++I(0x48c)>=2) I(0x48c)=0;
    } else if (buttons & 0x40) {
        index=D_001AA7D8[I(0x48c)].index;
        if (index && D_001A7AF8[index]) { func_002E5E58(4,0,0); D_001F288C[0]=index; I(0x494)=index; }
        else func_002E5E58(5,0,0);
    }
    { int selected=D_001AA7D8[I(0x48c)].index;
    I(0x494)=selected;
    if (selected && D_001A7AF8[selected]) D_001ADB10=((InputRecord *)(D_00139568[selected]*224 + (char *)D_00239BA0))->value; }
#undef I
}
