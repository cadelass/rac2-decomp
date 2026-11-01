/* GPT-6.1 Sol high tier, v0919; complete C reconstruction, not linked.
 * Profile: -O2 -G8 -ffunction-sections.
 * USA v1.01: 1132/1136 bytes, 0/3 placements (08, 19, 30).
 * The previous retained draft revalidated at 1124 bytes. The unsigned 16-bit
 * ID storage view with signed casts for indexing keeps the tail sign extension
 * inside each parity branch, as retail does. A short nibble gives a branch
 * instead of movn. Keeping the cost comparison's health load independent of
 * the later subtraction restores the retail FP register/compare structure;
 * progress += (1-progress)*factor also restores its add operand order.
 * Remaining: entry table/index allocation, srl versus sra in nibble selection,
 * annulled entry returns, retirement counter address/load, tail address GPRs,
 * and several state-1 load/store schedules. There is still a four-byte deficit.
 * A 1024-byte history row type or -mno-split-addresses worsens address setup;
 * splitting entry loads by parity duplicates them; division by 16 adds bias
 * instructions. A separate active-vehicle local does not solve allocation.
 * Reopen with evidence for the packed-history access and original object-field
 * lifetimes. Only USA v1.01 checked this pass; no linked build or match claimed.
 */

#include "common.h"
typedef int PickupQuad __attribute__((mode(TI)));
extern u8 D_L08_0021EAF0[];
extern u8 D_0019B4A8[];
extern int D_001A79F0 __attribute__((sda));
extern int D_001A79FC[] MACRO_ADDR;
/* Partial resident view through the last state field read here. */
typedef struct {
    u8 unknown00[0x80];
    PickupQuad position;
    u8 unknown90[0x17A0];
    u8 *vehicle;
    u8 unknown1834[0xA60];
    int mode;
    u8 unknown2298[4];
    int world;
} ResidentPrefix;
extern ResidentPrefix D_00189E20;
typedef struct { int duration; int timer; float progress; } PickupState;
extern int D_00138320[];
extern float D_L08_001B031C __attribute__((sda));
extern float D_L08_001B0324 __attribute__((sda));
extern float D_L08_001B032C __attribute__((sda));
extern float D_L08_001B0330 __attribute__((sda));
extern float D_L08_001B0334 __attribute__((sda));
extern int D_L08_001B0370 __attribute__((sda));
extern void func_002A7470(u8 *object, int bank, int anim, int frames);
extern float func_002A89A8(void *position, int flags, float distance);
extern float func_00282E80(void *a, void *b);
extern void func_00282CF0(void *out, void *a, void *b);
extern void func_00282D30(void *out, void *a, float scale);
extern void func_00282FB8(void *out, void *a, float magnitude);
extern void func_00282CC0(void *out, void *a, void *b);
extern int func_00282948(int *timer);
extern void func_0029F338(void *object);
extern void func_L08_003D3EF8(u8 *object);

void func_L08_003D4190(u8 *object)
{
    PickupState *data = *(PickupState **)(object + 0x68);
    u8 *vehicle;
    u8 *vehicleData;
    u8 *history;
    unsigned short id;
    short nibble;
    float cost;
    float movement[4] __attribute__((aligned(16)));
    if (object[0xb0] != 255) {
        id = *(unsigned short *)(object + 0xb2);
        if (D_L08_0021EAF0[0x464 + (short)id])
            return;
        nibble = D_0019B4A8[(D_001A79F0 << 10) + ((short)id >> 1)];
        if (id & 1)
            nibble >>= 4;
        if (nibble & 7)
            return;
    }
    switch (object[0x20]) {
    case 0: {
        float value;
        object[0x30] = 255;
        object[0x31] = 0;
        *(unsigned short *)(object + 0x34) |= 1;
        data->timer = data->duration * 60;
        if (object[0x43])
            func_002A7470(object, 0, 0, 2);
        object[0x20] = 1;
        value = func_002A89A8(object + 0x10, 0, 200.0f);
        if (value != 0.0f)
            *(float *)(object + 0x18) = value;
        break;
    }
    case 1: {
        float value;
        vehicle = D_00189E20.vehicle;
        if (vehicle == 0 || *(short *)(vehicle + 0xaa) != 0xeef ||
            vehicle[0x20] == 254 || vehicle[0x20] == 253 ||
            D_00189E20.mode != 0x31)
            return;
        vehicleData = *(u8 **)(vehicle + 0x68);
        *(u8 **)(vehicleData + 0x1b0) = object;
        value = func_00282E80(object + 0x10, &D_00189E20.position);
        if (value < *(float *)(vehicleData + 0x68)) {
            *(float *)(vehicleData + 0x68) = value;
            *(u8 **)(vehicleData + 0x6c) = object;
        }
        if (!(value < D_L08_001B031C) || !(*D_00138320 & 0x80))
            return;
        { u8 *activeVehicle = D_00189E20.vehicle;
        if (activeVehicle == 0 || (activeVehicle[0x42] != 2 && activeVehicle[0x43] != 2))
            return; }
        func_00282CF0(movement, &D_00189E20.position, object + 0x10);
        func_00282D30(movement, movement, 0.1f);
        movement[2] = 0;
        func_00282FB8(movement, movement, D_L08_001B0334 * 0.0166666675f);
        func_00282CC0(object + 0x10, object + 0x10, movement);
        if (!func_00282948(&data->timer))
            return;
        *(short *)(vehicleData + 0x8e) = 180;
        data->timer = D_L08_001B0370;
        qcopy(object + 0x10, &D_00189E20.position);
        object[0x31] = 1;
        *(unsigned short *)(object + 0x34) = (*(unsigned short *)(object + 0x34) & 0xfffe) | 0x800;
        data->progress = D_L08_001B032C;
        if (object[0x43] != 1)
            func_002A7470(object, 1, 0, 30);
        object[0x20] = 2;
        *(float *)(object + 0x48) = data->progress * 2.0f;
        break;
    }
    case 2: {
        float value;
        value = data->progress;
        value += (1.0f - value) * D_L08_001B0324;
        data->progress = value;
        *(float *)(object + 0x48) = value * 2.0f;
        qcopy(object + 0x10, &D_00189E20.position);
        if (func_00282948(&data->timer) || *(float *)(object + 0x2c) <= 0.0f) {
            cost = D_L08_001B0330 * *(float *)(*(u8 **)(object + 0x24) + 0x24);
            if (cost < *(float *)(object + 0x2c) || D_00189E20.world == 20 ||
                D_00189E20.world == 25 ||
                D_00189E20.mode == 0x39 ||
                D_00189E20.mode == 0x6f) {
                *(float *)(object + 0x2c) -= cost;
            } else {
                D_001A79FC[0]++;
                id = *(unsigned short *)(object + 0xb2);
                if (id & 1) {
                    history = &D_0019B4A8[((short)id >> 1) + (D_001A79F0 << 10)];
                    if (((*history >> 4) & 7) != 7)
                        *history += 16;
                } else {
                    history = &D_0019B4A8[((short)id >> 1) + (D_001A79F0 << 10)];
                    if ((*history & 7) != 7)
                        (*history)++;
                }
                func_0029F338(object);
            }
        } else {
            func_L08_003D3EF8(object);
        }
        break;
    }
    }
}
