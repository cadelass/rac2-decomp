/*
 * Tier: sol-high, task v1363. USA v1.01, game EE-GCC, -O2 -G8 -ffunction-sections.
 * Best check.py result: 2148/2156 bytes, 0/27 places; retail 0xF0 frame,
 * all nine saved GPRs and five saved FPRs, no pointer spill.
 * Required declarations are included below; compile in a dedicated -g8.c unit.
 *
 * Corrects three control-flow errors in the earlier sol-low transcription:
 * the line probe at 003A9E68 is inside the age < 7 branch; successful detonation
 * jumps from 003AA2B4 directly to cleanup at 003AA450; states other than 25/70
 * independently satisfy the detonation gate (003AA1A0 branches to 003AA1BC).
 *
 * The particle-loop snapshot uses an ordinary TImode copy, recovering retail's
 * offset load/store and likely-branch load. An explicit pre-loop minimumLifetime
 * recovers the fifth FPR and frame. Remaining differences: FPR allocation,
 * loop constant hoisting (127 rather than 2 in fp), particle-result registers,
 * particle-call address/setup and two div.s hazard nops, and global base setup.
 * Size mismatch still prevents relocation-qualified placement validation.
 *
 * Nineteen checker invocations (including final recheck) and two regalloc diagnostics in this task.
 * Splitting the lifetime arithmetic tied; bank-preserving call interleaving
 * did not change size. All constants declared before the loop gave 2132 bytes;
 * -mno-split-addresses gave 2140; separate vector scopes grew the frame to 0x110.
 * Next: reconstruct the particle-loop expression/lifetimes and actual global
 * record views; do not reintroduce the three control-flow errors above.
 */
