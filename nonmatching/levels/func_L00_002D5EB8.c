/* GPT-6.1 Sol high worker, USA v1.01, 29 October 2026.
 * Game profile: -O2 -G8 -ffunction-sections -frac2-gcse-unsplit-edges
 * -frac2-keep-block-order. check.py: 1296/1376 bytes, 0/27 places.
 * No linked build run. Separate explicit boolean labels recover branches
 * instead of movn around the two ID switches, but add unconditional jumps.
 * Remaining: boolean-register assignment, global address selection, and final
 * loop rotation / constant hoisting (retail saves through fp, this saves s5).
 * Block-local results reduce to 1272 bytes with better inner branch shape;
 * final for/do/infinite-loop rewrites did not recover the retail loop layout.
 * D_0018C958 has measured absolute addressing, hence its section declaration.
 * All required declarations are below.
 */
#include "include_asm.h"
extern int D_L00_001B19C8;
extern int D_0018C350, D_0018C34C, D_001A7A00, D_0018C2EC;
extern unsigned char D_001A7A28[], D_00139568[];
extern int D_L00_001A903C;
extern unsigned short D_0018C958 __attribute__((section(".data")));
extern int D_00139868[], D_001A7398[];
extern unsigned char D_001A7AF8[], D_001A7A7A;
extern char D_00189E20[];
typedef struct { int exists; unsigned char state; char pad[7]; int index; char pad2[58]; short value; char pad3[32]; int limit; char pad4[112]; } Entry1269;
extern Entry1269 D_L00_00262570[];
extern void func_L00_002D5E30(int*,int*,int*);
extern void func_0028A180(int,int), func_L00_003F1300(void), func_L00_0030C7F8(int), func_002B0A18(int,int), func_002E5E58(int,int,int);
extern int func_00288D58(void), func_00287F60(int);
extern void func_L00_0037E6A8(int,int), func_00287EB0(int), func_00288508(int);
extern int ref_L00_002D5EB8_00 __attribute__((sda));
void func_L00_002D5EB8(void) {
 int count, i, j, ok, selected;
 Entry1269 *e;
 if ((D_L00_001B19C8&15)==1 && D_L00_001B19C8!=1) return;
 count=4;
 func_L00_002D5E30(&D_0018C350,(int*)((char*)&D_0018C350-4),&count);
 for(j=0;j<10;j++) if(D_001A7A28[j]) count++;
 if (D_001A7A00!=count) {
  if (ref_L00_002D5EB8_00>=11 && D_001A7A00<count) {
   if (!D_0018C958) func_0028A180(0x9a9,0);
   func_L00_003F1300(); func_L00_0030C7F8(0x168); func_002B0A18(0x1235,-1); func_002E5E58(6,0,0);
  }
  D_0018C2EC=count; D_001A7A00=count;
 }
 for(i=0;i<56;i++) {
  if (D_L00_00262570[D_00139568[i]].state) {
   if (!func_00288D58()) continue;
   if (func_00287F60(i)==1) continue;
  }
  e=&D_L00_00262570[D_00139568[i]];
  selected = 0;
  if (e->exists) selected = e->state == 3;
  if (selected) continue;
  if(func_00287F60(i)<=0) continue;
  e=&D_L00_00262570[D_00139568[i]];
  if((D_00139868[i]>>5)<e->limit || e->limit<=0) continue;
  if(i==31 || i==9 || i==45) { func_L00_0037E6A8(i,e->value); continue; }
  if(*(int*)(D_00189E20+0x1248)==i) {
   if(!*(int*)(D_00189E20+0x340)) continue;
   if(D_001A7398[e->index]!=i) continue;
   func_L00_0037E6A8(i,e->value); continue;
  }
  if(func_00288D58()) {
   e=&D_L00_00262570[D_00139568[i]];
   if(!e->exists) continue;
   if(e->state<2) {
    if(e->state==1) {
     int valid=0;
     switch(i) {case 12:case 14:case 17:case 18:case 53:valid=1;break;}
     if(valid) goto available_yes;
     goto available_no;
    } else goto available_no;
   } else goto available_yes;
available_no:
   selected=0;
   goto available_done;
available_yes:
   selected=1;
available_done:
   if(selected) {
    if(D_L00_00262570[D_00139568[i]].exists) {
     j=func_00287F60(i);
     if(j<2) {
      if(j==1) {
       int valid=0;
       switch(i) {case 12:case 14:case 17:case 18:case 53:valid=1;break;}
       if(valid) goto owned_yes;
       goto owned_no;
      } else goto owned_no;
     } else goto owned_yes;
    } else goto owned_no;
owned_no:
    selected=0;
    goto owned_done;
owned_yes:
    selected=1;
owned_done:
    if(selected) { func_00287EB0(i); func_00288508(i); }
   }
  } else { func_00287EB0(i); func_00288508(i); }
 }
 if((D_L00_001B19C8&127) || D_001A7A7A) return;
 ok=1;
 for(i=0;i<56;i++) {
  if(D_L00_00262570[D_00139568[i]].exists) {
   if(i==10) goto next;
   if(i==9) goto next;
   if(!D_001A7AF8[i]) {ok=0; break;}
   if(i==14) goto next;
   if(i==12) goto next;
   if(i==17) goto next;
   if(i==18) goto next;
   if(i==53) goto next;
   if(func_00287F60(i)<=0) continue;
   if(!D_L00_00262570[D_00139568[i]].state) {ok=0; break;}
  }
next:;
 }
 if(ok && !D_001A7A7A) {
  D_001A7A7A=1; func_002E5E58(1,0,0); func_002B0A18(0x1233,-1); D_L00_001A903C=1;
 }
}
