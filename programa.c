/* Calculadora 17/4/26 */

#include "programa.h"

#define nxt (memory[LP]+=1) /* incrementa en uno la direccion de la lectura */
#define lin memory[memory[LP]] /* se obtiene la instruccion de la ram */

static void lectura() {
    /* esta instruccion lee la instruccion marcada por LP */
    u1 val=lin;
    u1 ins=val%16;
    u1 cmp=val/16;
    if(ins==STP) stp();
    else if(ins==LRV) {
        nxt;
        lrv(cmp,lin);
    } else if(ins==LRP) lrp();
    else if(ins==LPR) lpr();
    else if(ins==MOV) mov(cmp);
    else if(ins==SWP) swp(cmp);
    else if(ins==OPR) {
        if(cmp==AND) and();
        else if(cmp==OR) or();
        else if(cmp==XOR) xor();
        else if(cmp==NOT) not();
        else if(cmp==RGT) rcr();
        else if(cmp==LFT) lcr();
        else if(cmp==INC) inc();
        else if(cmp==DEC) dec();
    } else if(ins==IO) {
        u1 chr=cmp/4;
        cmp=cmp%4;
        if(cmp==OUT) out(chr);
        else if(cmp==IN) inp(chr);
        else if(cmp==CLR) clr();
    } else if(ins==JMP) {
        nxt;
        jmp(lin);
    } else if(ins==IF) {
        nxt;
        ifj(cmp,lin);
    } else if(ins==IFN) {
        nxt;
        ifn(cmp,lin);
    }
    if(memory[RF] & FJAD) {
        memory[RF] &= ~FJAD;
    } else {
        nxt;
    }
}

#undef nxt
#undef lin

#define isstp ((memory[RF] & FSTP)!=0)

static void scrout() {
    /* rige la pantalla. Se actualiza cada unidad de tiempo dada por la cte */
    static u1 timer=0;
    if(timer==TRP || isstp) {
        fls();
        timer=0;
    } else ++timer;
}
       
static void run() {
    /* se encarga de ejecutar el programa y de mostrar la pantalla */
    while(!isstp) {
        lectura();
        scrout();
    }
    scrout();
}

#undef isstp

static void read(u1 sop,u1* prg) {
    /* lee el programa y lo almacena en la ram*/
    u1* o=prg;
    u1* d=memory+RAM;
    while(o!=prg+sop && d!=memory+RAM+RAMD-1) {
        *d++=*o++;
    }
}

void program(u1* p) {
    memini();
    if(p) {
        read(*p,p+1);
        memprt();
        run();
    }
}
    
/* prueba */

int main() {
    u1 pr[]={15,23,20,23,9,30,118,5,102,5,8,22,7,5,7,0};
    program(pr);
}
