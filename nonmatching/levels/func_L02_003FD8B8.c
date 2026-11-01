/*
 * Tier: sol-high, 29 October 2026; USA v1.01 game -O2 -G8 -ffunction-sections.
 * Best retained check: 1292/1328 bytes, 0 of 1 places match.
 * Direct enabled-field tests recover the navigation-loop temporary registers.
 * Confirmation call tails still merge, removing nine retail instructions;
 * table/index preparation and input-clear store scheduling also differ.
 * -fno-expensive-optimizations, -fno-thread-jumps and -frac2-keep-block-order
 * tie the size; -fno-gcse regresses to 1276 bytes. An explicit input-clear
 * continuation does not prevent tail merging. Do not repeat these trials.
 * Next: recover the original confirmation control flow from a related menu.
 * Required declarations are below. Compile in a dedicated -g8.c unit; the
 * incomplete small-data table uses the approved SDATA view, not a false bound.
 */
#include "common.h"
extern int func_002B4BE8(void);
extern int D_0018C0B4 __attribute__((nosda));
extern void func_L00_002C42E0(int,int);
typedef struct { char pad[0x1C4]; int flags; } MenuInput;
extern MenuInput D_00138180;
extern char *D_L02_001B1190[] SDATA(D_L02_001B1190);
extern u8 D_001395B8[], D_00139568[];
typedef struct { char pad[4]; u8 enabled; char rest[0xDB]; } MenuRec;
extern MenuRec D_L02_00264A70[];
extern int func_L02_003F9B70(int);
extern int func_00288D58(void);
extern void func_002E5E58(int,int,int);
extern void func_00282978(void *);
extern void func_002A7750(char *,int,int);
extern void func_003355A8(int);
extern void func_L00_002C8BA8(int);
extern void func_002B49E0(int,int,int,int,int);
extern void func_L02_003FCA80(char *);
extern void func_002B8518(void);
extern int D_L02_002004A4 __attribute__((nosda));
extern int func_L00_0032EF10(int,int,int);
extern void func_L00_002E6CF0(void *,void *);
extern void func_L02_003FE250(char *);
void func_L02_003FD8B8(char *a0) {
    char *state = *(char **)(a0+0x68);
    int i, found;
    if (func_002B4BE8() != 5) {
    if (D_0018C0B4 != 0x6F) func_L00_002C42E0(0x6F,1);
    if (*(s16 *)(state+0x11A)==0) {
        if ((D_00138180.flags&0x2000) && *(s16 *)(state+0x118)<13) {
            for(i=*(s16 *)(state+0x118)+1;i<14;i++) {
                if (!D_001395B8[func_L02_003F9B70(*(int *)(D_L02_001B1190[i]+8))]) continue;
                if (i>=12 && !func_00288D58()) continue;
                if (i==7) { if(!D_L02_00264A70[D_00139568[0x1E]].enabled) continue; }
                if (i==8) { if(!D_L02_00264A70[D_00139568[0x2A]].enabled) continue; }
                *(s16 *)(state+0x118)=i;
                *(s16 *)(state+0x11A)=15;
                *(s16 *)(state+0x128)=15;
                func_002E5E58(3,0,0);
                break;
            }
        } else if ((D_00138180.flags&0x8000) && *(s16 *)(state+0x118)>0) {
            found=0;
            if (*(s16 *)(state+0x118)==1) {
                *(s16 *)(state+0x118)=0;
                found=1;
                func_002E5E58(3,0,0);
            } else {
                for(i=*(s16 *)(state+0x118)-1;i>=0;i--) {
                    if (!D_001395B8[func_L02_003F9B70(*(int *)(D_L02_001B1190[i]+8))]) continue;
                    if (i>=12 && !func_00288D58()) continue;
                    if (i==7) { if(!D_L02_00264A70[D_00139568[0x1E]].enabled) continue; }
                    if (i==8) { if(!D_L02_00264A70[D_00139568[0x2A]].enabled) continue; }
                    *(s16 *)(state+0x118)=i; found=1; break;
                }
            }
            if (!found) *(s16 *)(state+0x118)=0;
            *(s16 *)(state+0x11A)=15;
            *(s16 *)(state+0x126)=15;
            func_002E5E58(3,0,0);
        }
    } else func_00282978(state+0x11A);
    if (D_00138180.flags&0x40) {
        if (*(s16 *)(state+0x118)==0) {
        *(u16 *)(state+0x120)=*(u16 *)(state+0x118);
        *(s16 *)(state+0x122)=0;
        D_001395B8[0x3C]=*(u8 *)(state+0x118);
        func_002A7750(a0,8,-1);
        func_003355A8(2);
        func_L00_002C8BA8(0);
        func_002E5E58(4,0,0);
        D_00138180.flags=0;
        return;
        } else {
            if (!D_001395B8[func_L02_003F9B70(*(int *)(D_L02_001B1190[*(s16 *)(state+0x118)]+8))]) return;
            if (*(s16 *)(state+0x118)>=12 && !func_00288D58()) return;
            if (*(s16 *)(state+0x118)==7) { if(!D_L02_00264A70[D_00139568[0x1E]].enabled) return; }
            if (*(s16 *)(state+0x118)==8) { if(!D_L02_00264A70[D_00139568[0x2A]].enabled) return; }
        *(u16 *)(state+0x120)=*(u16 *)(state+0x118);
        *(s16 *)(state+0x122)=0;
        D_001395B8[0x3C]=*(u8 *)(state+0x118);
        func_002A7750(a0,8,-1);
        func_003355A8(2);
        func_L00_002C8BA8(0);
        func_002E5E58(4,0,0);
        D_00138180.flags=0;
        return;
        }
    } else if (D_00138180.flags&0x80) {
        func_002B49E0(5,1,0,0,0);
    } else if (D_00138180.flags&0x10) {
        func_L02_003FCA80(a0);
        D_00138180.flags=0;
        *(int *)((char *)&D_00138180+0x1A4)=0;
        *(int *)((char *)&D_00138180+0x1A0)=0;
        *(int *)((char *)&D_00138180+0x1C0)=0;
        func_002B8518();
    } else if (D_L02_002004A4 && func_L00_0032EF10(1,60,0) && func_L00_0032EF10(2,60,0) && func_L00_0032EF10(4,60,0) && func_L00_0032EF10(8,60,0)) {
        *(u16 *)(state+0x120)=*(u16 *)(state+0x118);
        func_002A7750(a0,5,-1);
    }
    } else func_L00_002E6CF0(func_L02_003FE250,a0);
}