#include "common.h"
typedef int Quad9C58 __attribute__((mode(TI)));
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
extern void func_002AFFD8(void *,void *,int);
extern void func_002FEE70(int,void *,int);
extern void func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float),func_00282F20(void *,void *,float);
extern void func_00282D08(void *,void *,void *,float),func_00283028(void *,void *,void *);
extern float func_00282DF0(void *),func_00282DB0(void *,void *);
extern float func_00283CE0(int),func_00283B98(float,float),func_00283198(float),func_00282C48(float);
extern int func_00282978(void *),func_00282948(void *),func_002A77E0(int);
extern void func_L00_0031D670(void *,void *,void *,float);
extern char *func_002BDCE8(void *,int,void *,float,float,unsigned int,float,float,int);
extern int func_002761F8(void *,void *,int,void *,int),func_00277258(void *,int,int,float);
extern int func_002E5CF8(int,int,void *);
extern void func_002E59F8(int),func_L00_00427078(void),func_002FEE50(int),func_0029F338(void *),func_00300190(void *,void *),func_002A9288(void *,float);
extern void func_L00_003A9798(void *,void *,void *,int);
extern void func_0032C700(void *,int,int,int,int,int,int,int,int,int,int,int,float,float);
typedef struct { char pad0[10]; union { short lifetime; unsigned char bytes[2]; } age; } Particle9C58;
typedef struct { char pad0[4]; int type; char pad8[2]; unsigned char alpha,life; } Payload9C58;
extern char D_L00_001A8F20[] __attribute__((sda));
extern char D_L00_001BF220[] __attribute__((sda));
typedef struct { char pad0[0x18]; char *hit; char pad1C[0x14]; float position[4],normal[4]; } Collision9C58;
extern Collision9C58 D_L00_001BF200;
extern char D_L00_001B9000[];
typedef struct {
 char pad0[0x1E0]; short control_state; char pad1E2[0x1230-0x1E2];
 int control_mask; char pad1234[0x1248-0x1234]; int state;
 char pad124C[0x2290-0x124C]; int collision_flags; int weapon;
} Hero9C58;
extern Hero9C58 D_00189E20 __attribute__((sda));
typedef struct {
 char pad0[0x108]; float axis_x,axis_y; char pad110[0x1A0-0x110];
 int held,pressed;
} Pad9C58;
extern Pad9C58 D_00138180 __attribute__((sda));
extern char D_00188660[];
extern int D_L00_001ADB2C __attribute__((sda));
void func_L00_003A9C58(char *m)
{
 float old[4],direction[4],a[4],b[4],c[4];
 char *d=*(char **)(m+0x68),*p,*q;
 int i,n,prior;float scale,speed,t;
 func_002AFFD8(m+0x10,direction,1);
 H(d,0x14)++;
 qcopy(old,m+0x10);
 func_002FEE70(I(d,0x48),d,0);
 scale=0.45f;
 func_00282CC0(m+0x10,m+0x10,d);
 func_00282978(d+0x2C);
 if(H(d,0x2C)) {
 float minimumLifetime=10000.0f;
 int particleType=2;
 for(i=0;i<3;i++) {
   *(Quad9C58 *)b=*(Quad9C58 *)(m+0x10);
   func_L00_0031D670(a,old,b,func_00283CE0(i)*0.3333f);
   n=func_002A77E0(6);if(func_002A77E0(2))n=-n;
   t=func_00283CE0(50);
   { Particle9C58 *particle=(Particle9C58 *)func_002BDCE8(a,n,D_L00_001A8F20,0.025f,1.0f,0x80808080,1.0f,H(d,0x2C)/t*70000.0f+minimumLifetime,1);
   if(particle) {
     Payload9C58 *payload;
     particle->age.lifetime=50;
     payload=(Payload9C58 *)((char *)particle+32);
     payload->type=particleType;payload->alpha=127;payload->life=particle->age.bytes[0];
   } }
 }
 }
 if(H(d,0x14)<7) {scale=func_00283CE0(H(d,0x14));scale/=func_00283CE0(7);scale*=0.45f;
 qcopy(a,m+0x10);
 func_00282D30(b,direction,F(d,0x20));func_00282CF0(c,m+0x10,b);
 if(func_002761F8(a,c,18,m,0))func_00282CC0(m+0x10,D_L00_001BF220,b);
 }
 F(d,0x24)=func_00283B98(F(d,0x24),0.025f);
 func_00282D30(a,direction,F(d,0x28));func_00282CF0(m+0x10,m+0x10,a);
 F(d,0x28)=func_00283198(F(d,0x24))*0.25f;
 func_00282D30(a,direction,F(d,0x28));func_00282CC0(m+0x10,m+0x10,a);
 F(m,0xF0)=func_00283B98(F(m,0xF0),F(d,0x30));
 F(m,0xF4)=func_00283B98(F(m,0xF4),F(d,0x34));
 F(m,0xF8)=func_00283B98(F(m,0xF8),F(d,0x38));
 func_00282948(d+0x44);
 if(func_00277258(m+0x10,0,D_00189E20.collision_flags,scale)) {
   qcopy(m+0x10,D_L00_001BF200.position);
   speed=func_00282DF0(d);scale=speed*0.25f;if(scale<0.033333335f)scale=0.033333335f;
   if(D_L00_001BF200.hit) {
     func_00282CF0(a,m+0x10,D_L00_001BF200.hit+0x10);
     t=func_00282DB0(direction,a);func_00282D30(b,direction,t);
     func_00282CC0(c,D_L00_001BF200.hit+0x10,b);
     func_00282CF0(a,m+0x10,c);func_00283028(d,d,a);
   } else {
     func_00282D30(a,D_L00_001BF200.normal,0.0009765625f);func_00282F20(a,a,1.0f);
     t=func_00282DB0(a,direction);t=func_00282C48(t);if(t>=0.8f)scale=speed;
     func_00283028(d,d,a);
   }
   if(!I(d,0x44)) {func_002E5CF8(2,0,m);I(d,0x44)=15;}
   func_00282F20(d,d,scale);
 }
 func_00282D08(d,d,d+0x50,0.01f);
 p=D_00188660+I(d,0x40)*0x70;
 if(*(char **)(p+0x88)!=m || !B(p,0x74)) I(d,0x40)=func_002E5CF8(0,4,m);
 if(!((D_00138180.pressed&D_00189E20.control_mask) ||
       (!(D_00138180.held&D_00189E20.control_mask) && H(d,0x2E)>20) ||
       ((D_00189E20.state!=25 && D_00189E20.state!=70) || B(m,0x20)==1)))goto steer;
 if(H(d,0x14)>=21) {
   B(m,0x20)=1;prior=H(d,0x16);
   if(func_00282978(d+0x16)) {
     func_002E59F8(I(d,0x40));func_002E5CF8(1,0,m);
     if(!prior)func_0032C700(m+0x10,1,40,20,30,40,50,1,1,1,0,D_L00_001ADB2C,1.5f,20.0f);
     else func_0032C700(m+0x10,1,20,15,30,15,30,1,1,0,0,D_L00_001ADB2C,0.6f,20.0f);
     func_L00_003A9798(m,d,m+0x10,1);goto destroy;
   }
 }
steer:
 if(D_00138180.held&D_00189E20.control_mask) {
   H(d,0x2E)++;
   if(D_00189E20.weapon!=49)D_00189E20.control_state=2;
   func_L00_00427078();
   if(D_00138180.axis_x!=0 || D_00138180.axis_y!=0) {
     speed=func_00282DF0(d);
     if(speed!=0) {
       func_00282D30(a,D_L00_001B9000,-D_00138180.axis_x*0.004166667f);func_00282CC0(d,d,a);
       func_00282D30(a,D_L00_001B9000+16,-D_00138180.axis_y*0.0008333333f);func_00282CC0(d,d,a);
       func_00282F20(d,d,speed);
     }
   }
 }
 if(F(m,0x10)<2 || F(m,0x10)>1021 || F(m,0x14)<2 || F(m,0x14)>1021 || F(m,0x18)<2 || F(m,0x18)>1021) {
destroy:
   func_002FEE50(I(d,0x48));func_0029F338(m);
 } else {func_00300190(m+0x10,m+0x10);func_002A9288(m,0.5f);}
}
