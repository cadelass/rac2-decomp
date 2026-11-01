/* GPT-6.1 Sol high worker v1629, 2026-10-29: retained improvement, unlinked.
 * Current pinned profile: -O2 -G16 -ffunction-sections -Wa,-G16.
 * Final check.py: 6516/6516 bytes, 0/8 USA v1.01 placements; first mismatch
 * +0x234 at every place. Opcode alignment is 1628/1629 (difflib, autojunk=False).
 * Eleven instructions differ after excluding relocation immediates:
 *  - L02 003C2924/2928: actor argument move and color's lui are interchanged.
 *  - 003C3194/3198/31A4/31AC: case 9 record base/sum use a1 instead of v0/v1.
 *  - 003C3F50/3F5C/3F60/3F64/3F88: case 10 final reset loop swaps v0/v1.
 * Improvements over v1620:
 *  - Case 1 snapshots mode after the proximity call, before its result is tested,
 *    and refreshes it after the guarded calls. This reproduces retail's gp load
 *    in the first beqz slot and its following absolute flag load, without nosda.
 *  - Case 0's two loops are ascending indexed loops. Loop reversal and strength
 *    reduction generate retail's pointer/countdown registers and initialization
 *    order, including all address setups before the random-angle loop.
 *  - A struct view with completion bytes at +0x464 reproduces the flag-index
 *    operand order and register choice. No level addresses are hard-coded.
 * Bounded negative trials: record pointer local, typed record indexing, and
 * pointer-sized integer arithmetic all leave case 9 unchanged. An actor local,
 * typed rotator fields, a saved-angle local and a vars-pointer local leave the
 * final reset loop unchanged. A color local before the guard leaves its setup
 * unchanged. Explicit vector pointers before the first loop move setup earlier
 * but change registers/accesses; ascending indexing is the measured remedy.
 * Reopen with new source-lifetime/allocation evidence for the three blocks above.
 * PAL and US2 checks report the name in neither catalogue. No linked check was
 * run because this body does not match. Required declarations follow below.
 * The earlier notes below are historical and their residual lists are superseded.
 */
/* GPT-6.1 Sol low worker v1620, 2026-10-29: retained improvement, still unlinked.
 * Current pinned compiler, -O2 -G16 -ffunction-sections -Wa,-G16:
 * 6508/6516 bytes, 0/8 USA v1.01 placements; 1625/1629 opcode alignment
 * (difflib, autojunk=False), up from the retained draft's 1624/1629.
 * Case 4 now uses a widened unsigned timer and explicit previous = timer++;
 * storing timer before testing previous emits retail's lhu/daddu/addiu/sltiu/
 * bnez/sh sequence, replacing the old redundant andi with the required copy.
 * Direct previous+1 shortened that sequence; splitting stores across the branch
 * added an extra branch/store. Duplicating case 1's failure arm compiled unchanged.
 * A nosda declaration for D_001A7B1E reached 6516 bytes and 1626 opcode alignment,
 * but still filled the first delay slot with its lui rather than the target's
 * gp load and changed the flag-test register; equal size was not a match.
 * Retained here is the smaller, minimal counter improvement. Case 0's setup order,
 * case 1's delay-slot fill and scattered allocation differences remain; reopen
 * with independent evidence for their source lifetimes/control-flow shape.
 * Declarations are self-contained below. PAL and us2 check.py both report this
 * name is in neither catalogue; no linked build was run for this unmatched body.
 * Older measurements below describe historical drafts, not this pinned result.
 */
