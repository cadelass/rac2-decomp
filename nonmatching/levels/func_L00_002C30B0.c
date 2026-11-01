/* Nonmatching reconstruction, GPT-6.1 Sol high, 2026-10-29.
 * Current pinned game compiler: -O2 -G8 -ffunction-sections -frac2-qcopy
 * -frac2-qcopy-barrier. USA v1.01: 1928/1928 bytes, 0/16 places;
 * first instruction mismatch +0xC (s6 save versus retail s5 save).
 * Relative to the preceding Sol-low draft, explicit current then previous
 * history-index remainder locals improve +0x4E0..+0x51C from 3/16 to 14/16
 * textually identical arithmetic instructions. The remaining two use s3
 * instead of retail s2 for -1. History base allocation/add operand order,
 * counter stores, resident bases and branch merges still differ.
 *
 * regalloc.py's baseline and diagnostic objects were byte-identical. GCSE
 * inserts the timer high-half pseudo 358 before the preceding object loop;
 * it has 4 refs/216 live insns and crosses 6 calls. The resident high half
 * (pseudo 357) has 15 refs/766 live insns and crosses 53 calls. The object
 * class constant 0x16 ends up in fp, requiring the extra save/restore.
 *
 * Eighteen bounded check.py calls, including baseline and final confirmation:
 * gcse-unsplit-edges, no-expensive-optimizations and explicit timer-end local
 * preserve the main blocker. No-gcse removes hoisting but gives 1940 bytes
 * and loses retail's resident high-half reuse. No-split-addresses gives 1868
 * bytes with the same loss. A 448-byte sda timer declaration hoists full
 * addresses; moving the object resident view inside its guard or indexing
 * the object table does not resolve allocation. Typed history views either
 * tie or add address materializations; explicit byte-array sda declarations
 * speculate the load into a branch slot and give 1924 bytes with unwanted GP.
 * Reopen with a measured GCSE/address-lifetime remedy; do not repeat these
 * forms. No linked build or other-release check run. All declarations follow.
 *
 * Previous Sol-low: 1928 bytes, 0/16; phase views/rematerialized counter stores
 * improved the earlier 1908-byte draft. Scoped locals, no-rerun-loop-opt,
 * timer incomplete-array sda and first-copy qcopy were already tried then.
 * The 2026-10-23 draft tested US/US2 at 1908/1928 bytes, 0/16; PAL has no
 * canonical catalogue entry.
 */

extern char D_00189EA0[];
extern char D_00189E20[];
extern int D_00138180[];
extern int D_L00_001A8F00;
extern float D_L00_001B18E0;
extern float D_L00_001B18E4;
extern unsigned int D_L00_001B19C8;
extern char *D_L00_001FACE0[];
extern char D_L00_0025BC60[];
extern unsigned char D_001A7AFF __attribute__((section(".data")));
extern void func_L00_002B9380(void);
extern void func_00282978(void *);
extern void func_00282948(void *);
extern void func_L00_002A7A10(void);
extern int func_002ABB78(void *);
extern int func_002A77E0(int);
extern float func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A8F70(void *, void *, int, void *, void *, float);
extern float func_L00_002D3B00(void *);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DF0(void *);
extern void func_L00_002C3838(void);
extern void func_L00_002D36E0(void *, int, float, float, float);
extern void func_L00_002D3778(void *, void *, float);
extern void func_L00_002B30E8(void);
typedef int UpdateQuad __attribute__((mode(TI)));

