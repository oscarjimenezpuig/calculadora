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

/* ordenes
 * stp = 0 STOP
 * loA = 1 load A con un valor
 * loB = 17 load B con un valor
 * loI = 33 load I con un valor
 * loJ = 49 load J con un valor
 * loA(I) = 2 load A con valor de direccion apuntada por I
 * lo(I)A = 3 load la direccion apuntada por I con el valor de A
 * movA = 4 mueve el registro B en el A
 * movB = 20 mueve el registro A en el B
 * movI = 36 mueve el registro J en el I
 * movJ = 52 mueve el registro I en el J
 * swpA = 5 intercambia A y B
 * swpI = 37 intercambia I y J
 * OPERACIONES (entre A y B)
 * and = 6 
 * or = 22
 * xor = 38
 * not = 54
 * rgt = 70
 * lft = 86
 * inc = 102
 * dec = 118
 * SALIDA Y ENTRADA EN PANTALLA
 * outval = 7
 * outchr = 71
 * inval = 23
 * inchr = 87
 * clr = 39
 * SALTOS Y SALTOS CONDICIONALES (con las banderas)
 * jmp = 8
 * ifzer = 25
 * ifneg = 41
 * ifcrr = 57
 * ifcrl = 73
 * ifnzer = 26 
 * ifnneg = 42
 * ifncrr = 58
 * ifncrl = 74
*/



void program(u1* prg);
/* lectura del programa, el primer dato es la longitud en bits de este */

