/* Tier: GPT-6.1 Sol (high effort), task v1395, USA v1.01.
 * Best check: 2268/2268 bytes, 0/19 places, first mismatch +0x380.
 * Default game profile: -O2 -G0 -ffunction-sections. Frame 0x1e0 matches.
 * Eight instruction words differ at +0x380..+0x39c: first probe-loop exit
 * and the following object-zero / failure-return scheduling. The other
 * instructions agree modulo relocations. No linked build was attempted.
 * Corrections to the old draft: the height guard uses up, not top; the
 * normal-angle threshold is 0x3eb2b8c4, not 0x3eb2b8c2. Float[4] temporaries
 * avoid TImode scalar bit-insertion code. Typed collision-result fields,
 * approved qcopy transfers, distinct found/edge and height/dot lifetimes,
 * and explicit step/max initialization recover the rest of retail.
 * Fourteen source checks (one declaration failure), plus allocator diagnostics
 * and the final repeat. Reusing i in both loops and returning found for its
 * zero case each tied this source exactly. Explicit break duplicates the
 * object-zero store into an annulled branch delay slot; moving object=0
 * after the failure guard gives a 0x1d0 frame. A conditional increment uses
 * movz; do-while changes loop optimization and gives 2272 bytes.
 * Next: investigate the first loop's original CFG / loop-exit value lifetime
 * before more wording trials. No fake dependencies or volatile accesses.
 * Self-contained declarations below; tested in a dedicated temporary unit.
 */
#include "common.h"
typedef int V4_Fbfdc087a __attribute__((mode(TI)));

