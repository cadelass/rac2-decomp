/* sol-high, USA v1.01; -O2 -G0 -ffunction-sections.
 * Best check.py: 1648 bytes / retail 1648, 0 of 27 places match.
 * Frame 0x220 and all local packet/vector offsets agree. The opening sequence
 * agrees through +0xB8; the first difference is store scheduling at +0xBC.
 * Reusing a working vector pointer for the initial origin and loop matrix
 * recovers retail's saved origin pointer. Grouping the next-point offset as
 * points + (i * 16 + 16) recovers its single-shift loop addressing. Keeping
 * texture offsets in their final stores improves UV result-register allocation.
 * Remaining: six invariant spill slots are rotated (p+48 spills first rather
 * than last), initial/final color-width stores are scheduled differently, and
 * raw UV multiplication/upper-coordinate temporaries use different FPRs.
 * Union vector lanes and one enclosing scratch record tie; splitting loop/tail
 * UV locals worsens the tail. Explicit corner pointers worsen allocation/size;
 * native TI copies with qcopy/barrier give 1636 bytes on this revised body.
 * Next: recover the invariant/corner lifetimes and UV temporary structure.
 * All required declarations follow. No linked build or other release was run.
 */
#include "common.h"
typedef int TrailQuad __attribute__((mode(TI)));
typedef union { TrailQuad quad; float f[4]; } TrailVector;
extern void func_00281DE8_7(void *, int, int, int);
extern int func_001163B0(void);
extern void func_00282CF0_7(void *, void *, void *);
extern void func_00282DD8_7(void *, void *, void *);
extern void func_00282F20_7(void *, void *, float);
extern void func_00282D30_7(void *, void *, float);
extern void func_002830C0_7(void *, void *, void *);
extern float func_00283CE0_7(int);
extern void func_00280B90_7(void *, void *, int);

