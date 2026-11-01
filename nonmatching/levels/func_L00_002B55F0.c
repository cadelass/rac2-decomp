/* Tier: sol-high, task v0997, USA v1.01, pinned game compiler, -O2 -G8.
 * Best check.py: 1176/1176 bytes, 0 of 17 places match; first mismatch +0x1c4.
 * Separate initial/cap pointers and direct typed root fields recover the prologue
 * and offset setup. Remaining: collision-loop block order, root/hit/position
 * allocation (s2/s1/s0 versus retail s1/s0/s2), and copy-result store order.
 * Next: a loop form preserving the mode-15 block before the ordinary path after
 * rotation. Explicit gotos, switch, keep-block-order and -g did not solve it;
 * FP-first collision signatures preserve the EE argument banks and improve two
 * argument loads. Full loop field typing grows to 1224 bytes; no-thread-jumps
 * regresses the first mismatch. Stopped after 17 exploratory checks plus a final recheck.
 * Required declarations are below. Reference: public OpenRAC/rac1-decomp,
 * src/overlays/l05_rilgar/hero_collision.c, Camera_MoveWithCollision (GPL-3.0).
 */
#include "common.h"
typedef struct {
    unsigned char pad218[0x218];
    short f218;
    unsigned char pad254[0x254-0x21a];
    float f254;
    unsigned char pad22b4[0x22b4-0x258];
    unsigned char f22b4;
    unsigned char pad22c3[0x22c3-0x22b5];
    unsigned char f22c3;
} MoveRoot;
extern MoveRoot D_00189E20;
#define ROOT ((char *)&D_00189E20)
extern int D_L00_001A8FF0 __attribute__((section(".sdata")));
extern char D_L00_001BF230[];
extern void func_00282C88(void *);
extern void func_L00_002D49F0(void);
extern float func_00282DB0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_L00_002D36E0(void *, int, float, float, float);
extern void func_L00_002D38A0(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00277258(float, void *, int, void *);
extern int func_L00_002E0200(float, float, void *, int, void *);
extern int func_00278870(float, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);

int func_L00_002B55F0(int mode) {
    float saved[4], tmp[4], d[4];
    char *initial = ROOT;
    char *a, *cap;
    char *b, *p;
    int i, r, m, steep;
    float len;
    if (*(short *)(initial + 0x1f0) != 0) return 1;
    qcopy(saved, initial + 0x80);
    func_00282C88(tmp);
    if (*(short *)(initial + 0x24fe) != 0) {
        func_L00_002D49F0();
        *(short *)(initial + 0x24fe) = 0;
    }
    steep = 0;
    if (-0.92f < func_00282DB0(initial + 0x20, initial + 0x2c0)) steep = 1;
    m = *(int *)(initial + 0x229c);
    if (m == 15 || m == 17) {
      if (m == 15) {
        func_00282C88(tmp);
        tmp[2] = 0.8f;
        func_00283098(tmp, tmp, *(char **)(initial + 0x2290) + 0xc0);
      }
    } else {
        if (D_00189E20.f22c3 != 0 || D_00189E20.f218 != 0 || steep) {
            if (D_00189E20.f22b4 == 2) {
                func_L00_002D38A0(tmp, tmp, 5.0f);
            } else if (D_00189E20.f22c3 == 1 || D_00189E20.f218 != 0) {
                func_L00_002D36E0(tmp, 0, 0.0f, 0.0f, 0.6f);
            } else if (D_L00_001A8FF0) {
                func_L00_002D38A0(tmp, tmp, 0.77f);
            } else {
                func_L00_002D36E0(tmp, 0, 0.0f, 0.0f, D_00189E20.f254);
            }
        } else tmp[2] = D_00189E20.f254;
    }
    func_00282CC0(ROOT + 0x80, ROOT + 0x80, tmp);
    for (i = 0; i < 8; i++) {
        a = ROOT;
        if (*(int *)(a + 0x229c) == 17) {
            if (func_00277258(0.6f, a+0x80, 0x24, *(void **)(a+0x2290)) == 0) break;
            goto resolved;
        }
        if (*(int *)(a + 0x229c) == 15) {
            if (func_00277258(0.45f, a+0x80, 0x24, *(void **)(a+0x2290)) == 0) break;
            goto resolved;
        }
        {
            int hit;
            if (*(u8 *)(a+0x22c3) != 0 || steep) {
                hit = func_00277258(*(float *)(a+0x264), a+0x80, 0x24, *(void **)(a+0x2290));
            } else {
                float t = *(float *)(a+0x250) - *(float *)(a+0x254);
                if (t < 0.05f) t = 0.05f;
                hit = func_L00_002E0200(*(float *)(a+0x264), t, a+0x80, 0x24, *(void **)(a+0x2290));
            }
            if (*(short *)(a+0x1e6) == 0) hit |= func_00278870(*(float *)(a+0x264), a+0x80);
            if (!hit) break;
        }
resolved:
        p = ROOT+0x80;
        qcopy(p, D_L00_001BF230);
        qcopy(p+0x1b0, D_L00_001BF230+0x10);
        qcopy(p+0x1c0, D_L00_001BF230-0x10);
        p -= 0x80;
        *(int *)(p+0x26c) = *(int *)(D_L00_001BF230-0x18);
        *(u8 *)(p+0x287) = 1;
    }
    b = ROOT+0x80;
    func_00282CF0(b,b,tmp);
    func_00282CF0(d,b,saved);
    len = func_00282DF0(d);
    if (*(float *)(b+0x1e4)*1.5f < len) {
        if (mode == 15) {
            if (d[0]>512.0f) d[0]=512.0f; else if (d[0]<-512.0f) d[0]=-512.0f;
            if (d[1]>512.0f) d[1]=512.0f; else if (d[1]<-512.0f) d[1]=-512.0f;
            if (d[2]>512.0f) d[2]=512.0f; else if (d[2]<-512.0f) d[2]=-512.0f;
            cap=ROOT;
            func_00282F20(d,d,*(float *)(cap+0x264));
            func_00282CC0(cap+0x80,saved,d);
        }
        return -1;
    }
    return 1;
}
