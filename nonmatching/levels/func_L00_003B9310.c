/* GPT-6.1 Sol (high), worker v1453, USA v1.01, pinned game compiler.
 * Profile: -O2 -G8 -ffunction-sections; use a separate *-g8.c unit.
 * Best: 2472/2472 bytes, 0/27 places, first difference +0xB8.
 * Sixteen instruction words differ after excluding relocation fields:
 * seven at +0xB8..+0xD0 (initial tuning/hero load scheduling), and nine at
 * +0x304..+0x324 (target-selection call setup). This is not a match;
 * relocation consistency and linked symbol bindings remain unvalidated.
 * All declarations are included below. No linked build was run.
 *
 * Corrected two control-flow errors in v1278: func_L00_003B9170 belongs
 * inside the initialization branch (retail +0x44 skips it); the callback
 * condition at +0x880 accepts held-button bits OR inactive/disabled hero,
 * independently of the positive-charge test. A shared target/descriptor
 * scratch recovers old target s3, scratch s0, descriptor s2, direction s4.
 * Scoped sound pointers and saved handle values recover sound-table setup;
 * typed angle, collision and controller globals recover their full bases.
 * The 0x80-byte angle object matches the initialization clear's full extent.
 *
 * Seventeen checker invocations (two C89 declaration-order errors) plus one
 * regalloc run. Debug information and the typed sound view made no change;
 * -fno-gcse grew the body to 2484 bytes. An inline target-point helper
 * reached 2472 but displaced stack-address lifetimes. Reusing candidate
 * as initial scratch rotated s0/s2/s3; independent sound scopes plus a
 * shared descriptor scratch recover the retail allocations instead.
 * A bank-preserving target-selector argument interleaving made no change.
 * Next: establish source ordering/declaration evidence for the two remaining
 * FP setup blocks, without selective volatile accesses or artificial uses.
 *
 * ref_00/ref_01 are GP views of D_L00_001B28E4/D_L00_001B28E0, respectively;
 * the ordinary externs retain absolute accesses. ref_02/ref_03 are GP floats
 * at canonical 001AFCEC/001AFCF0. These aliases still require linked checks.
 */
#include "common.h"

#define I(p,o) (*(int *)((char *)(p)+(o)))
#define S(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(unsigned char **)((char *)(p)+(o)))

typedef struct { float v[4]; } AimVector __attribute__((aligned(16)));
typedef struct {
    unsigned char pad0[0x1d8];
    int f1d8;
    unsigned char pad1dc[0x4];
    short f1e0;
    unsigned char pad1e2[0x15e];
    int f340;
    unsigned char pad344[0xa];
    short f34e;
    unsigned char pad350[0x8a8];
    unsigned char * fbf8;
    unsigned char padbfc[0x634];
    int f1230;
    unsigned char pad1234[0xc];
    int f1240;
    unsigned char pad1244[0x104c];
    unsigned char * f2290;
    int f2294;
    unsigned char pad2298[0x1c];
    unsigned char f22b4;
    unsigned char pad22b5[0x3];
    unsigned char f22b8;
    unsigned char pad22b9[0x3];
    unsigned char f22bc;
    unsigned char pad22bd[0x22f];
    short f24ec;
} AimHero;
extern AimHero D_00189E20;
extern unsigned char D_00188660[];
typedef struct { unsigned char pad0[0x1a0]; int held, pressed; } AimController;
extern AimController D_00138180;
typedef struct {
    unsigned char pad0[0x60];
    float pitch, f64, yaw;
    unsigned char pad6c[0x14];
} AimAngles;
typedef struct {
    unsigned char pad0[0x1924];
    float pitch, yaw;
} AimAlternateAngles;
extern AimAngles D_L00_0023DB20;
extern AimAlternateAngles D_L00_0025BE10;
extern AimVector D_L00_001B8DC0, D_L00_001B8FF0;
typedef struct { unsigned char pad0[0x18]; unsigned char *hit; } AimCollision;
extern AimCollision D_L00_001BF200;
typedef struct {
    unsigned char *target;
    short targetId, delay;
    union { int bits; float value; } height;
    unsigned char *candidate;
    int timer, special, mode;
    unsigned char pad1c[4];
    AimVector origin, direction;
    union { int bits; float value; } charge;
    int charge2, held, handle;
} AimState;
extern AimState *D_L00_001AFD78 __attribute__((sda));
extern int D_L00_001AFCE8 __attribute__((sda));
extern int D_L00_001AFCE0 __attribute__((sda));
extern unsigned short D_L00_001AFCE4 __attribute__((sda));
extern float D_L00_001B28E4, D_L00_001B28E0;
extern float ref_L00_003B9310_00 __attribute__((sda));
extern float ref_L00_003B9310_01 __attribute__((sda));
extern float ref_L00_003B9310_02 __attribute__((sda));
extern float ref_L00_003B9310_03 __attribute__((sda));
extern void func_00282A60(void *,int,int);
extern void func_L00_003B9170(void),func_L00_003B9290(void),func_L00_003B92D0(void);
extern void func_00282D30(void *,void *,float),func_00282CC0(void *,void *,void *);
extern void func_0029FCC0(void *,int,void *),func_00282978(short *);
extern unsigned char *func_002AB1F0(void *);
extern unsigned char *func_L00_003B8E58(void *,void *,void *,float,float,float,float,float);
extern int func_002761F8(void *,void *,int,void *,int),func_00282948(int *);
extern float func_00282E80(void *,void *),func_00282E48(void *,void *),func_00282C48(float);
extern void func_002E59F8(int);
extern void func_00273318(void *,float,unsigned int,void *,int,float,int,float,int);
extern void func_00282CF0(void *,void *,void *),func_00282F20(void *,void *,float);
extern void func_00283698(void *,void *),func_002830C0(void *,void *,void *);
extern float func_00283248(float,float),func_00283B98(float,float),func_00282E20(void *);
extern void func_L00_002C42E0(int,int),func_002AEC48(void *,void *,int,float,float);
extern void func_L00_002AF568(void),func_L00_002AF7D0(void),func_L00_002E6CF0(void (*)(void),void *);
extern void func_L00_003B84F0(void);
extern int func_002E5CF8(int,int,void *);