/* Advance the resident counters, nearby-object reactions, and movement history. */
void func_L00_002C30B0(void)
{

    float delta[4], step[4];

    { char *p = D_00189E20;
    if (!*(unsigned char *)(p + 0x22BD))
        func_L00_002B9380();
    ++*(int *)(p + 0x1B8);
    ++*(int *)(p + 0x1BC);
    ++*(int *)(p + 0x1C0);
    ++*(int *)(p + 0x1C4);
    func_00282978(p + 0x1E0);
    func_00282978(p + 0x1DC);
    func_00282978(p + 0x1D2);
    func_00282978(p + 0x1E4);
    func_00282978(p + 0x1F8);
    func_00282978(p + 0x1FE);
    func_00282948(p + 0x1D4);
    func_00282978(p + 0x210);
    func_00282978(p + 0x1D0);
    func_00282978(p + 0x1F4);
    func_00282978(p + 0x1F6);
    func_00282978(p + 0x204);
    func_00282978(p + 0x206);
    func_00282978(p + 0x1F0);
    func_00282978(p + 0x1EC);
    func_00282978(p + 0x1EE);
    func_00282978(p + 0x208);
    func_00282978(p + 0x200);
    func_00282978(p + 0x20E);
    func_00282978(p + 0x20A);
    func_00282978(p + 0x214);
    func_00282978(p + 0x212);
    func_00282978(p + 0x1FC);
    func_00282978(p + 0x216);
    func_00282978(p + 0x1FA);
    func_00282978(p + 0x218);
    func_00282978(p + 0x1F2);
    func_00282978(p + 0x21A);
    func_00282978(p + 0x21C);
    func_00282978(p + 0x1DE);
    func_00282978(p + 0x1E6);
    func_00282978(p + 0x222);
    func_00282978(p + 0x224);
    func_00282978(p + 0x226);
    if (!(D_00138180[0x1A0/4] & 4))
        *(short *)(p + 0x20C) = 0;
    if (*(short *)(p + 0x21C))
        func_L00_002A7A10();
    if (*(unsigned char *)(p + 0x22B8))
        ++*(int *)(p + 0x1D8);
    else
        *(int *)(p + 0x1D8) = 0;
    }
    { char *p = D_00189E20;
    if (D_00138180[0x1D4/4]) {
        char *counters = D_00189E20;
        *(int *)(counters + 0x1C8) = 0;
        ++*(int *)(counters + 0x1CC);
    } else {
        char *counters = D_00189E20;
        *(int *)(counters + 0x1CC) = 0;
        ++*(int *)(counters + 0x1C8);
    }
    }
    { char *p = D_00189E20;
    if (*(unsigned char *)(p + 0x22C3) && *(int *)(p + 0x229C) == 0
            && *(int *)(p + 0x340) && *(float *)(p + 0x170) < 0.0016666668f
            && *(float *)(p + 0x184) < 0.0016666668f)
        *(UpdateQuad *)(p + 0x80) = *(UpdateQuad *)(p + 0x2030);
    }
    { char *p = D_00189E20;
    if (*(short *)(p + 0x1454))
        *(int *)(p + 0x1E8) = 0;
    else
        ++*(int *)(p + 0x1E8);
    if (D_L00_001A8F00 == 0) {
        p = D_00189E20;
        if (D_L00_001B18E0 > 0.0f)
            ++*(short *)(p + 0x22A);
        else
            *(short *)(p + 0x22A) = 0;
        p = D_00189E20;
        if (*(short *)(p + 0x22A) > 120) {
            D_L00_001B18E0 = 0.0f;
            *(short *)(p + 0x22A) = 0;
        }
        if (D_L00_001B18E4 > 0.0f)
            ++*(short *)(p + 0x228);
        else
            *(short *)(p + 0x228) = 0;
        p = D_00189E20;
        if (*(short *)(p + 0x228) > 120) {
            *(short *)(p + 0x228) = 0;
            D_L00_001B18E4 = 0.0f;
        }
    }
    }
    { char *p = D_00189E20;
    if (*(short *)(p + 0x224)) {
        char *resident = D_00189E20;
        char **entry = D_L00_001FACE0;
        char *object = *entry;
        if (object) {
            do {
                if ((func_002ABB78(object)
                        || (object && *(char **)(object + 0x24)
                            && *(short *)(*(char **)(object + 0x24) + 0x46) == 0x16))
                        && ((D_L00_001B19C8 & 7) == (((int)object >> 8) & 7)
                            || !func_002A77E0(4))) {
                    if (func_00282E48(D_00189EA0, object + 0x10) < 15.37f) {
                        func_00282CF0(delta, object + 0x10, D_00189EA0);
                        func_00282F20(delta, delta, 1.7f);
                        func_002A8F70(object, *(void **)(resident + 0x2290), 0x4000000,
                                D_00189EA0, delta, 1.0f);
                    }
                }
                object = *++entry;
            } while (object);
        }
    }
    { char *timer = D_L00_0025BC60;
    do {
        func_00282948(timer);
        timer += 0x70;
    } while ((int)timer < (int)(D_L00_0025BC60 + 0x1C0));
    }
    }
    { char *p = D_00189E20;
    *(float *)(p + 0x24DC) = 9999.0f;
    if (*(short *)(p + 0x34E) && func_L00_002D3B00(p + 0xF0) < 0.0f) {
        if (*(int *)(p + 0x23C8) == 0x20) {
            int i;
            char *resident = D_00189E20;
            char *history;
            int samples = 8;
            func_00282C88(delta);
            history = resident + 0x1D90;
            for (i = 0; i < samples; ++i) {
                int index = *(int *)(resident + 0x23C4) - i;
                int current = (index + 31) % 32;
                int previous = (index + 30) % 32;
                func_00282CF0(step, history + current * 16,
                        history + previous * 16);
                func_00282CC0(delta, delta, step);
            }
            func_00282D30(delta, delta, 1.0f / (float)samples);
            if (func_00282DF0(delta) < 0.016666668f)
                ++*(short *)(D_00189E20 + 0x202);
            else
                *(short *)(D_00189E20 + 0x202) = 0;
        }
    } else {
        *(short *)(D_00189E20 + 0x202) = 0;
    }
    func_L00_002C3838();
    }
    { char *p = D_00189E20;
    if (*(unsigned char *)(p + 0x22B4) == 1)
        func_L00_002D36E0(p + 0xE0, 1, 0.0f, 0.0f, 0.4f);
    else
        func_L00_002D36E0(p + 0xE0, 1, 0.0f, 0.0f, 0.7f);
    if ((D_L00_001B19C8 & 3) == 0) {
        p = D_00189E20;
        if (*(unsigned char *)(p + 0x22B4) == 1) {
            *(float *)(p + 0x24A4) = 2.125f;
            *(float *)(p + 0x24A8) = 1.25f;
        } else if (D_001A7AFF) {
            *(float *)(p + 0x24A4) = 14.0f;
            *(float *)(p + 0x24A8) = 4.5f;
        } else {
            *(float *)(p + 0x24A4) = 4.25f;
            *(float *)(p + 0x24A8) = 2.25f;
        }
    }
    }
    { char *p = D_00189E20;
    if (*(float *)(p + 0x31C) < 4.0f) {
        *(UpdateQuad *)(p + 0xD0) = *(UpdateQuad *)(p + 0x2D0);
        func_L00_002D3778(p + 0xD0, p + 0xD0, 0.5f);
    } else {
        *(UpdateQuad *)(p + 0xD0) = *(UpdateQuad *)(p + 0xE0);
    }
    }
    { char *p = D_00189E20;
    char *object = *(char **)(p + 0x5C0);
    if (object) {
        if (!(*(unsigned short *)(object + 0x34) & 0x1000) || object == *(char **)(p + 0x33C))
            *(int *)(p + 0x5C0) = 0;
        if (*(int *)(p + 0x5C0) && *(int *)(p + 0x1248) != 0x2E)
            *(int *)(p + 0x5C0) = 0;
    }
    }
    { char *p = D_00189E20;
    if (*(float *)(p + 0x88) < 1.0f)
        func_L00_002B30E8();
    }
}