typedef struct {
unsigned char pad0[464];
short cooldown;
unsigned char pad1d2[146];
float radius;
unsigned char pad268[180];
float groundHeight;
unsigned char pad320[382];
unsigned char pastApex;
unsigned char pad49f[1945];
float frame;
unsigned char padc3c[5716];
void * moby;
int state;
unsigned char pad2298[4];
int control;
unsigned char pad22a0[20];
unsigned char vehicle;
} LedgeProbeResident;
extern LedgeProbeResident D_00189E20_ledgeProbe;
/* Related ledge-probe flow: OpenRAC/rac1-decomp hero_idle_and_animation.c,
 * check_ledge_grab (GPL-3.0); this version uses oriented vector helpers. */
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00283180(float);
extern float func_00283248(float, float);
extern float func_L00_002D3B00(void *);
extern void func_L00_002D3B58(void *, void *, float);
extern float func_L00_002D3EA8(void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern char *func_002AB1F0(void *);
extern char *func_002AD0B0(void *);
extern int func_00277258(void *, int, void *, float);
typedef struct {
    unsigned char pad0[0x18];
    void *moby;
    unsigned char pad1c[4];
    float position[4];
    unsigned char pad30[16];
    float normal[4];
} LedgeProbeHit;
extern LedgeProbeHit D_L00_001BF200;
#define FL(p,o) (*(float *)((char *)(p)+(o)))
#define IN(p,o) (*(int *)((char *)(p)+(o)))
#define SH(p,o) (*(short *)((char *)(p)+(o)))
#define BY(p,o) (*(unsigned char *)((char *)(p)+(o)))
int func_L00_002ACF88(void *position, void *unused, char *out)
{
    float v0[4], v1[4], v2[4], v3[4], v4[4], v5[4], v6[4], v7[4], v8[4], v9[4], v10[4], v11[4], v12[4], v13[4], v14[4], v15[4], v16[4], v17[4], v18[4], v19[4];
    #define g ((char *)&D_00189E20_ledgeProbe)
    #define hit ((char *)&D_L00_001BF200)
    char *a, *b;
    void *object;
    int go, found, i, kind, ok;
    int edge, j;
    float height;
    float step, max;
    float down, fwd, up, top, drop, rise, back, d, length;
    if (out) IN(out,0x28)=0;
    if (D_00189E20_ledgeProbe.cooldown) return 0;
    go=0;
    if (D_00189E20_ledgeProbe.vehicle==0) {
        if ((D_00189E20_ledgeProbe.control==4 && (D_00189E20_ledgeProbe.pastApex || func_L00_002D3B00(g+0xf0)<0.05833333730697632f)) || D_00189E20_ledgeProbe.control==2 || D_00189E20_ledgeProbe.state==8 || D_00189E20_ledgeProbe.state==25 || D_00189E20_ledgeProbe.state==26) go=1;
        if (D_00189E20_ledgeProbe.state==14 && D_00189E20_ledgeProbe.frame<37.0f) go=0;
    }
    if (D_00189E20_ledgeProbe.vehicle==1) {
        if ((D_00189E20_ledgeProbe.control==4 && D_00189E20_ledgeProbe.pastApex) || D_00189E20_ledgeProbe.control==2 || D_00189E20_ledgeProbe.state==75 || D_00189E20_ledgeProbe.state==73 || D_00189E20_ledgeProbe.state==74) go=1;
    }
    if (out != g+0x550) go=1;
    if (!go) return 0;
    down=-0.7f; fwd=0.3f; up=1.5f; top=1.15f; drop=-1.43f; rise=1.8f; back=0.5f;
    found=0;
    if (D_00189E20_ledgeProbe.vehicle==1) { down=-0.4f; fwd=0.25f; up=0.725f; top=0.7f; drop=-0.71f; rise=0.7f; back=0.32f; }
    qcopy(v0,position);
    func_00282F20(v4,g,D_00189E20_ledgeProbe.radius);
    func_00282CC0(v0,v0,v4);
    func_00282F20(v4,g+0x20,up+0.15f);
    func_00282CC0(v1,v0,v4);
    func_00282F20(v4,g+0x20,-top);
    func_00282CC0(v2,v0,v4);
    func_00282F20(v3,g,fwd*0.25f);
    for(i=0; !found && i<4; i++) {
        func_00282CC0(v1,v1,v3);
        func_00282CC0(v2,v2,v3);
        if(func_002761F8(v1,v2,4,D_00189E20_ledgeProbe.moby,0)) {
            kind=func_00278E78();
            if(kind!=9 && kind!=12 && kind!=0 && func_L00_002D3EA8(D_L00_001BF200.normal)<0.349065899848938f) found=1;
        }
    }
    object=0;
    if(!found) return 0;
    if(D_L00_001BF200.moby) {
        ok=0;
        a=func_002AB1F0(D_L00_001BF200.moby);
        b=func_002AD0B0(D_L00_001BF200.moby);
        if(a && (*(unsigned short *)(a+0x1e)&1)) ok=1;
        else if(b) ok=IN(b,0x3c)&1;
        if(!ok) return 0;
        object=D_L00_001BF200.moby;
    }
    if(out) *(void **)(out+0x38)=D_L00_001BF200.moby;
    qcopy(v6,D_L00_001BF200.position);
    func_00282CF0(v5,v6,position);
    if(up<func_L00_002D3B00(v5)) return 0;
    func_00282F20(v7,g+0x20,0.005f);
    func_00282CC0(v7,v7,v6);
    func_00282F20(v8,g,-1.0f);
    func_00282CC0(v8,v8,v7);
    if(func_002761F8(v8,v7,2,D_00189E20_ledgeProbe.moby,0)) {
        if(!D_L00_001BF200.moby || D_L00_001BF200.moby!=object) return 0;
    }
    if(out) {
        func_00282F20(v9,g+0x20,0.6f);
        func_00282CC0(v9,v9,v6);
        if(func_00277258(v9,4,D_00189E20_ledgeProbe.moby,0.45f)) IN(out,0x34)|=1;
        else IN(out,0x34)&=~1;
    }
    height=func_L00_002D3B00(v5);
    if(height+D_00189E20_ledgeProbe.groundHeight<rise || height<0.5f) return 0;
    *(V4_Fbfdc087a *)v11=0; FL(v11,0)=1.0f; FL(v11,8)=down;
    func_00283098(v11,v11,g);
    edge=0;
    func_00282CC0(v11,v11,v6);
    func_00282CF0(v9,position,v11);
    func_L00_002D3B58(v9,v9,0.0f);
    func_00282CC0(v9,v9,v11);
    func_00282F20(v10,g+0x20,-down*0.2f);
    for(j=0;j<5;j++) {
        if(func_002761F8(v9,v11,2,0,0)) {
            func_00282F20(v12,D_L00_001BF200.normal,1.0f);
            edge=1;
            func_L00_002D3B58(v12,v12,0.0f);
            break;
        }
        func_00282CC0(v9,v9,v10);
        func_00282CC0(v11,v11,v10);
    }
    if(!edge) return 0;
    length=func_00282DB0(g,v12);
    if(!(length<func_00283180(1.134464144706726f))) return 0;
    step=0.03f;
    max=2.4f;
    qcopy(v18,v6);
    func_00282F20(v17,g+0x2c0,-0.05f);
    func_00282F20(v16,v12,step);
    func_00282CC0(v15,v16,v17);
    func_00282CF0(v16,v16,v17);
    func_00282CC0(v13,v18,v16);
    func_00282CC0(v14,v18,v15);
    for(d=0.0f;d<max;d+=step) {
        if(!func_002761F8(v14,v13,4,D_00189E20_ledgeProbe.moby,0)) {
            if(out) {
                qcopy(out+0x10,v18);
                func_00282F20(v19,v12,back);
                func_00282F20(out,g+0x2c0,-drop);
                func_00282CC0(out,v19,out);
                func_00282CC0(out,out+0x10,out);
                FL(out,0x24)=func_00283248(FL(v12,0),FL(v12,4));
                IN(out,0x28)=1;
            }
            return 1;
        }
        qcopy(v18,D_L00_001BF200.position);
        func_00282CC0(v14,v18,v15);
        func_00282CC0(v13,v18,v16);
    }
    return 0;
}
#undef FL
#undef IN
#undef SH
#undef BY
#undef g
#undef hit
