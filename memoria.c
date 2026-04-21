/* Calculadora 16/4/26 */

#include "memoria.h"

#define fon(A) (memory[RF]|=(A))
#define foff(A) (memory[RF]&=~(A))
#define fget(A) ((memory[RF]&(A))?1:0)
#define freset (memory[RF]=(fget(FSTP))?FSTP:0)

#define vag memory[RA]
#define vbg memory[RB]
#define vas(V) (memory[RA]=(V))


u1 memory[MEMSIZ];

static void flgzero() {
    if(vag) foff(FZER);
    else fon(FZER);
}

static void flgcrr() {
    if(vag & 1) fon(FCRR);
    else foff(FCRR);
}

static void flgcrl() {
    if(vag & 128) fon(FCRL);
    else foff(FCRL);
}

void lrv(u1 r,u1 v) {
    if(r>=RA && r<=RJ) {
        if(r==RA) freset;
        memory[r]=v;
        flgzero();
    }
}

void lpr() {
    memory[memory[RI]]=memory[RA];
}

void lrp() {
    freset;
    memory[RA]=memory[memory[RI]];
    flgzero();
}

static u1 gorg(u1 dst) {
    switch(dst) {
        case RA:
            return RB;
        case RI:
            return RJ;
        case RJ:
            return RI;
        default:
            return RA;
    }
}

void mov(u1 d) {
    freset;
    u1 org=gorg(d);
    u1 dst=d;
    u1 v=memory[dst]=memory[org];
    flgzero();
    if(dst==RA) {
        if(v==0) fon(FZER);
    }
}

void swp(u1 d) {
    freset;
    u1 org=gorg(d);
    u1 dst=d;
    u1 v=memory[org];
    memory[org]=memory[dst];
    memory[dst]=v;
    flgzero();
}

void and() {
    freset;
    vas(vag & vbg);
    flgzero();
}

void or() {
    freset;
    vas(vag | vbg);
    flgzero();
}

void xor() {
    freset;
    vas(vag ^ vbg);
    flgzero();
}

void not() {
    freset;
    vas(~vag);
    flgzero();
}

void rcr() {
    freset;
    flgcrr(); 
    vas(vag>>1);
    flgzero();
}

void lcr() {
    freset;
    flgcrl();
    vas(vag<<1);
    flgzero();
}

void inc() {
    freset;
    vas(vag+1);
    if(vag==0) fon(FZER|FCRL);
}

void dec() {
    freset;
    vas(vag-1);
    if(vag==255) {
        fon(FNEG);
        vas(1);
    }
    flgzero();
}

void jmp(u1 v) {
    if(v>=RAM && v<RAM+RAMD) {
        memory[LP]=v;
        fon(FJAD);
    }
}

void ifj(u1 f,u1 v) {
    if(fget(f)) jmp(v);
}

void ifn(u1 f,u1 v) {
    if(fget(f)==0) jmp(v);
}

void stp() {
    fon(FSTP);
}

static void outval(u1 val) {
     u1* ptr=memory+VRAM+VRAMD-1;
    while(ptr!=memory+VRAM) {
        *(ptr)=*(ptr-1);
        ptr--;
    }
    *(memory+VRAM)=val;
}
    
#include <stdio.h> //dbg

void out(u1 chr) {
    if(chr) {
        outval(vag);
        fon(FOUT);
    } else {
        u1 val=vag;
        u1 cif[]={0,0,0};
        u1* pc=cif;
        u1 div=100;
        while(val) {
            *pc=val/div;
            val=(val-(*pc)*div);
            div=div/10;
            pc++;
        }
        pc=cif+2;
        while(pc>=cif) {
            outval(*pc+'0');
            pc--;
        }
        char s=fget(FNEG)?'-':'+';
        outval(s);
        fon(FOUT);
    }
}

void clr() {
    u1* ptr=memory+VRAM;
    while(ptr!=memory+VRAM+VRAMD) *ptr++=0;
    fon(FOUT);
}

#include <stdio.h>

void fls() {
    if(fget(FOUT)) {
        printf(">");
        u1* ptr=memory+VRAM;
        while(ptr!=memory+VRAM+VRAMD) {
            if(*ptr!=0) printf("%c",*ptr);
            ptr++;
        }
        printf("\n");
        foff(FOUT);
    }
}

#define iscif(A) ((A)>='0' && (A)<='9')

void inp(u1 chr) {
    fls();
    printf("<");
    char c=getchar();
    u1 val=0;
    if(chr) val=c;
    else if((c=='+' || c=='-' || iscif(c))) {
        u1 fact=100;
        if(c=='-') fon(FNEG);
        else foff(FNEG);
        if(iscif(c)) {
            val=fact*(c-'0');
            fact=fact/10;
        }
        while(fact) {
            c=getchar();
            val+=fact*(c-'0');
            fact=fact/10;
        }
    }
    vas(val);
}

void memini() {
    u1* ptr=memory;
    while(ptr!=memory+MEMSIZ) *ptr++=0;
    memory[LP]=RAM;
}

void memprt() {
    u1* ptr=memory;
    while(ptr!=memory+MEMSIZ) {
        printf("%03i  ",*ptr++);
        if(ptr-memory!=0 && (ptr-memory)%8==0) puts("");
    }
    puts("");
}



