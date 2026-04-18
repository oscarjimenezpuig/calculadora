/* Calculadora 17/4/26 */

#include "memoria.h"

/* los cuatro bits significativos se dedican a instrucciones, los cuatro segundos a registros o banderas */

/* instrucciones (cuatro primeros bits) */
#define STP 0
#define LRV 1
#define LRP 2
#define LPR 3
#define MOV 4
#define SWP 5
#define OPR 6 /* indicativo de las operaciones */
#define IO 7 /* ordenes de inout */
#define JMP 8
#define IF 9
#define IFN 10

/* varios (cuatro segundos bits) */
#define FC 32

/* registros */
#define PRA (RA)
#define PRB (RB)
#define PRI (RI)
#define PRJ (RJ)

/* banderas */
#define FZE (FZER)
#define FNE (FNEG)
#define FCR (FCRR)
#define FCL (FCRL)

/* operaciones */
#define AND 0
#define OR 1
#define XOR 2
#define NOT 3
#define RGT 4
#define LFT 5
#define INC 6
#define DEC 7

/* inout */
#define OUT 0
#define IN 1
#define CLR 2

/* complemento input */
#define NCHR 0 /* se entra un numero */
#define ICHR 1 /* se entra un caracter */

/* regir pantalla */

#define TRP 5 /* tiempo de refresco de la pantalla */

void program(u1* prg);
/* lectura del programa, el primer dato es la longitud en bits de este */