/* Nonmatching (Opus big7 handoff, 2026-10-26): 6508/6516 bytes; opcodes 1621/1629 and
 * full instructions 1588/1629 aligned (difflib vs L02 retail; identical at L03 and L17).
 * Profile: -O2 -G16 -ffunction-sections -Wa,-G16 (unit L02_003C26F0-g16.c).
 * What moved it from 1160/1629 opcodes: retail case order 0,1,4,2,3,9,6,8,7,10,5; then-arm
 * first (`== 7` arms in cases 6/7/9, gate-loop arms in 7, decoration != 0 in 3); inner gate
 * switch order 0,2,3,1; folded TImode assignments (position.bits = *(Quad *)...) where
 * retail has lq 0x10(reg)/sq 0x20(sp), qcopy where it has register addresses; u8 object;
 * duplicated counter address per arm in case 8; common 0xFF store after the case-0 if/else;
 * D_L02_001BA500 as one struct (view at +0x50); D_001A63A8[] selectors; rereads of
 * state->rotators[i] instead of an actor local; one loop counter per loop (cases 6/8/10);
 * int returns for func_L00_002C42E0 and func_002B0CE0 (both set $v0).
 * Still different:
 *  - case 0 matrix block: retail PREs HIGH(D_L02_001C8280) into $fp and rematerialises
 *    gp+0xD30 (D_L02_001AFD20) at the use; this keeps D_L02_001AFD20 in $fp. Retail also
 *    builds row 2 from a fresh lui and stores row1.w through (&D_L02_001C8280)+0x39C, which
 *    only happens here with the rows on a separate D_L02_001C8600 Matrix name (an
 *    overlapping symbol: replace it before landing). Likely a global-alloc priority tie
 *    between the two PRE'd pseudos (both live across the else-arm calls).
 *  - case 1: retail fills the first beqz delay slot from the target (gp lw of
 *    D_L02_001A8F00); here reorg fills it from the fall-through (D_001A7B1E load), 4 bytes.
 *  - case 4: `andi v1,v0,0xFFFF` where retail copies the lhu value (u16 post-increment).
 *  - case 9/10/0: a few v0/v1/a0/a1 choices; case 0 loop-init order (s1/s2), lui a1 slot.
 * Opus big9 (2026-10-26), re-measured on the reload-inheritance base: unchanged at 6508/6516,
 * 1621/1629 opcodes, 1588 full. Findings for the next attempt:
 *  - case 0: gcse PRE hoists four expressions into both arms of the disabled test:
 *    HIGH(rows+0x10) ($s7 in both), &D_L02_001AFD20, HIGH(D_L02_001C8280) and
 *    HIGH(D_L02_0021F4F0). Global-alloc priorities of the middle two are 111 vs 108 (3 refs,
 *    live 268 vs 276), so &D_L02_001AFD20 wins $fp. Putting row 2 on
 *    D_L02_001C8280.transform.row[2] gives retail's $fp = HIGH(...C8280) and the rematerialised
 *    gp+0xD30, but CSE then derives row 2 and the w store from each other. Retail has three
 *    unrelated HIGH computations (rows 1/0/3, row 2, the w store); the same row-2 fresh lui
 *    appears in func_002CA070 (boot, 27 places) and near 0x0037AA14 in L02, so it is a common
 *    idiom (row 1 set, row 0 copied, rows 3 and 2 cleared). Plain CSE relates any two
 *    addresses of one symbol, so the idiom must hide row 2's address from cse1; not found.
 *  - case 1: both reads are the gas macro (`lbu $2,D_001A7B1E` / `lw $3,D_L02_001A8F00`; gas
 *    uses $gp only inside a delay slot). Retail filled the first beqz from the target, which
 *    reorg does only when mostly_true_jump > 0 (EQ test gives 0): a NOTE_INSN_LOOP_BEG just
 *    before the target label or a LOOP_VTOP just after it. do/while and while wrappers did not
 *    produce it.
 *  - 0x3C2AF0 (addu operand order) is unaffected by index spellings.
 
 * Opus big16 (2026-10-26): the case 0 matrix block now matches retail exactly. The rows are
 * written on the real symbol (D_L02_001C8280.transform.row[...]; the overlapping
 * D_L02_001C8600 name is gone) and both clears use qzero_nc (common.h, rac1-decomp's
 * clobber-free qzero): its bare volatile asm flushes cse's table, so row 2's address and the
 * w store's base are rebuilt as in retail ($fp = HIGH(D_L02_001C8280), gp+0xD30
 * rematerialised, fresh lui for row 2). The case-0 notes above about this block are history.
 * Now 6508/6516 bytes, 1624/1629 opcodes, 1605 with registers. Left: the else arm's block
 * before the first func_002A7940 call (retail &position/&target/&rotation and the $fp lui
 * before randomAngle/i; here after), case 1's delay slot, case 4's andi, 0x3C2DD0 and the
 * small v0/v1 choices listed above.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad bits; float f[4]; } Vector;
typedef struct { Vector row[4]; } Matrix;
typedef void (*DrawCallback)(void *);

typedef struct {
    int record, unknown04, delayFrames, unknown0C;
    int linked[2], disabled, restoreMode;
    char *gates[20];
    char *platforms[20];
    char *rotators[20];
    int gateCount, platformCount, rotatorCount, completed;
    u8 *decoration;
    int unknown124;
    float angles[2];
    int retryTimer;
    float savedBrightness, savedAlpha;
    int savedCamera, selector, selectorMode, previousSelector;
} ChallengeState;

typedef struct {
    u8 unknown00[0x80];
    Vector position;
    float unknown90[2], heading;
    u8 unknown9C[0x100 - 0x9C];
    Vector velocity;
    u8 unknown110[0x222 - 0x110];
    u16 controlMode;
    u8 unknown224[0xC28 - 0x224];
    u32 flags;
    u8 unknownC2C[0x1248 - 0xC2C];
    int camera;
    u8 unknown124C[0x2290 - 0x124C];
    u8 *object;
    u8 unknown2294[0x22C8 - 0x2294];
    int cameraRequest;
} PlayerView;

typedef struct {
    u8 unknown00[0x1A0];
    union { u64 all; struct { u32 low, high; } word; } buttons;
} InputView;

extern PlayerView D_00189E20;
extern InputView D_00138180;
extern u8 D_0019B4A8[];
extern int D_001A79F0;
extern u8 D_001A7B1E;
extern s16 D_001A63A8[];
extern u8 D_00139568[];
typedef struct { u8 unknown00[0x14]; int sound; u8 unknown18[0xE0 - 0x18]; } SlotInfo;
extern SlotInfo D_L02_00264A70[];
typedef struct { u8 unknown[0x464]; u8 completed[0]; } ChallengeProgress;
extern ChallengeProgress D_L02_0021F4F0;
extern int D_L02_002004A4 __attribute__((nosda));
extern int D_L02_001A8F00;
extern char *D_L02_001B359C;
extern char *D_L02_001B368C;
extern u16 *D_L02_001FC060[];
extern Vector D_L02_001AFD20 __attribute__((sda));
extern Vector D_L02_001AFD30 __attribute__((sda));
extern float D_L02_001AFD40 __attribute__((sda));
extern float D_L02_001C0968 __attribute__((nosda));
typedef struct { u8 unknown00[0x380]; Matrix transform; } ChallengeGlobals;
extern ChallengeGlobals D_L02_001C8280;
typedef struct { Vector from, to; u8 unknown20[0x30]; char *view; } CameraPath;
extern CameraPath D_L02_001BA500;
extern float D_L02_001B308C, D_L02_001B3090;
extern char D_L02_002A4ED0[], D_L02_002A4F20[], D_L02_002A4F70[];
extern char D_L02_001AFD48[], D_L02_001AFD80[], D_L02_001AFDB8[], D_L02_001AFDF0[];

extern void func_0026FEB8(const char *, ...);
extern int func_002761F8(void *, void *, int, void *, int);
extern float func_00282C48(float);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00282CF0(void *, const void *, const void *);
extern float func_00282E48(const void *, const void *);
extern void func_002830C0(void *, const void *, const void *);
extern float func_00283180(float), func_00283198(float);
extern void func_002833F0(void *, const void *);
extern float func_00283B98(float, float), func_00283C80(float, float);
extern int func_00294630(int);
extern char *func_0029EFD0(int);
extern void func_0029F338(void *);
extern void func_0029FC20(char *, int, char *);
extern void func_0029FCC0(char *, int, char *);
extern void func_002A0430(unsigned int);
extern void func_002A0468(u64 *, u64, u64, u64, u64);
extern void func_002A7750(u8 *, int, int);
extern float func_002A7940(void);
extern int func_002A8508(int, int);
extern void func_002AA800(float *, int, float, float);
extern void func_002AC9F8(float *, float);
extern int func_002B49E0(int, int, int, int, u8 *);
extern int func_002B4B70(int, int);
extern char *func_002C19D8(void *, int, u32, float, float);
extern int func_002E5CF8(int, int, char *);
extern int func_002E5DA0(int, int, char *, int);
extern void *func_0032C700(void *, int, int, int, int, int, int, int,
                         float, float, int, int, int, void *);
extern void func_003355A8(int);
extern int func_L00_002D40F0(void);
extern void func_L00_002E6CF0(DrawCallback, void *);
extern void func_L00_003294F0(u8 *, int);
extern int func_L00_0032EF10(int, int, int *);
extern void func_L00_0042A500(int);
extern void func_L01_002C98B8(void);
extern int func_L02_003C5098(char *);
extern int func_L02_003C4068(char *);
extern void func_L02_003C4E18(char *);
extern void func_L02_003C46E0(void *);


extern void func_00294420(int);
extern int func_002B0CE0(int, int, int);
extern void func_00335370(const void *), func_003353C8(const void *);
extern void func_00335438(const void *, const void *, int, int, int);
extern int func_L00_002C42E0(int, int);
extern void func_L00_002D2168(int, int, float);
extern void func_L01_00323310(int, int);
extern void func_L02_003C4280(char *, int);
extern void func_L02_003C43F0(void *);
extern void func_L02_003C4848(char *);
extern void func_L02_003C49A0(void *, int);
extern void func_L02_003C4C80(char *), func_L02_003C4ED8(char *);
extern void func_L02_003C51F8(char *, u32, u32);
extern void func_L02_003C5438(void *, int, u32, int, u32);

void func_L02_003C26F0(u8 *object)
{
    ChallengeState *state = *(ChallengeState **)(object + 0x68);
    Vector position, target, rotation;
    Matrix transform;
    u32 status;

    switch ((u8)object[0x20]) {
    case 0: {
        char *actor;
        char *records;
        ChallengeGlobals *g;
        Matrix *m;
        char *record;
        int *linked;
        float *randomAngle;
        u16 *list;
        u16 last;
        u16 id;
        int i;
        int status;
        object[0x30] = 0x40;
        if (state->disabled != 0) {
            *(int *)(object + 0x98) = 0;
            *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xEFFF;
        } else {
            for (i = 0; i < 2; i++)
                state->angles[i] = func_002A7940();
            func_0029FCC0(object, 1, (char *)&position);
            qcopy(&target, &position);
            target.f[2] += 1.0f;
            qcopy(&rotation, &position);
            rotation.f[2] -= 1.0f;
            if (func_002761F8(&target, &rotation, 2, object, 0))
                *(float *)(object + 0x18) += (D_L02_001C0968 - position.f[2]) + D_L02_001AFD40;
        }
        state->retryTimer = 60;
        state->gateCount = 0;
        state->platformCount = 0;
        state->rotatorCount = 0;
        state->completed = 0;
        state->decoration = 0;
        records = D_L02_001B368C;
        *(float *)(records + state->record * 0x80 + 0x38) += 2.0f;
        qcopy(&D_L02_001C8280.transform.row[1], records + state->record * 0x80 + 0x30);
        qcopy(&D_L02_001C8280.transform.row[0], &D_L02_001AFD20);
        qzero_nc(&D_L02_001C8280.transform.row[3]);
        qzero_nc(&D_L02_001C8280.transform.row[2]);
        D_L02_001C8280.transform.row[1].f[3] = 0.0f;
        if (func_002A8508((u8)object[0x21], -1) >= 2) {
            list = D_L02_001FC060[(u8)object[0x21]];
            do {
                actor = D_L02_001B359C + (*list & 0x7FFF) * 0x100;
                if (*(short *)(actor + 0xAA) != 0x896)
                    func_002A0468((u64 *)actor, 0x505010ULL, 14ULL, 14ULL, 14ULL);
                if (*(short *)(actor + 0xAA) == 0xA24 && state->gateCount < 20) {
                    state->gates[state->gateCount] = actor;
                    *(float *)(*(char **)(actor + 0x68) + 0x10) = (float)state->delayFrames * 0.016666668f;
                    *(u16 *)(actor + 0x34) |= 0x41;
                    state->gateCount++;
                }
                if (*(short *)(actor + 0xAA) == 0xA55 && state->platformCount < 20) {
                    state->platforms[state->platformCount] = actor;
                    *(float *)(*(char **)(actor + 0x68) + 4) = (float)state->delayFrames * 0.016666668f;
                    *(u16 *)(actor + 0x34) |= 0x41;
                    state->platformCount++;
                }
                if (*(short *)(actor + 0xAA) == 0x873 && state->rotatorCount < 20) {
                    state->rotators[state->rotatorCount] = actor;
                    state->rotatorCount++;
                }
            } while (*(short *)list++ >= 0);
        }
        if (state->gateCount >= 20)
            func_0026FEB8(D_L02_002A4ED0, *(short *)(object + 0xB2));
        if (state->platformCount >= 20)
            func_0026FEB8(D_L02_002A4F20, *(short *)(object + 0xB2));
        if (state->rotatorCount >= 20)
            func_0026FEB8(D_L02_002A4F70, *(short *)(object + 0xB2));
        if (state->rotatorCount == 0)
            func_0026FEB8(D_L02_001AFD48, *(short *)(object + 0xB2));
        if (state->gateCount == 0)
            func_0026FEB8(D_L02_001AFD80, *(short *)(object + 0xB2));
        if (state->platformCount == 0)
            func_0026FEB8(D_L02_001AFDB8, *(short *)(object + 0xB2));
        id = *(u16 *)(object + 0xB2);
        if (D_L02_0021F4F0.completed[(short)id] != 0
            || (status = D_0019B4A8[((short)id >> 1) + D_001A79F0 * 0x400],
                (id & 1) ? ((status >> 4) & 7) != 0 : (status & 7) != 0)) {
                func_L00_003294F0((u8 *)object, 1);
            for (i = 0; i < 2; i++) {
                if (state->linked[i] != -1)
                    func_L00_003294F0((u8 *)(D_L02_001B359C + state->linked[i] * 0x100), 1);
            }
            func_002A7750((u8 *)object, 5, -1);
        } else {
            func_002A7750((u8 *)object, 1, -1);
        }
        object[0x30] = 0xFF;
        break;

    }
    case 1: {
        u8 *ids;
        SlotInfo *slots;
        int nearby = func_L02_003C5098(object);
        int mode = D_L02_001A8F00;

        if (nearby && D_001A7B1E) {
            func_002B0CE0(12, 0x27BD, 1);
            ids = D_00139568;
            slots = D_L02_00264A70;
            if (func_00294630(slots[ids[0x26]].sound) == 0) {
                func_00294420(slots[ids[0x26]].sound);
            } else if (D_00138180.buttons.word.high & 0x10) {
                state->savedCamera = D_00189E20.camera;
                D_00189E20.cameraRequest = 0x26;
                func_L02_003C4E18(object);
                func_002A7750((u8 *)object, 4, -1);
            }
            mode = D_L02_001A8F00;
        }
        if (mode != 2)
            func_L02_003C4ED8(object);
        break;

    }
    case 4: {
        int status;
        func_002B0CE0(1, 0, 1);
        D_00189E20.controlMode = 3;
        status = func_L00_002D40F0();
        if (status == 2 && D_00189E20.object[0x42] == D_00189E20.object[0x43]) {
            func_L00_002C42E0(0x6F, 0);
            func_L00_002D2168(0x54, 0, 7.0f);
            position.f[0] = func_00283180(*(float *)(object + 0xF8)) * 3.0f;
            position.f[1] = func_00283198(*(float *)(object + 0xF8)) * 3.0f;
            position.f[2] = 0.0f;
            func_0029FCC0(object, 0, (char *)&target);
            func_00282CC0(&position, &target, &position);
            qcopy(&rotation, object + 0xF0);
            rotation.f[2] = func_00283B98(*(float *)(object + 0xF8), 3.141593f);
            func_00335438(&D_L02_001BA500.from, &D_L02_001BA500.to, 3, 300, 0);
            func_00335370(&position);
            func_003353C8(&rotation);
            func_002E5CF8(0, 0, object);
            object[0x30] = 0xFF;
            func_002A7750((u8 *)object, 2, -1);
        } else {
            if (status != 0) {
                unsigned int timer = *(u16 *)(object + 0x96);
                unsigned int previous = timer++;
                *(u16 *)(object + 0x96) = timer;
                if (previous < 241)
                    break;
            }
            func_L01_002C98B8();
            func_002A7750((u8 *)object, 1, -1);
        }
        break;

    }
    case 2: {
        float angle;
        func_002B0CE0(1, 0, 1);
        func_0029FC20(object, 1, (char *)&transform);
        func_002830C0(&rotation, &D_L02_001AFD30, &transform);
        func_00282CF0(&D_00189E20.velocity, &rotation, &D_00189E20.position);
        D_00189E20.velocity.f[2] = 0.0f;
        func_002AC9F8(D_00189E20.velocity.f, 0.025000002f);
        angle = func_00283B98(*(float *)(object + 0xF8), 3.1415927f);
        func_002AA800(&D_00189E20.heading, 0, angle, 0.017453296f);
        if (D_00189E20.flags & 2)
            func_L00_002D2168(0x55, 0, 7.0f);
        position.f[0] = func_00283180(*(float *)(object + 0xF8)) * 3.0f;
        position.f[1] = func_00283198(*(float *)(object + 0xF8)) * 3.0f;
        position.f[2] = 0.0f;
        func_0029FCC0(object, 0, (char *)&target);
        func_00282CC0(&position, &target, &position);
        D_00189E20.controlMode = 3;
        if (func_00282E48(&D_L02_001BA500.from, &position) <= 0.05f) {
            func_00335438(&D_L02_001BA500.from, &D_L02_001BA500.to, 2, 300, 0);
            func_00335370(&target);
            func_003353C8(&D_L02_001BA500.to);
            func_002E5CF8(0, 0, object);
            object[0x30] = 0xFF;
            func_002A7750((u8 *)object, 3, -1);
        }
        break;

    }
    case 3: {
        u8 *decoration;
        s16 *selectors;
        char *record;
        int status;
        func_002B0CE0(1, 0, 1);
        D_00189E20.controlMode = 3;
        if (D_00189E20.flags & 2)
            func_L00_002D2168(0x55, 0, 0.0f);
        func_0029FCC0(object, 0, (char *)&position);
        if (func_00282E48(&D_L02_001BA500.from, &position) <= 0.5f) {
            record = D_L02_001B368C + state->record * 0x80;
            qcopy(&target, record + 0x30);
            qcopy(&rotation, record + 0x70);
            qcopy(&transform.row[0], &target);
            transform.row[0].f[2] += 30.0f;
            func_00335438(&transform, &rotation, 2, 480, 0);
            *(int *)(*(char **)(D_L02_001BA500.view + 0x70) + 0xE0) = 0x1C2;
            func_00335370(&target);
            func_003353C8(&rotation);
            state->decoration = (u8 *)func_0029EFD0(0xB12);
            if (state->decoration != 0) {
                state->decoration[0x30] = 0x80;
                *(u16 *)(state->decoration + 0x32) = 0x80;
                *(u16 *)(state->decoration + 0x34) &= 0xFFBE;
                decoration = state->decoration;
                qcopy(decoration + 0x10, record + 0x30);
                *(float *)(decoration + 0x18) += 15.0f;
                *(u16 *)(state->decoration + 0x34) &= 0xFF7F;
            } else {
                func_0026FEB8(D_L02_001AFDF0);
            }
            state->savedBrightness = D_L02_001B308C;
            state->savedAlpha = D_L02_001B3090;
            D_L02_001B308C = 100.0f;
            D_L02_001B3090 = 255.0f;
            state->previousSelector = D_001A63A8[0x1E] != -1 ? D_001A63A8[0x1E] : D_001A63A8[0x24];
            func_L01_00323310(state->selector, state->selectorMode);
            func_002A7750((u8 *)object, 9, -1);
        }
        break;

    }
    case 9: {
        char *actor;
        char *actors;
        char *part;
        u16 *list;
        u16 last;
        func_002B0CE0(1, 0, 1);
        func_L00_002C42E0(0x6F, 1);
        if (func_00282E48(&D_L02_001BA500.from, D_L02_001B368C + state->record * 0x80 + 0x30) <= 1.0f) {
            if (D_L02_001A8F00 == 7) {
                *(u16 *)(object + 0x34) &= 0xFF7F;
                if (func_002A8508((u8)object[0x21], -1) >= 2) {
                    list = D_L02_001FC060[(u8)object[0x21]];
                    actors = D_L02_001B359C;
                    do {
                        actor = actors + (*list & 0x7FFF) * 0x100;
                        *(u16 *)(actor + 0x34) &= 0xFF7F;
                        if (*(short *)(actor + 0xAA) == 0x873) {
                            *(u16 *)(*(char **)(*(char **)(actor + 0x68) + 0x1C) + 0x34) &= 0xFF7F;
                        }
                    } while (*(short *)list++ >= 0);
                }
                func_002A7750((u8 *)object, 6, -1);
            } else {
                if (func_002B49E0(7, 1, (int)object, 1, 0) == 0)
                    break;
                func_003355A8(3);
                D_00189E20.cameraRequest = state->savedCamera;
                func_L00_002C42E0(0, 1);
                D_00189E20.cameraRequest = state->savedCamera;
                if (state->restoreMode != -1)
                    func_L00_0042A500(state->restoreMode);
                func_002A7750((u8 *)object, 1, -1);
            }
        }
        break;

    }
    case 6: {
        char *part;
        char *other;
        char *data;
        char *actor;
        char *vars;
        int i1, i2, i3, i4;
        int status;
        if (D_L02_001A8F00 == 7) {
            func_L00_002E6CF0(func_L02_003C43F0, object);
            if (D_00138180.buttons.all & 0xE000000000ULL) {
                func_L02_003C46E0(object);
            } else if (D_00138180.buttons.word.high & 0x10) {
                D_00189E20.cameraRequest = state->savedCamera;
                func_003355A8(3);
                D_00189E20.cameraRequest = state->savedCamera;
                func_L00_002C42E0(0, 1);
                object[0x30] = 0x40;
                if (state->decoration) {
                    func_0029F338(state->decoration);
                    state->decoration = 0;
                }
                func_L02_003C4848(object);
                for (i1 = 0; i1 < state->rotatorCount; i1++) {
                    *(float *)(state->rotators[i1] + 0xF8) = *(float *)(*(char **)(state->rotators[i1] + 0x68) + 0x10);
                    func_002833F0(state->rotators[i1] + 0xC0, state->rotators[i1] + 0xF0);
                }
                D_L02_001B308C = state->savedBrightness;
                D_L02_001B3090 = state->savedAlpha;
                func_002B4B70(0, 0);
                if (state->restoreMode != -1)
                    func_L00_0042A500(state->restoreMode);
                func_L01_00323310(state->previousSelector, state->selectorMode);
                func_002A7750((u8 *)object, 1, -1);
            } else if (D_L02_002004A4 && func_L00_0032EF10(1, 60, 0)) {
                if (func_L00_0032EF10(2, 60, 0)) {
                    if (state->platformCount > 0)
                        func_002E5DA0(5, 0, state->platforms[0], 0x896);
                    func_002A7750((u8 *)object, 8, -1);
                }
            }
            for (i2 = 0; i2 < state->platformCount; i2++) {
                func_L02_003C4280(state->platforms[i2], 0);
                position.bits = *(Quad *)(state->platforms[i2] + 0x10);
                func_L02_003C5438(&position, 6, 0x88802020, 4, 0x7F6F6FFF);
            }
            for (i3 = 0; i3 < state->gateCount; i3++) {
                status = func_L02_003C4068(state->gates[i3]);
                switch (status) {
                case 0:
                    position.bits = *(Quad *)(state->gates[i3] + 0x10);
                    func_L02_003C5438(&position, 6, 0x88802020, 4, 0x7F6F6FFF);
                    break;
                case 2:
                    data = *(char **)(state->gates[i3] + 0x68);
                    other = D_L02_001B359C + *(int *)data * 0x100;
                    state->completed++;
                    qcopy(&position, other + 0x10);
                    func_L02_003C49A0(&position, 50);
                    func_L02_003C49A0(&position, 50);
                    position.f[2] += 1.0f;
                    func_L02_003C5438(&position, 6, 0x88FF1010, 4, 0x7F6F6FFF);
                    break;
                case 3:
                    vars = *(char **)(state->gates[i3] + 0x68);
                    actor = D_L02_001B359C + *(int *)vars * 0x100;
                    if (*(int *)(*(char **)(vars + 8) + 8) != 0) {
                        qcopy(&position, actor + 0x10);
                        position.f[2] += 1.0f;
                        func_L02_003C5438(&position, 6, 0x88FF1010, 4, 0x7F6F6FFF);
                        --*(int *)(*(char **)(vars + 8) + 8);
                    }
                    break;
                case 1:
                    func_002A7750((u8 *)object, 7, -1);
                    break;
                }
            }
            if (state->completed == state->gateCount) {
                if (state->platformCount > 0)
                    func_002E5DA0(5, 0, state->platforms[0], 0x896);
                func_002A7750((u8 *)object, 8, -1);
            }
        } else {
            if (*(u16 *)(object + 0x96) < 6)
                break;
            func_003355A8(3);
            D_00189E20.cameraRequest = state->savedCamera;
            func_L00_002C42E0(0, 1);
            object[0x30] = 0x40;
            if (state->decoration) {
                func_0029F338(state->decoration);
                state->decoration = 0;
            }
            func_L02_003C4848(object);
            for (i4 = 0; i4 < state->rotatorCount; i4++) {
                *(float *)(state->rotators[i4] + 0xF8) = *(float *)(*(char **)(state->rotators[i4] + 0x68) + 0x10);
                func_002833F0(state->rotators[i4] + 0xC0, state->rotators[i4] + 0xF0);
            }
            D_L02_001B308C = state->savedBrightness;
            D_L02_001B3090 = state->savedAlpha;
            func_L01_00323310(state->previousSelector, state->selectorMode);
            func_002A7750((u8 *)object, 1, -1);
        }
        break;

    }
    case 8: {
        u16 id;
        u8 *counter;
        int idx;
        int i, j, k;
        if (D_L02_001A8F00 == 7) {
            func_L00_002E6CF0(func_L02_003C43F0, object);
            for (i = 0; i < state->platformCount; i++) {
                func_L02_003C4280(state->platforms[i], 1);
                position.bits = *(Quad *)(state->platforms[i] + 0x10);
                func_L02_003C5438(&position, 60, 0x8800FF00, 4, 0x7F6F6FFF);
            }
            if (!(D_00138180.buttons.word.high & 0x10) && *(u16 *)(object + 0x96) < 241)
                break;
            id = *(u16 *)(object + 0xB2);
            if (id & 1) {
                if (((D_0019B4A8[((short)id >> 1) + D_001A79F0 * 0x400] >> 4) & 7) != 7)
                    D_0019B4A8[((short)id >> 1) + D_001A79F0 * 0x400] += 16;
            } else {
                if ((D_0019B4A8[((short)id >> 1) + D_001A79F0 * 0x400] & 7) != 7)
                    D_0019B4A8[((short)id >> 1) + D_001A79F0 * 0x400] += 1;
            }
            func_002A0430((u8)object[0xB0]);
            func_L00_003294F0((u8 *)object, 1);
            for (j = 0; j < 2; j++) {
                if (state->linked[j] != -1)
                    func_L00_003294F0((u8 *)(D_L02_001B359C + state->linked[j] * 0x100), 1);
            }
            func_003355A8(3);
            D_00189E20.cameraRequest = state->savedCamera;
            func_L00_002C42E0(0, 1);
            object[0x30] = 0x40;
            if (state->decoration) {
                func_0029F338(state->decoration);
                state->decoration = 0;
            }
            D_L02_001B308C = state->savedBrightness;
            D_L02_001B3090 = state->savedAlpha;
            func_002B4B70(0, 0);
            if (state->restoreMode != -1)
                func_L00_0042A500(state->restoreMode);
            func_L01_00323310(state->previousSelector, state->selectorMode);
            func_002A7750((u8 *)object, 5, -1);
        } else {
            if (*(u16 *)(object + 0x96) < 6)
                break;
            id = *(u16 *)(object + 0xB2);
            if (id & 1) {
                if (((D_0019B4A8[((short)id >> 1) + D_001A79F0 * 0x400] >> 4) & 7) != 7)
                    D_0019B4A8[((short)id >> 1) + D_001A79F0 * 0x400] += 16;
            } else {
                if ((D_0019B4A8[((short)id >> 1) + D_001A79F0 * 0x400] & 7) != 7)
                    D_0019B4A8[((short)id >> 1) + D_001A79F0 * 0x400] += 1;
            }
            func_002A0430((u8)object[0xB0]);
            func_L00_003294F0((u8 *)object, 1);
            for (k = 0; k < 2; k++) {
                if (state->linked[k] != -1)
                    func_L00_003294F0((u8 *)(D_L02_001B359C + state->linked[k] * 0x100), 1);
            }
            func_003355A8(3);
            D_00189E20.cameraRequest = state->savedCamera;
            func_L00_002C42E0(0, 1);
            object[0x30] = 0x40;
            if (state->decoration) {
                func_0029F338(state->decoration);
                state->decoration = 0;
            }
            D_L02_001B308C = state->savedBrightness;
            D_L02_001B3090 = state->savedAlpha;
            func_L01_00323310(state->previousSelector, state->selectorMode);
            func_002A7750((u8 *)object, 5, -1);
        }
        break;

    }
    case 7: {
        char *actor;
        char *vars;
        int i;
        if (D_L02_001A8F00 == 7) {
            func_L00_002E6CF0(func_L02_003C43F0, object);
            if (state->retryTimer != 0) {
                state->retryTimer--;
            } else if (D_00138180.buttons.word.high & 0x10) {
                func_003355A8(3);
                D_00189E20.cameraRequest = state->savedCamera;
                func_L00_002C42E0(0, 1);
                object[0x30] = 0x40;
                if (state->decoration) {
                    func_0029F338(state->decoration);
                    state->decoration = 0;
                }
                func_L02_003C4848(object);
                for (i = 0; i < state->rotatorCount; i++) {
                    *(float *)(state->rotators[i] + 0xF8) = *(float *)(*(char **)(state->rotators[i] + 0x68) + 0x10);
                    func_002833F0(state->rotators[i] + 0xC0, state->rotators[i] + 0xF0);
                }
                D_L02_001B308C = state->savedBrightness;
                D_L02_001B3090 = state->savedAlpha;
                func_L01_00323310(state->previousSelector, state->selectorMode);
                func_002B4B70(0, 0);
                func_002A7750((u8 *)object, 1, -1);
            } else if (D_00138180.buttons.all & 0xE000000000ULL) {
                func_L02_003C4848(object);
                func_002A7750((u8 *)object, 10, -1);
            }
            for (i = 0; i < state->gateCount; i++) {
                actor = state->gates[i];
                vars = *(char **)(actor + 0x68);
                if (*(int *)(*(char **)(vars + 8) + 4) != 1) {
                    if (*(int *)(vars + 0x14) >= **(int **)(vars + 0x18) - 1) {
                        position.bits = *(Quad *)(actor + 0x10);
                        func_L02_003C5438(&position, 6, 0x5026A883, 4, 0x7F6F6FFF);
                        if (*(u16 *)(object + 0x96) < 2) {
                            func_0032C700(state->gates[i] + 0x10, 0, 0, 0, 0, 0, 0, 1,
                                         1.0f, 20.0f, 0, 0, 0, 0);
                            func_002C19D8(state->gates[i] + 0x10, 0, 0x5026A883, 2.0f, 10500.0f);
                        }
                    } else {
                        position.bits = *(Quad *)(actor + 0x10);
                        func_L02_003C5438(&position, 6, 0x88802020, 4, 0x7F6F6FFF);
                    }
                }
            }
            for (i = 0; i < state->platformCount; i++) {
                position.bits = *(Quad *)(state->platforms[i] + 0x10);
                func_L02_003C5438(&position, 6, 0x88802020, 4, 0x7F6F6FFF);
            }
        } else {
            if (*(u16 *)(object + 0x96) < 6)
                break;
            func_003355A8(3);
            D_00189E20.cameraRequest = state->savedCamera;
            func_L00_002C42E0(0, 1);
            object[0x30] = 0x40;
            if (state->decoration) {
                func_0029F338(state->decoration);
                state->decoration = 0;
            }
            func_L02_003C4848(object);
            for (i = 0; i < state->rotatorCount; i++) {
                *(float *)(state->rotators[i] + 0xF8) = *(float *)(*(char **)(state->rotators[i] + 0x68) + 0x10);
                func_002833F0(state->rotators[i] + 0xC0, state->rotators[i] + 0xF0);
            }
            D_L02_001B308C = state->savedBrightness;
            D_L02_001B3090 = state->savedAlpha;
            func_L01_00323310(state->previousSelector, state->selectorMode);
            func_002A7750((u8 *)object, 1, -1);
        }
        break;

    }
    case 10: {
        char *actor;
        int i1, i2;
        int completed;
        float angle;
        func_L00_002E6CF0(func_L02_003C43F0, object);
        completed = 0;
        for (i1 = 0; i1 < state->rotatorCount; i1++) {
            angle = func_00283C80(*(float *)(*(char **)(state->rotators[i1] + 0x68) + 0x10), *(float *)(state->rotators[i1] + 0xF8));
            if (func_00282C48(angle) >= 0.08f) {
                *(float *)(state->rotators[i1] + 0xF8) = func_00283B98(*(float *)(state->rotators[i1] + 0xF8), 0.05235988274f);
                func_002833F0(state->rotators[i1] + 0xC0, state->rotators[i1] + 0xF0);
            } else {
                completed++;
            }
        }
        if (completed == state->rotatorCount) {
            for (i2 = 0; i2 < state->rotatorCount; i2++) {
                *(float *)(state->rotators[i2] + 0xF8) = *(float *)(*(char **)(state->rotators[i2] + 0x68) + 0x10);
                func_002833F0(state->rotators[i2] + 0xC0, state->rotators[i2] + 0xF0);
            }
            func_002A7750((u8 *)object, 6, -1);
        }
        break;
    }
    case 5: {

        break;

    }
    }

    status = (u8)object[0x20];
    if (status >= 6) {
        if (status == 8)
            func_L02_003C51F8(object, 0xDD107010, 0xDD105010);
        else if (status == 7)
            func_L02_003C51F8(object, 0xFF0000DD, 0xFF000090);
        else
            func_L02_003C51F8(object, 0xFF000070, 0xFF000050);
    }
    if (object[0x31] != 0)
        func_L02_003C4C80(object);
    ++*(short *)(object + 0x96);
}
