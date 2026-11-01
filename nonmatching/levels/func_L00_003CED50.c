/*
 * Tier: sol-high worker v1303, USA v1.01, pinned upstream toolchain.
 * Best: 1764/1764 bytes, 0/2 places; 24 instruction words differ.
 * Standalone flags: -O2 -G8 -ffunction-sections -frac2-keep-block-order.
 * Remaining differences: effect-call argument scheduling at +0x474/+0x478,
 * +0x494/+0x4A0 and +0x56C..+0x5B8. The first pair exchanges the zero FP
 * argument and -1 stack temporary; the second exchanges a0/a2 setup. The
 * later effect call also orders its constants, arguments and store differently.
 * Separate object/list/base locals recover all three indexed-object walks.
 * D_L00_001A8F20 needs MACRO_ADDR; this also recovers collision-branch setup.
 * Corrected the old draft: collision success jumps to DeleteMoby, not closing.
 * Retail writes v repeatedly but passes the uninitialized vb/vc stack vectors;
 * preserve this observed behavior. All required declarations are included.
 * No linked build claimed. Further useful work needs original effect-argument
 * lifetimes; additional FP/integer interleavings and an inline effect helper
 * did not improve this retained result. Explicit-break list loops grew to 1812.
 */
#include "common.h"
typedef struct { char pad[0x10]; int collision; } GateClass;
typedef struct { int child[4]; int destroy_on_child; int close_volume; int block_volume; int group; } GateContext;
typedef struct {
    char pad00[0x10]; float position[4]; u8 state;
    char pad21[3]; GateClass *object_class; char pad28[0xC]; u16 flags;
    char pad36[0xD]; u8 animation; char pad44[0x1C]; u8 anim_flags;
    char pad61[7]; GateContext *context; char pad6c[0xC]; int render_flags;
    char pad7c[0x19]; u8 destroyed; char pad96[2]; int collision;
    char pad9c[0x5C]; float angle; char padfc[4];
} GateObject;
extern short *D_L00_001FA920[];
extern GateObject *D_L00_001B1E9C;
extern char D_00189EA0[];
extern char D_L00_001A8F20[] MACRO_ADDR;
extern int func_002A8508(int,int);
extern float func_00282E80(void *,void *);
extern int func_002ACBC8(void *,int);
extern void func_002A7470(void *,int,int,int);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *,void *,void *);
extern int func_00277258(void *,float,int,void *);
extern int func_002E5CF8(int,int,void *);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_002B0A68(void *,int,void *,float,float,float,float,int);
extern void func_0029F338(void *);
void func_L00_003CED50(GateObject *m)
{
    GateContext *d=m->context;
    int i;
    float v[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float vb[4] __attribute__((aligned(16)));
    float vc[4] __attribute__((aligned(16)));
    if(m->state==0) {
        if(D_L00_001FA920[d->group] && func_002A8508(d->group,-1)>=2) {
            GateObject *base=D_L00_001B1E9C;
            short *p=D_L00_001FA920[d->group];
            do {
                GateObject *o=base+(*p&0x7fff);
                o->flags|=0x43;
                o->collision=0;
            } while(*p++>=0);
        }
        if(func_00282E80(m->position,D_00189EA0)<6.0f &&
           !func_002ACBC8(D_00189EA0,d->close_volume) &&
           !func_002ACBC8(D_00189EA0,d->block_volume)) {
            m->state=1; m->render_flags=0x24c102;
            if(m->animation!=1) func_002A7470(m,1,0,0);
            m->collision=0;
            if(D_L00_001FA920[d->group] && func_002A8508(d->group,-1)>=2) {
                GateObject *base=D_L00_001B1E9C;
                short *p=D_L00_001FA920[d->group];
                do {
                    GateObject *o=base+(*p&0x7fff);
                    o->flags&=0xffbc;
                    o->collision=o->object_class->collision;
                } while(*p++>=0);
            }
        } else if(func_002ACBC8(D_00189EA0,d->close_volume)) m->state=5;
        for(i=0;i<4;i++) {
            if(d->child[i]!=-1) {
                GateObject *o=D_L00_001B1E9C+d->child[i];
                if(o->destroyed || (s8)o->state<0) {
                    if(d->destroy_on_child) {
                        goto destroyed;
                    }
                    m->state=1;
                    if(m->animation!=1)func_002A7470(m,1,0,0);
                    m->collision=0;
                }
            }
        }
    }
    if(m->state==1 && (m->anim_flags&2)) {
        m->state=3;m->render_flags=0x224c1;
        if(m->animation!=2)func_002A7470(m,2,0,0);
    }
    if(m->state==2) {
        v[0]=func_00283180(m->angle-1.5707964897155762f)*0.3f;
        v[1]=func_00283198(m->angle-1.5707964897155762f)*0.3f;v[2]=0;
        func_00282CC0(m->position,m->position,v);
        qcopy(a,m->position);qcopy(b,m->position);qcopy(c,m->position);
        a[2]+=0.75f;b[2]+=0.75f;c[2]+=0.75f;
        v[0]=func_00283180(m->angle)*0.8f;
        v[1]=func_00283198(m->angle)*0.8f;v[2]=0;
        v[0]=func_00283180(m->angle+3.1415929794311523f)*0.8f;
        v[1]=func_00283198(m->angle+3.1415929794311523f)*0.8f;v[2]=0;
        func_00282CC0(b,b,vb);func_00282CC0(c,c,vc);
        if(func_00277258(a,0.6f,0,m) || func_00277258(b,0.68f,0,m) || func_00277258(c,0.68f,0,m)) {
            func_002E5CF8(2,0,m);
            func_002ABBB8(m,D_L00_001A8F20,a,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
            goto delete_object;
        }
    }
    goto closing;
destroyed:
    m->state=12;
    qcopy(v,m->position);v[2]+=1.0f;
    func_002E5CF8(2,0,m);
    a[0]=func_00283180(m->angle-1.5707964897155762f)*0.3f;
    a[1]=func_00283198(m->angle-1.5707964897155762f)*0.3f;a[2]=0;
    func_002ABBB8(m,D_L00_001A8F20,v,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
    func_002B0A68(m,255,a,3,6,3,6,255);
delete_object:
    func_0029F338(m);return;
closing:
    if(m->state==3 && func_002ACBC8(D_00189EA0,d->close_volume)) {
        m->state=4;
        if(m->animation!=3)func_002A7470(m,3,0,0);
    }
    if(m->state==4 && (m->anim_flags&2)) {
        m->state=5;m->collision=m->object_class->collision;
        if(m->animation!=0)func_002A7470(m,0,0,0);
    }
}
