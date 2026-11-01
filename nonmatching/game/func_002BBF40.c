/*
 * Tier: sol-high, task v1133, 2026-10-29. USA v1.01 only.
 * Best: 1480/1480 bytes, 0/28 places; 34 instruction words differ outside
 * relocation bits. Profile: -O2 -G0 -ffunction-sections -g -ffast-math.
 * Remaining: size/quadratic FPR allocation ($f22/$f23), arithmetic scheduling,
 * root ordering and expired-state GPR/store ordering. First difference +0x1D4.
 * Corrects the older draft: size recalculation follows the child-spawn test
 * unconditionally, subject to flag bit 4; it is not the test's else branch.
 * Scoped integer locals and a shared decrement pointer recover the GPR frame.
 * Inline doubled denominator preserves retail's post-root scheduling better
 * than reassigning quadratic before calculating the two roots.
 * The spawn declaration interleaves one FP and integer argument while keeping
 * each EE argument bank's order, count and widths; this matches its call setup.
 * MACRO_ADDR on D_001B168C recovers the absolute assembler-macro float load.
 * All needed declarations follow. No linked-build or matching credit claimed.
 */
#include "common.h"
extern void func_00282CC0(void *,void *,void *),func_00282F20(void *,void *,float);
extern int func_00282978(void *),func_00283CF0(float),func_00283D38(int,int,float);
extern void func_002B9180(void *);
extern float func_002A7878(float,float);
extern char D_001B5340[];
extern char *func_002BBCB0(void *,void *,int,int,int,int,int,float,int,float);
extern float func_00282C10(float), func_00282E48(void *,void *), func_00283CE0(int);
extern void func_00282D30(void *,void *,float), func_002829A8(void *);
extern int func_002A7820(int,int);
extern float D_001B168C MACRO_ADDR;
void func_002BBF40(char *p)
{
    char *q=p+32;
    short *remaining;
    p[8]=(unsigned char)p[8]+1;
    if (((q[0x19]^1)&1)) {
        char *timer;
        func_00282CC0(p+16,p+16,q);
        if(q[0x19]&4) *(float *)(q+8)+=0.00272222236f;
        func_00282D30(q,q,(q[0x19]&2)?0.6f:0.8f);
        timer = p + 56;
        remaining = (short *)(p + 10);
        if(*(short *)(p+10)==func_00283CF0((unsigned char)q[0x1b]*0.85f) && (unsigned char)q[0x1a]<2) {
            if(!(q[0x19]&4)) {
                int i, life, style;
                float size;
                i=4;
                do {
                    --i;
                    life=func_00283CF0((unsigned char)q[0x1b]*func_002A7878(0.9f,1.1f));
                    style=(unsigned char)q[0x18];
                    size=func_002A7878(0.85f,1.0f);
                    func_002BBCB0(p+16,q,*(int *)(q+16),*(int *)(q+20),life,style,(unsigned char)q[0x1a]+1,*(float *)(q+28),(unsigned char)q[0x19],*(float *)(q+12)*size);
                }while(i>=0);
            }
        }
        {
            if(!(q[0x19]&4)) {
                float size, duration, linear, quadratic, root, first, second, b;
                float scaled8, scaled3, denominator;
                size = *(float *)(q + 28);
                duration = func_00283CE0((unsigned char)q[0x1b]);
                linear = 8.0f;
                quadratic = 3.0f;
                scaled8 = size * linear;
                scaled3 = size * quadratic;
                linear = duration * linear;
                denominator = size * scaled8;
                scaled3 = duration * scaled3;
                quadratic = duration * quadratic;
                denominator += scaled8;
                linear -= scaled3;
                linear /= denominator;
                quadratic = (quadratic + linear * scaled8) / (size * -8.0f);
                duration -= func_00283CE0(*(short *)(p + 10));
                duration *= 4.0f;
                duration = quadratic * duration;
                root = func_00282C10(linear * linear - duration);
                first = (-linear - root) / (quadratic + quadratic);
                second = (-linear + root) / (quadratic + quadratic);
                *(float *)(p + 12) = first > second ? first : second;
                b=func_00282E48(p+16,D_001B5340);
                if(b<10.0f) *(float *)(p+12)*=b*0.075f+0.25f;
            }
        }
        if(q[0x19]&2) *(int *)(p+4)=func_00283D38(*(int *)(q+16),0x0fffffff,(float)*(short *)(p+10)/(unsigned char)q[0x1b]);
        else *(int *)(p+4)=func_00283D38(*(int *)(q+20),*(int *)(q+16),(float)*(short *)(p+10)/(unsigned char)q[0x1b]);
        func_002829A8(timer);
        if(func_00282978(remaining)) {
            unsigned int flags = (unsigned char)q[0x19];
            if(flags&2) {
                float size;
                q[0x1b] = (*(short *)(p+10) = (unsigned char)q[0x1b]*3);
                q[0x19]=(q[0x19]&0xfd)|4;
                size=func_002A7878(1.6f,2.0f);
                func_00282F20(q,q,*(float *)(q+12)*size);
            } else {
                int life;
                int duration = (unsigned char)q[0x1b];
                *(int *)(q+16)=*(int *)(q+20);
                q[0x19]=flags|1;
                *(int *)(q+20)=((unsigned char)p[3]==0x48)?0:0x0f2f3f3f;
                life=func_002A7820(duration*2,duration*3);
                if(q[0x19]&8) life*=5;
                q[0x1b]=life;
                *(short *)(p+10)=(unsigned char)life;
            }
        }
    } else {
        int i, life;
        i=func_00283CF0((unsigned char)q[0x1b]*0.75f)+1;
        life=func_00283CF0((unsigned char)q[0x1b]*0.25f)+1;
        *(float *)(q+8)+=0.000833333354f;
        func_00282CC0(p+16,p+16,q);
        func_00282D30(q,q,0.98f);
        if(i<*(short *)(p+10)) *(int *)(p+4)=func_00283D38(*(int *)(q+20),*(int *)(q+16),(float)(*(short *)(p+10)-i)/life);
        else if((unsigned char)p[3]==0x48) *(short *)(p+10)=0;
        else *(int *)(p+4)=(*(int *)(p+4)&0xffffff)|((*(short *)(p+10)*15/i)<<24);
        remaining = (short *)(p + 10);
        if(D_001B168C>1.0f) func_00282978(remaining);
        if(func_00282978(remaining)) func_002B9180(p);
    }
}

