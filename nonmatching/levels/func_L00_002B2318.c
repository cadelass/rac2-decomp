/* Tier: sol-high, task v1280. USA v1.01, default game profile
 * (-O2 -G0 -ffunction-sections): 1788 bytes versus 1832; 0 of 27 places match.
 * Rechecked from the earlier 1728-byte draft under this checkout's toolchain.
 * All declarations needed by the draft are below; transfers use common.h.
 *
 * Improvements: typed hero/record/owner views recover the retail save set and
 * several base lifetimes; sda on the incomplete effect-table array avoids its
 * extra invariant base register; qcopy matches the two register-address copies.
 * The object scan must use !(16 < distance), rather than distance <= 16, to
 * preserve retail's unordered comparison behavior.
 *
 * Remaining: record flag load at L00 002B2984 and its index arithmetic are dead
 * in ordinary C and disappear. The source keeps that read without volatile.
 * Allocation of the scan cursor/global base and final-loop constants differs;
 * the two input bytes still use split absolute loads with different scheduling.
 * -G8 and -g do not close the gap; -mno-split-addresses worsens hero addressing.
 * sda input-byte probes speculated a GP load and are deliberately not retained.
 * No linked build was run: the candidate fails check.py on size everywhere.
 * Next useful evidence: original record-flag semantics and source lifetime
 * structure, rather than another equivalent loop spelling or an invented load.
 */
#include "common.h"

typedef int Vec128 __attribute__((mode(TI)));

extern unsigned char D_001A7B01;
extern unsigned char D_001A7B41;
extern int func_00282948(void *);
extern char *D_L00_001FACE0[];
extern int func_002AB1F0(void *);
extern float func_00282E20(void *);
typedef struct {
    char pad[9];
    unsigned char index;
} ItemSelector2318;
extern ItemSelector2318 D_00139568;
typedef struct {
    char pad0[4];
    unsigned char flag;
    char pad1[0x58 - 5];
    int count;
    char pad2[224 - 0x5c];
} Record2318;
extern Record2318 D_L00_00262570[];
extern void func_L00_0040B838(void *, int, void *, int);
extern float func_00283248(float,float);
extern float func_00283C80(float,float);
extern void func_0029FCC0(void *,int,void *);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern float func_002A78D8(float,float);
extern int func_00283CF0(float);
typedef struct {
    char pad[0x64];
    unsigned char *owner;
} Owner2318;
extern Owner2318 D_L00_001FE940;
extern char D_L00_001B8F20[] __attribute__((sda));
extern char *func_002C16C0(void *,void *,int,int,int,int,float,float,float,float,float);

extern int func_L00_002ADEA0(int);
extern void func_00282CF0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, int, int);
typedef struct {
    char pad0[0x80]; float position[4];
    char pad1[0x98-0x90]; float heading;
    char pad2[0x1314-0x9c]; char *weapon;
    char pad3[0x18d0-0x1318]; char *target; int active, timer;
    char pad4[0x2010-0x18dc]; float point[4] __attribute__((aligned(16)));
    char pad5[0x2290-0x2020]; int owner;
    char pad6[0x22b4-0x2294]; unsigned char mode;
    char pad7[0x24fc-0x22b5]; short blocked;
} Hero2318;
extern Hero2318 D_00189E20;

