/* GPT-6.1 Sol high, v0825, 2026-10-29: USA v1.01, 300/300 bytes,
 * 0/27 placements. Profile: -O2 -G0 -ffunction-sections -frac2-qcopy
 * -frac2-qcopy-barrier. All declarations follow; common.h supplies qcopy.
 * Writing count through base[i] and state through rec recovers retail's
 * s0/s1/s2 record/target/count allocation, record-relative field offsets,
 * all loop updates and the final count/state store order. The source puts
 * the state store first because scheduling moves it into the branch slot.
 * Remaining: 17 non-relocation instruction differences, all in the entry,
 * the kind store, and the outer-index increment/test. Base is loaded into
 * v1 instead of v0, so kind/index use t1/t0 instead of t0/v1. First +0x04.
 * Indexing both final stores instead shrinks to 292 bytes. Integer/byte
 * views of the pointer global, an earlier index declaration, mixed integer/
 * float parameter order and -g tie on this best draft; -fno-rerun-loop-opt
 * tied on the 292-byte variant. No linked build. Next: explain why the
 * initial base pseudo stays in v1 in local allocation.
 */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

typedef struct { TI128 pos; TI128 dir; float target[4]; int owner, kind, busy; float scale; int state, count, pad[2]; } EffectRecord;
extern EffectRecord *D_L00_001B2B50;

extern void func_00282F20(char *a, char *b, float c);


extern void func_00282DD8(char *a, char *b, char *c);

extern float func_002A7940(void);
extern void func_L00_003E6778(char *, int, float, float, int);
extern void func_00282CC0(void *, void *, void *);


extern float func_00283B98(float a, float b);

void func_L00_003E64F8(char *owner, int a1, void *a2, void *a3, float f12)
{
    EffectRecord *base = D_L00_001B2B50;
    EffectRecord *rec;
    TI128 local;
    float v;
    int i = 0;
    int j;

    do {
        rec = &base[i];
        if (rec->owner == 0) {
            rec->kind = a1;
            rec->scale = f12;
            rec->owner = (int)owner;
            rec->busy = 0;
            qcopy(rec, a3);
            qcopy(rec->target, a2);
            rec->target[2] = *(float *)((char *)owner + 0x18);
            func_00282F20((char *)&local, (char *)a3, 2.0f);
            func_00282CC0((char *)&local, (char *)&local, (char *)rec->target);
            func_00282DD8((char *)&rec->dir, (char *)rec->target, (char *)&local);
            v = func_002A7940();
            for (j = 47; j >= 0; j--) {
                func_L00_003E6778((char *)rec, 2, v, 0.0f, 0);
                v = func_00283B98(v, 0.1336848f);
        }
        rec->state = 0;
        base[i].count = 0;
        break;
        }
    } while (++i <= 0);
}
