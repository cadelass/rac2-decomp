/* GPT-6.1 Sol high-effort worker, 29 October 2026; retained near miss.
 * Current game compiler, -O2 -G0 -ffunction-sections: 1108/1112 bytes,
 * 0 of 27 USA v1.01 placements match (tools/check.py --diff).
 * Retail's 0x70 frame and saved-register set are reproduced. Controller
 * +0x40/+0x44/+0x48 are signed halfwords. An explicit ended snapshot,
 * typed controller, shared actor-frame snapshot and typed input/playback
 * objects improve the earlier 1080-byte reconstruction.
 * Residual: initial counter store/compare scheduling, the GP flags load in
 * an FP branch slot instead of retail's absolute load, skip-input branch
 * orientation, and stop-call block placement. Best size was reached at
 * trials 3 and 8 and confirmed by a twelfth checker run. No linked build
 * was run.
 * The later explicit per-arm stop-call form aligns the actor loop and
 * teardown after an offset, but is 1104 bytes; signed masks, local boolean
 * snapshots, nested/goto input forms and nosda did not close the residual.
 * Next: independent evidence for skip-input expression/block structure,
 * not forced reloads or scheduling barriers. Required declarations follow.
 */

typedef struct { char prefix[0x3C]; int abort; } SequencePlayback;
extern SequencePlayback D_L00_001BEFC0;
extern float D_L00_001B18E0 __attribute__((sda));
extern int D_001A7A08[] __attribute__((sda));
extern int D_001A7478 __attribute__((sda)), D_001A79F0 __attribute__((sda)), D_001A7B90 __attribute__((sda));
typedef struct { char prefix[0x1A0]; union { unsigned long long all; struct { unsigned int low, high; } word; } buttons; } SequenceInput;
extern SequenceInput D_00138180;
extern short D_001A63AC;
extern void func_00288BB8(void *);
extern int func_002B4B70(int, int);
extern void func_L00_002FC7A8(void);
extern void func_002B6658(void);
extern void func_002E5F60(void);
extern void func_L00_002A6DD0(void);
extern float func_002AA2E8(float *, float, float);
extern int func_002B6D28(void);
extern int func_00288BE8(void *);

extern void func_00293D30(void);
extern int func_002F5AF8(void);
extern void func_0029F390(unsigned char *);
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A0F48(unsigned char *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_002ECB70(void *);
extern void func_002A93B0(void *);
extern void func_L00_002D4E58(void *, int);
extern void func_L00_002A70F8(void *);
extern void func_L00_002FCBE8(void);
extern void func_002914B8(void);
extern void func_0029FFB8(void);

extern int D_L00_001BCAC0[];
extern void func_002B7CE0(int);
extern void func_002F5220(void);
extern void func_002B9390(void);
extern int func_L00_003046D0(int);
extern void func_002E4AC8(void);
extern void func_002F52B8(void);

typedef struct {
    char prefix[0x34];
    int time, frame, chunk;
    short end_time, pad42, count, pad46, fade_time;
    char pad4a[14];
    int done;
    char pad5c[0x130];
    unsigned char *actors[0];
} SequenceState;
#define SEQUENCE ((SequenceState *)D_L00_001BCAC0)

void func_L00_00370408(void) {
    float first[4];
    float second[4];
    int ended;
    unsigned char *object;
    char *path;
    int abort;
    int threshold;
    int complete;
    int i;
    short id;
    if (SEQUENCE->done) return;
    if (SEQUENCE->end_time == 0) {
        func_00288BB8(&D_L00_001BEFC0);
        SEQUENCE->done = 1;
        func_002B4B70(0, 0);
        return;
    }
    func_002F5220();
    func_L00_002FC7A8();
    func_002B6658();
    func_002E5F60();
    func_L00_002A6DD0();
    func_002B9390();
    ++SEQUENCE->time;
    ++SEQUENCE->frame;
    if (SEQUENCE->time < 18) {
        func_002AA2E8(&D_L00_001B18E0, 0.0f, 0.16666667f);
        if (D_L00_001B18E0 > 1.0f) D_L00_001B18E0 = 1.0f;
    }
    if (SEQUENCE->fade_time <= SEQUENCE->time) func_002B6D28();
    ended = SEQUENCE->time >= SEQUENCE->end_time;
    abort = 0;
    if (SEQUENCE->time > 17 && D_L00_001B18E0 == 0.0f) {
        if (((D_001A7A08[0] & -0x10000) == 0 && D_001A7478 == 0 && D_001A79F0 > 0) ||
            !(D_00138180.buttons.word.high & 0x800)) {
            if ((D_00138180.buttons.all & 0x8000000000FULL) == 0x8000000000FULL) abort = 1;
        } else abort = 1;
    }
    if (abort) {
        D_L00_001BEFC0.abort = 1;
        func_00288BB8(&D_L00_001BEFC0);
        SEQUENCE->done = 1;
    } else {
        if (ended) {
            SEQUENCE->done = 1;
            if (func_00288BE8(&D_L00_001BEFC0)) goto finish;
        } else {
            threshold = D_001A7B90 ? 80 : 96;
            if (SEQUENCE->frame >= threshold) {
                ++SEQUENCE->chunk;
                if (D_001A63AC) func_002B7CE0(1);
                func_00293D30();
                func_L00_003046D0(SEQUENCE->chunk + 1);
            }
            complete = func_002F5AF8();
            for (i = 0; i < SEQUENCE->count; i++) {
                object = SEQUENCE->actors[i];
                { int frame = SEQUENCE->frame >> 1;
                object[0x41] = frame + 1;
                object[0x40] = frame; }
                func_0029F390(object);
                *(float *)(object + 0x44) = func_00283CE0(SEQUENCE->frame & 1) * 0.5f;
                if (complete && (SEQUENCE->frame & 1)) *(float *)(object + 0x44) = 1.0f;
                path = *(char **)(object + 0x68);
                func_00282D30(first, path + object[0x40] * 16, 1.0f - *(float *)(object + 0x44));
                func_00282D30(second, path + object[0x41] * 16, *(float *)(object + 0x44));
                func_00282CC0(object + 0x10, first, second);
                object[0x61] = 0xFF;
                func_002A0F48(object);
                if (*(short *)(object + 0xAA) == 0xD54) func_L00_002E6EF8(func_002ECB70, object);
                if (object[0x6F]) func_002A93B0(object);
                id = *(short *)(object + 0xAA);
                if (id == 0 || id == 0xF6B) func_L00_002D4E58(object, 0);
                id = *(short *)(object + 0xAA);
                if (id == 10 || id == 0x1159 || id == 0x57 || id == 0xD6B) func_L00_002A70F8(object);
            }
            goto finish;
        }
    }
    func_002B4B70(0, 0);
finish:
    func_L00_002FCBE8();
    func_002E4AC8();
    func_002914B8();
    func_0029FFB8();
    func_002F52B8();
}