void func_L00_002B2318(void) {
    float v[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float angle;
    Record2318 *record;
    int i;
    if (!D_00189E20.active || D_00189E20.mode) return;
    if (!D_001A7B01 && !D_001A7B41) return;
    if (func_L00_002ADEA0(3)!=3 && func_L00_002ADEA0(3)!=2) return;
    if (D_00189E20.blocked) return;
    if (func_00282948(&D_00189E20.timer)) {
        char *object;
        char **p=D_L00_001FACE0;
        while ((object=*p)!=0) {
            char *type=*(char **)(object+0x24);
            if (type && *(short *)(type+0x46)==5 && object && *(unsigned char *)(object+0x20)!=254 && *(unsigned char *)(object+0x20)!=253 && func_002AB1F0(object)) {
                func_00282CF0(v,object+0x10,D_00189E20.position);
                if (!(16.0f<func_00282E20(v))) D_00189E20.target=object;
            }
            p++;
        }
        { char *target=D_00189E20.target;
        if (!target || *(short *)(*(char **)(target+0x24)+0x46)!=5 || *(unsigned char *)(target+0x20)==254 || *(unsigned char *)(target+0x20)==253) return;
        if (!func_002761F8(D_00189E20.point,target+0x10,0,D_00189E20.owner,0)) return;
        func_00282CF0(v,D_00189E20.target+0x10,D_00189E20.position);
        if (!(func_00282E20(v)<16.0f)) return;
        }
        record=&D_L00_00262570[D_00139568.index];
        if (record->count>0) {
            if (record->flag) func_L00_0040B838(D_00189E20.point,D_00189E20.owner,D_00189E20.target,1);
            else func_L00_0040B838(D_00189E20.point,D_00189E20.owner,D_00189E20.target,0);
            record=&D_L00_00262570[D_00139568.index];
            D_00189E20.timer=120;
            --record->count;
        } else {
            D_00189E20.active=0;
            D_L00_00262570[D_00139568.index].count=30;
        }
    } else {
        char *object=D_00189E20.target;
        angle=func_00283C80(func_00283248(*(float *)(object+0x10)-D_00189E20.position[0],*(float *)(object+0x14)-D_00189E20.position[1]),D_00189E20.heading);
        if (angle>1.3962636f && D_L00_00262570[D_00139568.index].flag) {
            char *weapon=D_00189E20.weapon;
            *(int *)(weapon+0x78)=0x800000ff;
            *(unsigned short *)(weapon+0x34)|=0x10;
            qcopy(v, D_00189E20.point);
            func_0029FCC0(weapon,6,a); func_0029FCC0(weapon,7,b);
            *(Vec128 *)c=0; *(Vec128 *)d=0;
            c[0]=-0.025f; c[1]=0.01f; c[2]=0.04f;
            d[0]=-0.025f; d[1]=-0.01f; d[2]=0.04f;
            func_00283098(c,c,weapon+0xc0); func_00282CC0(a,a,c);
            func_00283098(d,d,weapon+0xc0); func_00282CC0(b,b,d);
            for (i=29;i>=0;i--) {
                a[0]+=func_002A78D8(0.0f,0.004f); a[1]+=func_002A78D8(0.0f,0.004f); a[2]+=func_002A78D8(0.0f,0.004f);
                b[0]+=func_002A78D8(0.0f,0.004f); b[1]+=func_002A78D8(0.0f,0.004f); b[2]+=func_002A78D8(0.0f,0.004f);
                { char *effect=func_002C16C0(a,D_L00_001B8F20,2,127,0x2020ff,func_00283CF0(func_002A78D8(1.0f,-1.0f)),25200.0f,500.0f,1.0f,0.0f,0.0f);
                if (effect) effect[2]=*D_L00_001FE940.owner; }
                { char *effect=func_002C16C0(b,D_L00_001B8F20,2,127,0x2020ff,func_00283CF0(func_002A78D8(1.0f,-1.0f)),25200.0f,500.0f,1.0f,0.0f,0.0f);
                if (effect) effect[2]=*D_L00_001FE940.owner; }
            }
        }
        qcopy(v, D_00189E20.point);
        if (angle<1.3962636f) {
            for (i=19;i>=0;i--) {
                a[0]=v[0]+func_002A78D8(0.0f,0.04f); a[1]=v[1]+func_002A78D8(0.0f,0.04f); a[2]=v[2]+func_002A78D8(0.0f,0.04f);
                /* Retail reads this byte even though the result is dead before the call. */
                (void)D_L00_00262570[D_00139568.index].flag;
                { char *effect=func_002C16C0(a,D_L00_001B8F20,2,127,0x20ff20,func_00283CF0(func_002A78D8(1.0f,-1.0f)),31500.002f,500.0f,1.0f,0.0f,0.0f);
                if (effect) effect[2]=*D_L00_001FE940.owner; }
            }
        }
    }
}
