/* func_0034E070: Opus 5.5 xhigh, task v1751. Exact in USA v1.01, not in the other releases.
 * Result: USA v1.01 420/420 bytes, 28 of 28 places. PAL and v2.00: 420/420 bytes, 0 of 28 places.
 * Left to do: the C cannot be one definition. PAL and v2.00 differ from v1.01 only in five field
 * offsets of the record set, all +0x20 past f7A0: 0x220C/0x222C, 0x2210/0x2230, 0x1D30/0x1D50,
 * 0x1D6C/0x1D8C, 0x1FBC/0x1FDC. The catalogues carry the name to those releases, so it needs
 * tools/carry.py --demote (or a release-specific definition) before this body can land in src/.
 * Wording: record holds 0x8710 first because retail keeps that constant and the record pointer in
 * one pseudo ($s0); two variables cost a saved register. The scalar alias of D_001A8CFC is required:
 * the array spelling gives 0 of 28. Profile: -O2 -G0 -ffunction-sections.
 * Declarations are all below; the prototype in 0034CEA0.c is void func_0034E070(void *, void *, void *).
 */
#include "common.h"

extern char *D_001A8CFC_scalar __asm__("D_001A8CFC") __attribute__((sda));
extern char D_001AE710[];
extern char D_001AE720[];

extern int func_00336D50(int, int);
extern void func_00336408(void *, int, int, void *, void *);
extern void func_00336CC8(void *, int);
extern void func_00336B90(void *, int);
extern void func_00336B98(void *, int);
extern void func_00336498(void *, int, int);
extern void func_003364B0(void *, int, int);
extern void func_00336CE0(void *, unsigned int);
extern void func_00336CC0(void *, int);
extern void func_0034B2C8(void *, void *, void *);
extern void func_00336710(void *, void *, void *);
extern int *func_00335E20(void *);
extern void *func_003367B8(void *);
extern void func_00337C10(void *, void *);

typedef struct {
    char records[0x798];
    void *f798;
    char pad79C[4];
    char f7A0[0x1590];
    char f1D30[0x3C];
    char f1D6C[0x250];
    char f1FBC[0x250];
    int f220C;
    int f2210;
} RecordSet;

void func_0034E070(void *object, void *a1, void *a2)
{
    RecordSet *set = object;
    char *record = (char *)0x8710;
    char *end = set->records + 0x750;
    void *colour;

    set->f220C = func_00336D50((int)D_001A8CFC_scalar + (int)record, 0x57);
    set->f2210 = func_00336D50((int)D_001A8CFC_scalar + (int)record, 0x58);
    record = set->records;
    do {
        func_00336408(record, 0x20, 1, D_001AE710, a2);
        func_00336CC8(record, 5);
        func_00336B90(record, 0x64);
        func_00336B98(record, 0);
        func_00336498(record, 0x8049C1FF, 0x80001EFF);
        func_003364B0(record, 0x50F0C070, 0x50F0C070);
        func_00336CE0(record, 0x80000000);
        func_00336CC0(record, 1);
        record += 0x48;
    } while (record < end);
    record = set->f1D30;
    func_0034B2C8(set->f7A0, a1, a2);
    func_00336710(record, D_001AE720, a2);
    colour = func_00335E20(record);
    *(float *)colour = 2155905152.0f;
    colour = func_003367B8(record);
    *(float *)colour = 60008.0f;
    colour = func_003367B8(record);
    *(int *)((char *)colour + 4) = 0;
    set->f798 = a2;
    func_00337C10(set->f1D6C, a2);
    func_00337C10(set->f1FBC, a2);
}