extern float D_L00_001B8DC0[];
void func_L00_003DCC48(float tex, float width, float step, void *start, char *points, int color, int count)
{
    char origin[16] __attribute__((aligned(16)));
    char p[144] __attribute__((aligned(16)));
    char q[144] __attribute__((aligned(16)));
    float m[16];
    TrailVector offsets[2];
    int i;
    char *basis = origin;
    float v, u;
    *(TrailQuad *)origin = *(TrailQuad *)start;
    func_00281DE8_7(p,43,1,128);
    func_00281DE8_7(q,43,1,128);
    offsets[0].quad=0; offsets[1].quad=0;
    width *= .25f;
    *(int *)(p+64)=*(int *)(p+68)=color;
    *(int *)(q+64)=*(int *)(q+68)=color;
    *(int *)(p+72)=*(int *)(p+76)=color;
    *(int *)(q+72)=*(int *)(q+76)=color;
    offsets[1].f[2]=width+width;
    offsets[0].f[3]=offsets[1].f[3]=1;
    offsets[0].f[2]=width;
    if (!(func_001163B0()&1)) {
        *(float *)(p+80)=tex; *(float *)(p+84)=0; *(float *)(p+88)=tex; *(float *)(p+92)=1;
        *(float *)(p+96)=step+tex; *(float *)(p+100)=0; *(float *)(p+104)=step+tex; *(float *)(p+108)=1;
        *(float *)(q+80)=tex; *(float *)(q+84)=0; *(float *)(q+88)=tex; *(float *)(q+92)=1;
        *(float *)(q+96)=step+tex; *(float *)(q+100)=0; *(float *)(q+104)=step+tex; *(float *)(q+108)=1;
    } else {
        *(float *)(p+80)=tex; *(float *)(p+84)=1; *(float *)(p+88)=tex; *(float *)(p+92)=0;
        *(float *)(p+96)=step+tex; *(float *)(p+100)=1; *(float *)(p+104)=step+tex; *(float *)(p+108)=0;
        *(float *)(q+80)=tex; *(float *)(q+84)=1; *(float *)(q+88)=tex; *(float *)(q+92)=0;
        *(float *)(q+96)=step+tex; *(float *)(q+100)=1; *(float *)(q+104)=step+tex; *(float *)(q+108)=0;
    }
    func_00282CF0_7(m,points,basis); func_00282F20_7(m,m,1);
    func_00282CF0_7(m+4,D_L00_001B8DC0,basis);
    func_00282DD8_7(m+8,m+4,m); func_00282F20_7(m+8,m+8,1); func_00282DD8_7(m+4,m,m+8);
    qcopy(m+12,basis);
    qcopy(p,offsets); qcopy(q,offsets+1);
    func_00282D30_7(p+16,p,-1); func_00282D30_7(q+16,q,-1);
    func_002830C0_7(p,p,m); func_002830C0_7(p+16,p+16,m); func_002830C0_7(q,q,m); func_002830C0_7(q+16,q+16,m);
    for(i=0;i<count-1;i++) {
        basis = (char *)m;
        func_00282CF0_7(basis,points+(i*16+16),points+i*16); func_00282F20_7(basis,basis,1);
        func_00282CF0_7(basis+16,D_L00_001B8DC0,points+i*16);
        func_00282DD8_7(basis+32,basis+16,basis); func_00282F20_7(basis+32,basis+32,1); func_00282DD8_7(basis+16,basis,basis+32);
        qcopy(basis+48,points+i*16);
        offsets[0].f[2]*=.7f; offsets[1].f[2]=offsets[0].f[2]+offsets[0].f[2];
        qcopy(p+32,offsets); qcopy(q+32,offsets+1);
        func_00282D30_7(p+48,p+32,-1); func_00282D30_7(q+48,q+32,-1);
        func_002830C0_7(p+32,p+32,basis); func_002830C0_7(p+48,p+48,basis); func_002830C0_7(q+32,q+32,basis); func_002830C0_7(q+48,q+48,basis);
        u=step*func_00283CE0_7(i+1); v=u+step; if(u>=1) {u-=1;v-=1;} 
        *(float *)(p+80)=u+tex; *(float *)(p+88)=u+tex; *(float *)(p+96)=v+tex; *(float *)(p+104)=v+tex;
        *(float *)(q+80)=u+tex; *(float *)(q+88)=u+tex; *(float *)(q+96)=v+tex; *(float *)(q+104)=v+tex;
        func_00280B90_7(p,0,0); func_00280B90_7(q,0,0);
        if(i) { *(int *)(p+68)=color|0x7f000000; *(int *)(p+64)=color|0x7f000000; *(int *)(q+68)=color|0x3f000000; *(int *)(q+64)=color|0x3f000000; }
        *(int *)(p+76)=color|0x7f000000; *(int *)(p+72)=color|0x7f000000; *(int *)(q+76)=color|0x3f000000; *(int *)(q+72)=color|0x3f000000;
        qcopy(p,p+32);qcopy(p+16,p+48);qcopy(q,q+32);qcopy(q+16,q+48);
    }
    qcopy(m+12,points+(count-1)*16);
    offsets[0].f[2]*=.7f; offsets[1].f[2]=offsets[0].f[2]+offsets[0].f[2];
    qcopy(p+32,offsets);qcopy(q+32,offsets+1);
    func_00282D30_7(p+48,p+32,-1);func_00282D30_7(q+48,q+32,-1);
    func_002830C0_7(p+32,p+32,m);func_002830C0_7(p+48,p+48,m);func_002830C0_7(q+32,q+32,m);func_002830C0_7(q+48,q+48,m);
    *(int *)(q+76)=*(int *)(q+72)=*(int *)(p+72)=*(int *)(p+76)=color;
    u=step*func_00283CE0_7(i+1);v=u+step;if(u>=1){v-=1;u-=1;}
    *(float *)(p+80)=u+tex;*(float *)(p+88)=u+tex;*(float *)(p+96)=v+tex;*(float *)(p+104)=v+tex;
    *(float *)(q+80)=u+tex;*(float *)(q+88)=u+tex;*(float *)(q+96)=v+tex;*(float *)(q+104)=v+tex;
    func_00280B90_7(p,0,0);func_00280B90_7(q,0,0);
}