void func_L00_003B9310(unsigned char *object,AimState *state)
{
    AimVector target, origin, direction, temp;
    unsigned char matrix[64] __attribute__((aligned(16)));
    unsigned char *candidate, *old, *entry;
    float range, cone, angle;
    int initialized=state->mode;
    D_L00_001AFD78=state;
    if (!initialized) {
        state->targetId=-1; state->timer=D_L00_001AFCE8;
        state->charge.bits=0; state->charge2=0; state->target=0;
        state->delay=0; state->height.bits=0; state->special=0;
        D_L00_001AFCE0=0; state->handle=-1;
        func_00282A60(&D_L00_0023DB20,0,128);
        state->mode=1;
        func_L00_003B9170();
    }
    func_L00_003B9290();
    range=D_L00_001B28E4; cone=D_L00_001B28E0;
    ref_L00_003B9310_00=35.0f;
    if (D_00189E20.f2294==29 && (U(D_00189E20.f2290,0x34)&1)) {
        qcopy(&state->origin,&D_L00_001B8DC0); qcopy(&origin,&D_L00_001B8DC0);
        ref_L00_003B9310_01=0.10471976548433304f; angle=0.0872664749622345f;
        if (!state->special) state->target=0;
        state->special=1;
    } else {
        func_00282D30(&origin,D_00189E20.f2290+0xe0,0.75f);
        func_00282CC0(&origin,(char *)&D_00189E20+0x80,&origin);
        if (D_00189E20.f22b4!=4) func_0029FCC0(object,1,&state->origin);
        else func_0029FCC0(D_00189E20.f2290,5,&state->origin);
        angle=0.2617994248867035f; D_L00_001B28E0=angle; state->special=0;
    }
    func_00282978(&state->delay); old=state->target;
    if (old) {
        unsigned char *descriptor;
        entry=old;
        descriptor=func_002AB1F0(entry);
        if (descriptor) {
            func_00282D30(&direction,entry+0xe0,F(descriptor,0x10));
            func_00282CC0(&target,entry+0x10,&direction);
        } else qcopy(&target,entry+0x10);
        if (!old || B(old,0x20)==254 || B(old,0x20)==253 ||
            (descriptor && F(descriptor,0)<=0.0f) || !B(old,0x31) || D_00189E20.f24ec) {
            state->target=0; state->targetId=-1; state->height.bits=0;
        } else D_00189E20.fbf8=old;
    }
    if (state->mode==1 && !D_00189E20.f24ec && !state->delay && !D_L00_001AFCE0 && !D_00189E20.f1e0) {
        qcopy(&direction,&D_L00_001B8FF0);
        if (D_00189E20.f2294==29) direction.v[2]=0;
        func_00282D30(&state->direction,&direction,1.0f);
        candidate=func_L00_003B8E58(&origin,&direction,state->target,angle,cone,range,0.7853982448577881f,0.6108653f);
        if (!candidate) {
            func_00282F20(&temp,&direction,D_L00_001B28E4);
            func_00282CC0(&temp,&temp,&origin);
            if (func_002761F8(&origin,&temp,0,D_00189E20.f2290,0)) {
                unsigned char *hit=D_L00_001BF200.hit;
                if (hit && B(hit,0x20)!=254 && B(hit,0x20)!=253 && S(hit,0xaa)==0xee1) {
                    entry=P(hit,0x68);
                    if ((B(entry,0x3b1)&0x80) && (F(entry,0x3e4)==0.0f || func_00282E80(&origin,object+0x10)<F(entry,0x3e4)))
                        candidate=D_L00_001BF200.hit;
                }
            }
        }
        if (candidate) {
            if (candidate==state->candidate) {
                if (func_00282948(&state->timer)) {
                    unsigned char *newDescriptor;
                    if (state->handle!=-1) {
                        int handle=state->handle;
                        unsigned char *sound=D_00188660+handle*0x70;
                        if (P(sound,0x88)==object && B(sound,0x74)) func_002E59F8(handle);
                    }
                    state->target=candidate; state->handle=-1;
                    state->targetId=U(candidate,0xaa); state->height.bits=0; state->delay=D_L00_001AFCE4;
                    newDescriptor=func_002AB1F0(candidate);
                    if (newDescriptor) {
                        state->height.value=F(newDescriptor,0x10);
                        func_00282D30(&temp,state->target+0xe0,F(newDescriptor,0x10));
                        func_00282CC0(&target,state->target+0x10,&temp);
                    } else qcopy(&target,state->target+0x10);
                }
            } else state->timer=D_L00_001AFCE8;
        } else {
            state->targetId=-1; state->timer=D_L00_001AFCE8; state->target=0; state->height.bits=0;
        }
        state->candidate=candidate;
    }
    if (D_00189E20.f2294==29) func_00273318(object,1.0f,0x600fff0f,0,38,0.0f,-1,90.0f,4);
    if (state->target) {
        float opacity=func_00282C48(0.9f-func_00282E48(&D_L00_001B8DC0,&target)*0.006666667f*0.65f);
        func_00273318(object,opacity,0xff0fff0f,&target,38,0.0f,-1,90.0f,4);
        func_00282CF0(&state->direction,&target,&state->origin);
        func_00282F20(&state->direction,&state->direction,1.0f);
    }
    {
        func_00283698(matrix,object+0xc0);
        func_002830C0(&direction,&state->direction,matrix);
        if (D_00189E20.f22b4!=4) {
            D_L00_0023DB20.yaw=func_00283B98(1.5707964f,func_00283248(direction.v[0],direction.v[1]));
            D_L00_0023DB20.pitch=-func_00283248(func_00282E20(&direction),direction.v[2]);
        } else {
            D_L00_0025BE10.yaw=func_00283248(direction.v[0],direction.v[1]);
            D_L00_0025BE10.pitch=func_00283248(func_00282E20(&direction),direction.v[2]);
        }
    }
    if (state->mode==1 && D_00189E20.f2294!=28 && D_00189E20.f2294!=49) {
        if (D_00189E20.f2294==1) func_L00_002C42E0(29,1);
        if (D_00189E20.f22b4!=4) func_002AEC48(object,&D_L00_0023DB20,D_00189E20.f22b4==4?5:0,ref_L00_003B9310_02,ref_L00_003B9310_03);
        if (D_00189E20.f340 && !D_00189E20.f34e && !D_L00_001AFCE0 && !D_00189E20.f22bc && (D_00138180.held&D_00189E20.f1230) && (D_00189E20.f1240>=16 || D_00189E20.f22b4==4)) {
            if (!state->held) {
                if (D_00189E20.f22b4!=4) {
                    unsigned char *sound;
                    func_L00_002AF568(); sound=D_00188660+state->handle*0x70;
                    if (P(sound,0x88)!=object || !B(sound,0x74)) state->handle=func_002E5CF8(0,4,object);
                }
                state->held=1;
            }
            if (D_00189E20.f340 && !D_00189E20.f34e && (D_00138180.pressed&D_00189E20.f1230)) {
                unsigned char *sound;
                state->charge.bits=0; state->charge2=0;
                sound=D_00188660+state->handle*0x70;
                if (P(sound,0x88)!=object || !B(sound,0x74)) state->handle=func_002E5CF8(0,4,object);
            }
        }
        if (state->charge.value>0.0f || (D_00138180.held&D_00189E20.f1230) || !D_00189E20.f340 || D_00189E20.f34e)
            func_L00_002E6CF0(func_L00_003B84F0,object);
        if (!(D_00138180.held&D_00189E20.f1230) && (D_00189E20.f1d8>=10 || !D_00189E20.f22b8 || !D_00189E20.f340 || D_00189E20.f34e)) {
            if (state->handle!=-1) {
                int handle=state->handle;
                unsigned char *sound=D_00188660+handle*0x70;
                if (P(sound,0x88)==object && B(sound,0x74)) func_002E59F8(handle);
            }
            state->handle=-1;
            if (D_00189E20.f22b4!=4) func_L00_002AF7D0();
            state->held=0;
        }
    }
    func_L00_003B92D0();
}
