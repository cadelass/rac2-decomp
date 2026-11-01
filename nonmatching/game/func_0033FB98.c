/*
 * func_0033FB98 (Opus 5.5, xhigh, task v2059).
 * Best, tools/check.py on this C as src/game/0033F030-menu-g8.c (the name gives it -G8, which it needs):
 * USA v1.01 28 of 28 places, 1720/1720 bytes; PAL 0 of 28; USA v2.00 0 of 28.
 *
 * What differs on PAL and v2.00: exactly four field offsets, the same in both releases.
 *   +0x1D4 self + 0x8B8 -> 0x8D8    +0x200 self + 0x900 -> 0x930
 *   +0x22C self + 0x948 -> 0x988    +0x258 self + 0x990 -> 0x9E0
 * self+0x828 does not move: these are elements 2 to 5 of children from 0x828 whose size is 0x48 in
 * v1.01 and 0x58 in the other two. Measured: this C with the right column gives PAL 28 of 28 and
 * v2.00 28 of 28, and v1.01 0 of 28. So nothing else in the function changes between releases.
 *
 * This is not a wording problem. Each source is compiled once, with flags from config/cflags.txt that
 * do not depend on the release (tools/build.py flags_for, compile_c), so one definition cannot emit
 * both immediates. The PAL and v2.00 catalogues carry the function under its v1.01 name only because
 * tools/levels.py identity() masks large offsets on registers: docs/VERSIONS.md "What the build
 * disproves". func_0033F0A0 and func_0033F218, which use the same four offsets, are in neither catalogue.
 *
 * What would unblock it, as docs/VERSIONS.md describes: tools/carry.py --version pal --demote and
 * --version us2 --demote after a build, recording it in config/<version>/not_carried.tsv. Then this C
 * goes into src/ and the right-column C into src/pal/ and src/us2/ under the release's own names
 * (PAL 00341C18, v2.00 00340AA8). Both of its callers defined in C, func_0029CBE0 and func_0033F218,
 * are already absent from those catalogues.
 */
#include "include_asm.h"

