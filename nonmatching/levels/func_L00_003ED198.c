/* GPT-6.1 Sol (high effort), task v0822, USA v1.01.
 * Best check.py: 1712/1720 bytes; 0 of 27 places match.
 * Required profile: -O2 -G0 -ffunction-sections -g; declarations below.
 * Improved over the sol-low draft: index-first byte-offset table addressing
 * fixes s7/fp and the addu operand order; sda on D_L00_001B19C8 fixes the
 * final modulo load; one shared tracking/trail pointer fixes phase to s0.
 * Remaining: delta address uses s1 directly instead of v0 then s5, and the
 * trail delta lacks retail's s0-to-s5 copy. Trail counter/position/particle
 * registers remain s2/s3/s5 instead of s1/s2/s3. This accounts for the two
 * missing moves. No linked build run for this unmatched function.
 * Ascending for/do loops tie; moving pointer assignment after vector calls,
 * enclosing the stack arrays in a struct, and using individual vector structs
 * all tie with this draft. Explicit trail/particle pointer aliases change
 * allocation but do not improve it. A reordered union changed stack offsets.
 */

#include "common.h"
extern void func_00282D30(char *, char *, float);
extern void func_002AFFD8(void *, void *, int);
extern int func_L00_003EE228(char *);
extern char *func_002AB1F0(char *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00300190(void *, void *);
extern float func_00283B98(float, float);
extern void func_L00_003EE100(char *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_L00_003EDB98(void *, int, int);
extern void func_00334160(void *, int, int);
extern int func_00282948(void *);
extern void func_L00_003EDEE0(void *);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern char *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void func_L00_002E6EF8(void *, void *);
extern void func_0029F338(void *);
extern char D_00139568[];
typedef struct { unsigned char flag[4]; unsigned char enabled; char pad[0x6B]; float value; char tail[0x6C]; } B0714Entry;
extern B0714Entry D_L00_00262570[];
extern char *D_0018C0B0 NOT_SDA;
typedef struct { char pad[0x18]; char *target; char pad1[4]; float position[4]; } B0714Hit;
extern B0714Hit D_L00_001BF200;
extern char D_L00_001A8F20[] __attribute__((sda));
extern unsigned char *D_L00_001FEA14;
extern unsigned char *D_L00_001FE9F4;
extern int D_L00_001B19C8 __attribute__((sda));
extern char func_L00_003ED850[];

void func_L00_003ED198(char *obj)
{
    float old[4], scratch[4], previous[4], delta[4], temp[4];
    unsigned char hit[48];
    float particle[4];
    char *state = *(char **)(obj + 0x68);
    char *target;
    char *info;
    char *p;
    float *tracking_delta;
    float length, speed, scale;
    int phase, i;

    qcopy(old, obj + 0x10);
    func_002AFFD8(obj + 0x10, scratch, 1);
    qcopy(previous, obj + 0x10);
    target = *(char **)(state + 0x1C);
    if (target) {
        if (*(unsigned char *)(target + 0x20) == 0xFE) goto clear_target;
        if (*(unsigned char *)(target + 0x20) == 0xFD) goto clear_target;
        if (func_L00_003EE228(target)) goto clear_target;
        {
            func_00282CF0(tracking_delta = delta, *(char **)(state + 0x1C) + 0x10, obj + 0x10);
            info = func_002AB1F0(*(char **)(state + 0x1C));
            if (info) {
                func_00282D30((char *)temp, *(char **)(state + 0x1C) + 0xE0, *(float *)(info + 0x10));
                func_00282CC0(tracking_delta, tracking_delta, temp);
            }
            length = func_00282DF0(tracking_delta);
            if (length == 0.0f) goto clear_target;
            {
                speed = *(float *)(state + 0x2C);
                func_00282D30(state + 0x20, (char *)tracking_delta, speed / length);
                *(float *)(state + 0x2C) = speed;
            }
        }
    }
    goto target_done;
clear_target:
    *(char **)(state + 0x1C) = 0;
target_done:
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        func_00282CC0(obj + 0x10, obj + 0x10, state + 0x20);
        func_00300190(obj + 0x10, obj + 0x10);
        *(float *)(obj + 0xF0) = func_00283B98(*(float *)(obj + 0xF0), *(float *)(state + 0x44));
        *(float *)(obj + 0xF4) = func_00283B98(*(float *)(obj + 0xF4), *(float *)(state + 0x48));
        *(float *)(obj + 0xF8) = func_00283B98(*(float *)(obj + 0xF8), *(float *)(state + 0x4C));
        func_L00_003EE100(obj);
        *(char **)(hit + 0x10) = obj;
        *(int *)(hit + 0x14) = 0x10000;
        *(float *)(hit + 0x1C) = ((B0714Entry *)((unsigned char)D_00139568[0x1F] * 0xE0 + (char *)D_L00_00262570))->value;
        *(int *)(hit + 0x20) = 1;
        qcopy(hit, state + 0x20);
        func_00282F20(hit, hit, 1.0f);
        *(float *)(hit + 0xC) = 5627.925f;
        *(short *)(hit + 0x1A) = *(unsigned short *)(obj + 0xAA);
        hit[0x18] = 1;
        hit[0x19] = 1;
        if (func_002761F8(previous, obj + 0x10, 0, D_0018C0B0, hit)) {
            if (!D_L00_001BF200.target) func_L00_003EDB98(D_L00_001BF200.position, 15, 0);
            else if (*(int *)(D_L00_001BF200.target + 0x98)) {
                func_L00_003EDB98(D_L00_001BF200.position, 10, 1);
                if (((B0714Entry *)((unsigned char)D_00139568[0x1F] * 0xE0 + (char *)D_L00_00262570))->enabled)
                    func_00334160(D_L00_001BF200.target, 0x3D, *(int *)(obj + 0xB8));
                else
                    func_00334160(D_L00_001BF200.target, 0x1F, *(int *)(obj + 0xB8));
            }
            *(unsigned char *)(obj + 0x20) = 1;
            *(char **)(state + 0x1C) = 0;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            *(int *)(state + 0x38) = 6;
        } else if (func_00282948(state + 0x38)) {
            func_L00_003EDEE0(obj + 0x10);
            *(unsigned char *)(obj + 0x20) = 1;
            *(char **)(state + 0x1C) = 0;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            *(int *)(state + 0x38) = 6;
        }
        phase = func_002A77E0(255);
        p = func_002C65A0(obj + 0x10, D_L00_001A8F20, 2, 0x202080, phase, 64, 16, 420000.0f, 420000.0f, 0.0f, 1);
        if (p) p[2] = *D_L00_001FEA14;
        p = func_002C65A0(obj + 0x10, D_L00_001A8F20, 2, 0x202080, (phase + 128) % 255, 64, 16, 420000.0f, 420000.0f, 0.0f, 1);
        if (p) p[2] = *D_L00_001FEA14;
        func_00282CF0(tracking_delta = delta, obj + 0x10, previous);
        func_00282D30((char *)tracking_delta, (char *)tracking_delta, 0.1f);
        qcopy(temp, previous);
        for (i = 4; i >= 0; i--) {
            phase = func_002A77E0(255);
            scale = func_002A7878(0.1f, 0.3f);
            particle[0] = temp[0] + func_002A78D8(0.0f, 0.05f);
            particle[1] = temp[1] + func_002A78D8(0.0f, 0.05f);
            particle[2] = temp[2] + func_002A78D8(0.0f, 0.05f);
            func_002C65A0(particle, D_L00_001A8F20, 15, 0x808080, phase, 32, 0, scale * 210000.0f, scale * 42000.0f, 0.0f, 1);
            func_00282CC0(temp, temp, tracking_delta);
        }
        if (D_L00_001B19C8 % 10 == 0) {
            p = func_002C65A0(obj + 0x10, D_L00_001A8F20, 30, 0x202080, 0, 32, 0, 2100.0f, 420000.0f, 0.0f, 1);
            if (p) p[2] = *D_L00_001FE9F4;
        }
        func_L00_002E6EF8(func_L00_003ED850, obj);
        break;
    case 1:
        if (func_00282948(state + 0x38)) {
            func_0029F338(obj);
            return;
        }
        func_L00_002E6EF8(func_L00_003ED850, obj);
        break;
    }
    if (*(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f ||
        *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f ||
        *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f)
        func_0029F338(obj);
}
