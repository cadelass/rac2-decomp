/* func_002A68A8 - 564 bytes, 28 places. Tier: Claude Opus 5.5 (xhigh), 31 October 2026.
   Best check.py result: 564/564 bytes, 0/28 places, 4 instructions differ, first at +0x214.
   Replaces the marker in src/game/002A0430.c (-O2 -G8 -ffunction-sections); needs only the
   declarations below.

   All three loops now match byte for byte. The earlier `count`/`limit` locals are what kept them
   off: reading D_00239BA0[D_00139568[i]].count twice through a record pointer lets cse/gcse turn
   the second read into retail's retained `daddu $v1,$v0,$zero`, which also fixes every head
   register. Distinct i/j/k indices are needed for $a1/$a0/$a0, and the pointer for `lhu 0x8E(reg)`
   (a direct array.field folds the symbol with 0x8E).

   Only two swapped pairs remain, both scheduling:
     mine:   addiu $a0,2; addiu $v1,1; movn $a0,$v1,$v0; ld $s0; daddu $v0,$a0; ld $ra
     retail: addiu $v1,1; addiu $a0,2; movn $a0,$v1,$v0; ld $s0; ld $ra; daddu $v0,$a0
   The per-arm `r = f(5) ? 1 : 2` below is what gets the allocation and movn: cross-jumping merges
   the arms (retail's `b` from loop 2 into the tail has that shape) and the join label stops combine
   merging the cmove into the copy to $v0. That label survives until sched2, because cross-jumping
   runs after it, so `set $v0` stays at the head of the epilogue block; retail schedules it as in a
   one-block tail.

   A single common tail has the right order of ld/ld/daddu but the wrong registers. Best such form,
   `if (f(5) != 0) return 1; return 2;`: addiu $a0,1; addiu $v1,2; movn $v1,$a0,$v0; ...; daddu $v0,$v1.
   Local allocation gives the shorter-lived `2` first pick. Also measured, no better: ternaries in
   both polarities, x/r locals, reuse of sum or the first parameter, short/uchar/long returns
   (long: 568 bytes), reassigning the random result in an if/else (keeps a branch, 560-564 bytes),
   r set before the call (takes $s0).

   Next: a form with retail's one-block tail where the cmove stays apart from the copy to $v0,
   setting `1` before `2`. */

typedef struct {
    unsigned char pad0[0x8E];
    unsigned short count;
    unsigned char pad90[0x50];
} Class_2A68A8;

extern unsigned char D_001A7AF8[] __attribute__((sda));
extern unsigned char D_00139568[];
extern int D_00139688[];
extern Class_2A68A8 D_00239BA0[];
extern int func_002A77E0(int);

int func_002A68A8(int unused, int *out)
{
    int i;
    int j;
    int k;
    int sum = 0;
    int total = 0;
    int pick;
    int r;
    Class_2A68A8 *cls;

    for (i = 0; i < 0x38; i++) {
        if (D_001A7AF8[i] != 0) {
            cls = &D_00239BA0[D_00139568[i]];
            if (cls->count != 0 && i != 0x1F && i != 0x3D && i != 0x2D && i != 0x4D) {
                total++;
                if (D_00139688[i] < cls->count)
                    sum++;
            }
        }
    }
    if (sum != 0) {
        pick = func_002A77E0(sum);
        for (j = 0; j < 0x38; j++) {
            if (D_001A7AF8[j] != 0) {
                cls = &D_00239BA0[D_00139568[j]];
                if (cls->count != 0 && D_00139688[j] < cls->count && j != 0x1F && j != 0x3D) {
                    if (pick == 0) {
                        *out = j;
                        break;
                    }
                    pick--;
                }
            }
        }
        r = func_002A77E0(5) ? 1 : 2;
    } else {
        pick = func_002A77E0(total);
        for (k = 0; k < 0x38; k++) {
            if (D_001A7AF8[k] != 0) {
                cls = &D_00239BA0[D_00139568[k]];
                if (cls->count != 0 && k != 0x1F && k != 0x3D && k != 0x2D && k != 0x4D) {
                    if (pick == 0) {
                        *out = k;
                        break;
                    }
                    pick--;
                }
            }
        }
        r = func_002A77E0(5) ? 1 : 2;
    }
    return r;
}
