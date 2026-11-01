/* GPT-6.1 Sol high, 28 October 2026. USA v1.01: 816/816 bytes, 0/27 places.
 * Profile: -O2 -G0 -ffunction-sections. Requires common.h transfer helpers.
 * Only two instructions differ: +0x214/+0x218 set a0=s3, a1=sp, whereas retail
 * sets a1=sp, a0=s3 before the endpoint displacement scale call.
 * Direct &position expressions with qcopy reproduce the a2-to-fp copy and
 * the saved-register allocation; a separate dot-product statement fixes s0/s1.
 * A float-first declaration for the in-place scale preserves the EE bank orders
 * and fixes its argument scheduling. Float-first/middle/default declarations for
 * the endpoint call, moving hit=1 after it, and i=hit versus i=0 all tie.
 * Stop: tied source forms. Next: a justified endpoint-call expression/lifetime
 * change that reverses only those two argument setup moves.
 */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { int count; int reserved[3]; Vector points[0]; } Path;
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float);
/* The EE keeps integer and FP argument order in independent register banks. */
extern void scale_vector_radius(float, void *, const void *) __asm__("func_00282F20");
extern void func_00282CC0(void *, const void *, const void *);
extern const Vector D_0018A0E0;
extern const Path *D_L00_001FDA80[];
extern float func_00282DB0(const void *, const void *);
extern void func_00282DD8(void *, const void *, const void *);
extern float func_00282C48(float);
extern float func_00282DF0(const void *);

/* Push the point away from the active edges while retaining its plane height. */
int func_L00_003425F8(int pathIndex, const Vector *point, Vector *out, float radius) {
    Vector relative, displacement, position, segment, unit, cross, planePart;
    int hit = 0;
    const Path *path;
    int i;
    float height, side, length, along;
    const Vector *start;
    qcopy(&position, point);
    path = D_L00_001FDA80[pathIndex];
    height = func_00282DB0(&position, &D_0018A0E0);
    for (i = 0; i < path->count - 1; ++i) {
        if (path->points[i].f[3] == 0.0f && path->points[i + 1].f[3] == 0.0f)
            continue;
        start = &path->points[i];
        func_00282CF0(&relative, &position, start);
        func_00282CF0(&segment, &path->points[i + 1], start);
        along = func_00282DB0(&relative, &D_0018A0E0);
        func_00282F20(&planePart, &D_0018A0E0, along);
        func_00282CF0(&relative, &relative, &planePart);
        func_00282F20(&planePart, &D_0018A0E0, func_00282DB0(&segment, &D_0018A0E0));
        func_00282CF0(&segment, &segment, &planePart);
        func_00282F20(&unit, &segment, 1.0f);
        func_00282DD8(&cross, &relative, &unit);
        side = func_00282C48(func_00282DB0(&cross, &D_0018A0E0));
        if (!(side > radius)) {
            length = func_00282DF0(&segment);
            along = func_00282DB0(&relative, &unit);
            if (length < along || along < 0.0f) {
                if (func_00282DF0(&relative) < radius) {
                    hit = 1;
                    func_00282F20(&displacement, &relative, radius);
                    func_00282CC0(&position, &displacement, start);
                }
            } else {
                hit = 1;
                func_00282F20(&planePart, &unit, along);
                func_00282CF0(&displacement, &relative, &planePart);
                scale_vector_radius(radius, &displacement, &displacement);
                func_00282CC0(&displacement, &displacement, &planePart);
                func_00282CC0(&position, &displacement, start);
            }
        }
    }
    if (hit) {
        height -= func_00282DB0(&position, &D_0018A0E0);
        func_00282F20(&segment, &D_0018A0E0, height);
        func_00282CC0(out, &position, &segment);
    }
    return hit;
}
