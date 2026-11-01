/* GPT-6.1 Sol high, task v1058, USA v1.01: 1340/1340 bytes, 0/27 places.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier -fno-gcse.
 * The 0xD0 frame, mode register, loop countdown and FP register allocation now
 * agree. Initial address/save scheduling, camera full-address retention versus
 * retail's shared high half, and particle-call float/global-load scheduling differ.
 * Explicit direction-pointer lifetime plus -fno-gcse removes the extra up-pointer
 * invariant that otherwise spills mode and grows the frame to 0xE0. Keeping the
 * camera pointer gives the retail size; defining it after the first call adds
 * instructions. Array/union spelling, -fno-strength-reduce, -fno-rerun-loop-opt,
 * and -fno-expensive-optimizations did not remove that invariant by themselves.
 * Keep .245f literal; the two other paired coefficients need the products below
 * to reproduce retail's rounding. Declarations needed by this draft follow.
 * Not a linked match; the INCLUDE_ASM marker is restored.
 */
#include "common.h"
typedef unsigned int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } V;
extern char D_L00_001B8C80[], D_00189ED0[];
extern int D_L00_001A8FF0;
extern float D_L00_001B1358 __attribute__((sda));
extern float D_L00_001B135C __attribute__((sda));
extern float D_L00_001B1344 __attribute__((sda));
extern float D_L00_001B1348 __attribute__((sda));
extern float D_L00_001B134C __attribute__((sda));
extern float D_L00_001B1350 __attribute__((sda));
extern float D_L00_001B1354 __attribute__((sda));
extern void func_00282CF0(void *,void *,void *),func_00282CC0(void *,void *,void *);
extern void func_00282F20(void *,void *,float),func_00282D30(void *,void *,float);
extern float func_00282DB0(void *,void *),func_002A7878(float,float),func_002A78D8(float,float);
extern int func_002A77E0(int),func_001163B0(void),func_00283CF0(float);
extern void func_002ACEC0(float,void *,void *,void *);
extern char *func_002C2210(void *,int,float,float,float,int,int,int,void *,int);
void func_L00_00412928(void *position,int count,int mode)
{
    V velocity, spawn, direction, up, temp;
    float size,speed;
    int sign,i;
    char *particle;
    V *directionPtr;
    char *camera=D_L00_001B8C80+0x140;
    func_00282CF0(&direction,camera,position);
    directionPtr=&direction;
    if (D_L00_001A8FF0 == 0) {
        direction.f[2]=0;
        up.f[0]=0; up.f[1]=0; up.f[2]=1; up.f[3]=1;
    } else {
        func_00282CF0(&temp,position,D_00189ED0);
        func_00282F20(&up,&temp,1);
        func_00282D30(&temp,&up,func_00282DB0(&up,directionPtr));
        func_00282CF0(directionPtr,directionPtr,&temp);
    }
    if (count > 0) { i=count; do {
        size=func_002A7878(D_L00_001B1358,D_L00_001B135C);
        sign=func_002A77E0(2); if (!sign) --sign;
        func_002ACEC0(func_002A7878(-1.0471977f,1.0471977f),&velocity,directionPtr,&up);
        speed=func_002A7878(D_L00_001B1344,D_L00_001B1348)*0.016666668f;
        func_00282F20(&velocity,&velocity,speed);
        velocity.f[2]=func_002A7878(D_L00_001B134C,D_L00_001B1350)*0.016666668f;
        qcopy(&spawn,position);
        spawn.f[0]+=func_002A78D8(0,.15f);
        spawn.f[1]+=func_002A78D8(0,.15f);
        spawn.f[2]+=func_002A78D8(0,.15f);
        if(!mode) {
            if(!(func_001163B0()&1)) {
                func_00282D30(&velocity,&velocity,1.5f);
                particle=func_002C2210(&spawn,60,size*.35f,size,D_L00_001B1354,0x7f800000,0,sign,&velocity,0);
                if(particle) particle[9]=func_00283CF0(4)+112;
                particle=func_002C2210(&spawn,60,size*.245f,size*.7f,D_L00_001B1354,0x7f7f7f7f,1,-sign,&velocity,0);
                if(particle) particle[9]=func_00283CF0(4)+112;
            } else {
                func_00282CF0(&temp,camera,&spawn);
                func_00282F20(&temp,&temp,speed);
                func_00282CC0(&velocity,&velocity,&temp);
                particle=func_002C2210(&spawn,40,size*2.05f,size,D_L00_001B1354,0x7f800000,0,sign,&velocity,0);
                if(particle) particle[9]=func_00283CF0(4)+112;
                particle=func_002C2210(&spawn,40,size*(2.05f*.7f),size*.7f,D_L00_001B1354,0x7f7f7f7f,1,-sign,&velocity,0);
                if(particle) particle[9]=func_00283CF0(4)+112;
            }
        } else {
            if(!(func_001163B0()&1)) {
                func_00282D30(&velocity,&velocity,1.5f);
                particle=func_002C2210(&spawn,60,size*.3f,size,D_L00_001B1354,0x7f800000,0,sign,&velocity,0);
                if(particle) particle[9]=func_00283CF0(4)+112;
                particle=func_002C2210(&spawn,60,size*(.3f*.7f),size*.7f,D_L00_001B1354,0x7f7f7f7f,1,-sign,&velocity,0);
                if(particle) particle[9]=func_00283CF0(4)+112;
            } else {
                func_00282CF0(&temp,camera,&spawn);
                func_00282F20(&temp,&temp,speed);
                func_00282CC0(&velocity,&velocity,&temp);
                particle=func_002C2210(&spawn,40,size*.25f,size,D_L00_001B1354,0x7f800000,0,sign,&velocity,0);
                if(particle) particle[9]=func_00283CF0(4)+112;
                particle=func_002C2210(&spawn,40,size*(.25f*.7f),size*.7f,D_L00_001B1354,0x7f7f7f7f,1,-sign,&velocity,0);
                if(particle) particle[9]=func_00283CF0(4)+112;
            }
        }
        } while (--i);
    }
}
