/* GPT-6.1 Sol high worker, 29 October 2026, pinned upstream game compiler.
   -O2 -G8 -ffunction-sections. 2012/2012 bytes, 0/2 USA v1.01 places;
   final check first differs at +0x2C. Typed resident fields recover the retail
   s0 low base and s5 high half, improving the earlier raw-pointer reconstruction.
   The candidate still saves fp: the high half of D_L22_0025DCE0 is hoisted
   across the object loop into s6, pushing its constant 22 into fp. Retail
   rematerializes the table high half and keeps 22 in s6. Register-allocation
   dumps verify this extra lifetime. Other differences include the counter-store
   delay slot, history remainder allocation, mode-call block layout, and copy
   operand registers. Separating loop variables and marking the timer table sda
   did not remove the hoist; a do/while and explicit history indices made it
   smaller without matching. Next: independently scoped table address lifetime
   and fully typed vectors/objects. Corrected the threshold literal to the
   measured 0x3ADA740F; 0.0016666667f was one ULP too small.
   All declarations and shared qcopy dependencies are included below.
   Not linked or counted. */

#include "common.h"
typedef struct {
 char pad0[136];
 float f88;
 char pad8c[228];
 float f170;
 char pad174[16];
 float f184;
 char pad188[48];
 int f1b8;
 int f1bc;
 int f1c0;
 int f1c4;
 int f1c8;
 int f1cc;
 char pad1d0[8];
 int f1d8;
 char pad1dc[12];
 int f1e8;
 char pad1ec[22];
 short f202;
 char pad204[8];
 short f20c;
 char pad20e[14];
 short f21c;
 char pad21e[6];
 short f224;
 char pad226[2];
 short f228;
 short f22a;
 char pad22c[240];
 float f31c;
 char pad320[32];
 int f340;
 char pad344[10];
 short f34e;
 char pad350[624];
 int f5c0;
 char pad5c4[3204];
 int f1248;
 char pad124c[520];
 short f1454;
 char pad1456[3654];
 int f229c;
 char pad22a0[20];
 unsigned char f22b4;
 char pad22b5[3];
 unsigned char f22b8;
 char pad22b9[4];
 unsigned char f22bd;
 char pad22be[5];
 unsigned char f22c3;
 char pad22c4[256];
 int f23c4;
 int f23c8;
 char pad23cc[216];
 float f24a4;
 float f24a8;
 char pad24ac[48];
 float f24dc;
} UpdateState;
extern UpdateState D_00189E20;
extern char D_00138180[];
extern int D_L22_001A8F00[] __attribute__((sda));
extern float D_L22_001B1B60[] __attribute__((sda));
extern float D_L22_001B1B64;
extern int D_L22_001B1C48;
extern unsigned char D_001A7AFF[] __attribute__((sda));
extern char *D_L22_001FBBA0[];
extern char D_L22_0025DCE0[];
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
#define G (&D_00189E20)
void func_L22_002C8610(void) {

 float v[4], delta[4];
 int i;
 char **list;
 char *object;
 if (!G->f22bd) func_L00_002B9380();
 G->f1b8++; G->f1bc++; G->f1c0++; G->f1c4++;
 func_00282978((char *)G+0x1E0);
 func_00282978((char *)G+0x1DC);
 func_00282978((char *)G+0x1D2);
 func_00282978((char *)G+0x1E4);
 func_00282978((char *)G+0x1F8);
 func_00282978((char *)G+0x1FE);
 func_00282948((char *)G+0x1D4);
 func_00282978((char *)G+0x210);
 func_00282978((char *)G+0x1D0);
 func_00282978((char *)G+0x1F4);
 func_00282978((char *)G+0x1F6);
 func_00282978((char *)G+0x204);
 func_00282978((char *)G+0x206);
 func_00282978((char *)G+0x1F0);
 func_00282978((char *)G+0x1EC);
 func_00282978((char *)G+0x1EE);
 func_00282978((char *)G+0x208);
 func_00282978((char *)G+0x200);
 func_00282978((char *)G+0x20E);
 func_00282978((char *)G+0x20A);
 func_00282978((char *)G+0x214);
 func_00282978((char *)G+0x212);
 func_00282978((char *)G+0x1FC);
 func_00282978((char *)G+0x216);
 func_00282978((char *)G+0x1FA);
 func_00282978((char *)G+0x218);
 func_00282978((char *)G+0x1F2);
 func_00282978((char *)G+0x21A);
 func_00282978((char *)G+0x21C);
 func_00282978((char *)G+0x1DE);
 func_00282978((char *)G+0x1E6);
 func_00282978((char *)G+0x222);
 func_00282978((char *)G+0x224);
 func_00282978((char *)G+0x226);
 if (!(*(int *)(D_00138180+0x1A0)&4)) G->f20c=0;
 if (G->f21c) func_L00_002A7A10();
 if (G->f22b8) G->f1d8++; else G->f1d8=0;
 if (*(int *)(D_00138180+0x1D4)) { G->f1c8=0; G->f1cc++; }
 else { G->f1cc=0; G->f1c8++; }
 if (G->f22c3 && !G->f229c && G->f340 && G->f170<0.0016666668234393f && G->f184<0.0016666668234393f)
  qcopy((char *)G+0x80,(char *)G+0x2030);
 if (G->f1454) G->f1e8=0; else G->f1e8++;
 if (!D_L22_001A8F00[0]) {
  if (D_L22_001B1B60[0]>0) G->f22a++; else G->f22a=0;
  if (G->f22a>120) { D_L22_001B1B60[0]=0; G->f22a=0; }
  if (D_L22_001B1B64>0) G->f228++; else G->f228=0;
  if (G->f228>120) { G->f228=0; D_L22_001B1B64=0; }
 }
 if (G->f224) {
  UpdateState *hero = G;
  for (list=D_L22_001FBBA0; (object=*list)!=0; list++) {
   if (func_002ABB78(object) || (object && *(char **)(object+0x24) && *(short *)(*(char **)(object+0x24)+0x46)==22)) {
    if ((D_L22_001B1C48&7)==(((int)object>>8)&7) || !func_002A77E0(4)) {
     if (func_00282E48((char *)G+0x80,object+0x10)<15.37f) {
      func_00282CF0(v,object+0x10,(char *)G+0x80);
      func_00282F20(v,v,1.7f);
      func_002A8F70(object,*(void **)((char *)hero+0x2290),0x4000000,(char *)G+0x80,v,1.0f);
     }
    }
   }
  }
 }
 for (object=D_L22_0025DCE0; (int)object<(int)(D_L22_0025DCE0+0x1C0); object+=0x70) func_00282948(object);
 G->f24dc=9999.0f;
 if (G->f34e && func_L00_002D3B00((char *)G+0xF0)<0 && G->f23c8==32) {
  func_00282C88(v);
  for (i=0;i<8;i++) {
   func_00282CF0(delta,(char *)G+0x1D90+((G->f23c4-i+31)%32)*16,(char *)G+0x1D90+((G->f23c4-i+30)%32)*16);
   func_00282CC0(v,v,delta);
  }
  func_00282D30(v,v,1.0f/(float)i);
  if (func_00282DF0(v)<0.016666668f) G->f202++; else G->f202=0;
 } else G->f202=0;
 func_L00_002C3838();
 switch (G->f22b4) {
 case 1: func_L00_002D36E0((char *)G+0xE0,1,0,0,0.4f); break;
 case 2: func_L00_002D36E0((char *)G+0xE0,1,0,0,4); break;
 default: func_L00_002D36E0((char *)G+0xE0,1,0,0,0.7f); break;
 }
 if (!(D_L22_001B1C48&3)) {
  switch (G->f22b4) {
  case 1: G->f24a4=2.125f; G->f24a8=1.25f; break;
  case 2: G->f24a4=15; G->f24a8=3; break;
  }
 } else if (D_001A7AFF[0]) { G->f24a4=14; G->f24a8=4.5f; }
 else { G->f24a4=4.25f; G->f24a8=2.25f; }
 if (G->f31c<4) { qcopy((char *)G+0xD0,(char *)G+0x2D0); func_L00_002D3778((char *)G+0xD0,(char *)G+0xD0,0.5f); }
 else qcopy((char *)G+0xD0,(char *)G+0xE0);
 if (*(char **)((char *)G+0x5C0)) {
  char *p=*(char **)((char *)G+0x5C0);
  if (!(*(unsigned short *)(p+0x34)&0x1000) || p==*(char **)((char *)G+0x33C)) G->f5c0=0;
  if (G->f5c0 && G->f1248!=0x2E) G->f5c0=0;
 }
 if (G->f88<1) func_L00_002B30E8();
}
#undef G
