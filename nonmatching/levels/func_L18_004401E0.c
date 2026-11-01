/* GPT-6.1 Sol high, task v0962. USA v1.01, levels 18/19/20.
 * -O2 -G8 -ffunction-sections: 1112/1112 bytes, 0/3 places.
 * First difference +0x120. Fourteen instruction words differ outside relocation
 * values: scratch-base s0 and PRE copy s6 are formed before the first vector
 * scale/random call instead of the second; the owner-equality branch at +0x31C
 * also targets an epilogue restore three words later than retail.
 * Improvements over the prior 1136-byte draft: NOT_SDA on D_L18_001BFC18;
 * physical-bank-preserving call interleavings; MACRO_ADDR on the incomplete
 * D_L18_001A8F20 array; positive nested owner test with a FreeMoby call in each
 * branch, enabling the compiler to share the impact-call tail. C16C0 and BD8B0
 * really return pointers; the current src definitions establish these returns.
 * Seventeen checks including the final best-draft recheck and one C89 parse
 * failure. Separate scoped FX/query storage grows the frame to 0x110;
 * -fno-gcse loses PRE copies, shrinks the frame to 0xD0, and gives 1092 bytes.
 * -frac2-gcse-unsplit-edges is unchanged. Explicit block-local vector pointer
 * and splitting only the second random result retain the best bytes (tie).
 * Splitting both random results changes s1 timing and TI scratch allocation.
 * Reopen with independently justified scratch-address/lifetime evidence.
 * All declarations are included below. No linked build was run.
 */
#include "common.h"
typedef int TI __attribute__((mode(TI)));
typedef union { u8 b[0x30]; u16 h[0x18]; int i[0xC]; float f[0xC]; void *p[0xC]; } View;
typedef union { u8 b[0x40]; float f[0x10]; int i[0x10]; } State;
extern float D_L18_001B234C MACRO_ADDR;
extern float D_L18_001B2350 MACRO_ADDR;
extern int D_L18_001B2348 __attribute__((sda));
typedef union { u8 b[0x48]; int i[0x12]; float f[0x12]; } Params;
extern Params D_L18_002BDA10;
extern int D_L18_001BFC18 NOT_SDA;
extern u8 D_L18_001A8F20[] MACRO_ADDR;
extern void func_00282CC0(void *,void *,void *);
extern float func_00282DF0(void *);
extern float func_002A7878(float,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282D30(void *,void *,float);
extern void *func_002C16C0(void *,void *,int,int,int,int,float,float,float,float,float);
extern void func_00283098(void *,void *,void *);
extern float func_002A7940(void);
extern void func_002ACEC0(void *,void *,void *,float);
extern int func_001163B0(void);
extern void *func_002BD8B0(void *,void *,int,int,float,int,int);
extern int func_002761F8(void *,void *,int,int,void *);
extern int func_00277258(float,void *,int,int);
extern int func_00282948(void *);
extern int func_00277F48(void *,int,int,float,void *);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_0029F338(void *);
void func_L18_004401E0(u8 *o) {
    float pos[4] __attribute__((aligned(16)));
    union { View request; struct { float v[4], a[4], b[4], c[4]; } fx; } scratch __attribute__((aligned(16)));
    State *s = *(State **)(o+0x68);
    int flag;
    func_00282CC0(pos,o+0x10,s);
    flag = 0;
    if (D_L18_001B234C > 0.9f || D_L18_001B2350 > 0.9f) flag = 1;
    if (!flag || !(D_L18_001B2348 & 1)) {
        float len = func_00282DF0(s);
        *(TI *)scratch.fx.b = 0;
        scratch.fx.b[0] = func_002A7878(-1.0f,1.0f);
        scratch.fx.b[1] = func_002A7878(-1.0f,1.0f);
        scratch.fx.b[2] = func_002A7878(-1.0f,1.0f);
        *(TI *)scratch.fx.a = *(TI *)scratch.fx.b;
        func_00282F20(scratch.fx.a,scratch.fx.a,func_002A7878(D_L18_002BDA10.f[0],D_L18_002BDA10.f[1]) * (1.0f/60.0f));
        func_00282D30(scratch.fx.v,s,func_002A7878(D_L18_002BDA10.f[2],D_L18_002BDA10.f[3]));
        func_00282CC0(scratch.fx.a,scratch.fx.a,scratch.fx.v);
        func_00282F20(scratch.fx.v,s,func_002A7878(0.0f,1.0f)*len);
        func_00282CC0(scratch.fx.v,scratch.fx.v,o+0x10);
        func_002C16C0(o+0x10,scratch.fx.a,D_L18_002BDA10.i[4],D_L18_002BDA10.i[5],D_L18_002BDA10.i[6],D_L18_002BDA10.i[7],D_L18_002BDA10.f[8],D_L18_002BDA10.f[9],D_L18_002BDA10.f[10],D_L18_002BDA10.f[11],0.0f);
        *(TI *)scratch.fx.c = 0;
        scratch.fx.c[2] = D_L18_002BDA10.f[12];
        *(TI *)scratch.fx.b = *(TI *)scratch.fx.c;
        func_00283098(scratch.fx.b,scratch.fx.b,o+0xC0);
        func_002ACEC0(scratch.fx.b,scratch.fx.b,o+0xC0,func_002A7940());
        if (func_001163B0() & 1)
            func_002BD8B0(&scratch.request,scratch.fx.b,D_L18_002BDA10.i[13],D_L18_002BDA10.i[14],(float)D_L18_002BDA10.i[15],D_L18_002BDA10.i[16],D_L18_002BDA10.i[17]);
    }
    scratch.request.p[4] = o;
    scratch.request.i[5] = 0x10001;
    scratch.request.f[7] = s->f[8];
    scratch.request.i[8] = 1;
    qcopy(&scratch.request,s);
    func_00282F20(&scratch.request,&scratch.request,s->f[9]);
    scratch.request.f[3] = 5627.925f;
    scratch.request.b[0x18] = s->b[0x28];
    scratch.request.b[0x19] = s->b[0x2C];
    scratch.request.h[0x1A/2] = *(u16 *)(o+0xAA);
    if (func_002761F8(o+0x10,pos,0,s->i[4],&scratch.request) || func_00277258(0.2f,pos,0,s->i[4]) || func_00282948(s->b+0x34)) {
        if (D_L18_001BFC18) {
            if (D_L18_001BFC18 != s->i[4]) {
            func_00277F48(o+0x10,0,s->i[4],0.5f,&scratch.request);
            func_002ABBB8(o,D_L18_001A8F20,0,0.0f,0.0f,0,2,10,0.0f,0.0f,9.0f,0.666f,0,0.0f,0,1,-1,0,0x810001);
            func_0029F338(o);
            }
        } else {
            func_002ABBB8(o,D_L18_001A8F20,0,0.0f,0.0f,0,2,8,0.0f,0.0f,9.0f,0.5f,0,0.0f,0,1,-1,0,0x810001);
            func_0029F338(o);
        }
    } else qcopy(o+0x10,pos);
}