typedef struct { float x, y; } Pair;
typedef struct { int value; } MenuColor;
extern Pair D_001AE048[], D_001AE050[], D_001AE058[], D_001AE060[], D_001AE068[], D_001AE070[];
typedef struct { int value; char pad[20]; int id; } Item;
typedef struct { Item *items; } Items;
extern Items *D_001B18D4;
extern char *D_001A8CFC;
extern unsigned char D_00139568[];
extern int D_00139868[];
extern char D_00239BA0[];
extern struct { char pad[0x1C4]; int buttons; } D_00138180;
extern void *func_00115484(void *, int, unsigned int);
extern void func_00335E38(void *, float, float, float, float);
extern void func_00335E68(void *, int);
extern void func_00336920(void *, int, int);
extern char *func_0034E5B8(void *);
extern void func_00336F20(int, int *, int *, int *);
extern int *func_00335E20(void *);
extern void func_00336498(void *, int, int);
extern void func_00336B90(void *, int);
extern void func_00336B98(void *, int);
extern int func_002E5E58(int, int, void *);
extern void func_003409C8(void *, int);
extern void func_00340B70(void *, int);
extern unsigned int func_002A9588(unsigned int, unsigned int, int, int, int);
extern void func_003363C0(void *, float);
/* Updates the eight item rows, their colors and the current menu selection. */
int func_0033FB98(char *self, int buttons)
{
    Pair a, b, c, d, e, f, g, h, j, k;
    MenuColor firstColor, secondColor, textColor;
    int i;
    char *child;
    func_00115484(&a,0,8);
    func_00115484(&b,0,8);
    func_00115484(&c,0,8);
    func_00115484(&d,0,8);
    e = D_001AE048[0];
    f = D_001AE050[0];
    g = D_001AE058[0];
    h = D_001AE060[0];
    j = D_001AE068[0];
    func_00335E38(self + 0x0, a.x + (*(Pair **)(self+0x80C))->x, a.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    func_00335E38(self + 0x4C, d.x + (*(Pair **)(self+0x80C))->x, d.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    func_00335E38(self + 0xE4, b.x + (*(Pair **)(self+0x80C))->x, b.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    func_00335E38(self + 0x130, c.x + (*(Pair **)(self+0x80C))->x, c.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    func_00335E38(self + 0x828, e.x + (*(Pair **)(self+0x80C))->x, e.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    func_00335E38(self + 0x8B8, g.x + (*(Pair **)(self+0x80C))->x, g.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    func_00335E38(self + 0x900, f.x + (*(Pair **)(self+0x80C))->x, f.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    func_00335E38(self + 0x948, h.x + (*(Pair **)(self+0x80C))->x, h.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    func_00335E38(self + 0x990, j.x + (*(Pair **)(self+0x80C))->x, j.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    k=D_001AE070[0];
    func_00335E38(self + 0x2A8, k.x + (*(Pair **)(self+0x80C))->x, k.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    func_00335E38(self + 0x2F4, k.x + (*(Pair **)(self+0x80C))->x, k.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    func_00335E38(self + 0x5A0, k.x + (*(Pair **)(self+0x80C))->x, k.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    if (D_001B18D4) {
        int resourceOffset;
        i=0;
        resourceOffset = 0x36F28;
        for (child = self + 0x5EC; i < 8; child += 0x3C, i++) {
            char *bar, *row;
            if (!D_001B18D4->items[i].value) func_00335E68(child,0);
            else {
                func_00335E68(child,1);
                func_00336920(child,D_001B18D4->items[i].value,0);
            }
            bar=func_0034E5B8(D_001A8CFC+resourceOffset)+i*0x48;
            func_00335E68(bar,0);
            firstColor.value = 0;
            secondColor.value = 0;
            textColor.value = 0;
            func_00336F20(D_001B18D4->items[i].id,&firstColor.value,&secondColor.value,&textColor.value);
            {
                int *primary = func_00335E20(child);
                *primary = (*primary & 0xFF000000) | (textColor.value & 0xFFFFFF);
            }
            bar=func_0034E5B8(D_001A8CFC+resourceOffset)+i*0x48;
            func_00335E68(bar,1);
            func_00336498(bar,firstColor.value,secondColor.value);
            func_00336B90(bar,100);
            func_00336B98(bar,100);
            row=D_00239BA0+D_00139568[D_001B18D4->items[i].id]*224;
            if (*(int *)row) {
                int active = (unsigned char)row[4] != 0;
                if (*(int *)(row+0x6C) || active) {
                    func_00336B90(bar,*(int *)(row+0x6C));
                    {
                        int *secondary = func_00335E20(child);
                        *secondary = (*secondary & 0xFF000000) | (textColor.value & 0xFFFFFF);
                    }
                    if (*(int *)(D_00239BA0+D_00139568[D_001B18D4->items[i].id]*224+0x6C)>0)
                        func_00336B98(bar,D_00139868[D_001B18D4->items[i].id]>>5);
                }
            }
        }
    }
    if (buttons&4) {
        int v,lower;
        func_002E5E58(3,0,0);
        lower=-1;
        v=*(int *)(self+0x7CC)-1;
        *(int *)(self+0x7CC)=v>lower?v:7;
    } else if (buttons&8) {
        int v;
        func_002E5E58(3,0,0);
        v=*(int *)(self+0x7CC)+1;
        *(int *)(self+0x7CC)=v>7?0:v;
    } else {
        switch (*(int *)(self+0x81C)) {
        case 0: func_003409C8(self,buttons); break;
        case 1: func_00340B70(self,buttons); break;
        }
    }
    if (D_00138180.buttons&12) func_002A9588(0,0,1,0,1);
    {
        int *p=func_00335E20(self+0x5A0);
        *p=func_002A9588(0x60442D00,0x70FFFEED,20,0,0);
    }
    func_003363C0(self+0x5A0,(float)*(int *)(self+0x7CC));
    return 0;
}
