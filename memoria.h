/* Calculadora 16/4/26 */


#define MEMSIZ 256

#define RA 0 /* acumulador */
#define RB 1 /* segundo operador */
#define RI 2 /* direccion */
#define RJ 3 /* segunda direccion */
#define RF 4 /* banderas */
#define LP 5 /* linea de programa */
#define VRAM 6 /* comienzo de la ram visual */
#define VRAMD 12 /* dimension en bytes de la ram visual */
#define RAM (VRAM+VRAMD) /* inicio de la ram donde reside el programa */
#define RAMD (MEMSIZ-RAM)/* dimension de la ram */

#define FZER 1 /* bandera que dice si el acumulador A es 0 */
#define FNEG 2 /* bandera que dice si el acumulador A es negativo */
#define FCRR 4 /* bandera de acarreo a la derecha */
#define FCRL 8 /* bandera de acarreo a la izquierda */
#define FSTP 16 /* bandera de stop de ejecucion de programa */
#define FJAD 32 /* bandera que avisa de que el salto de memoria ya se ha realizado */
#define FOUT 64 /* avisa si dentro del out hay algo */

typedef unsigned char u1;

extern u1 memory[MEMSIZ];

void lrv(u1 r,u1 v);
/* se carga directamente uno de los registros con un valor (A,B,I,J)*/

void lpr();
/* carga el la direccion apuntada en el registro I con el valor del registro A */

void lrp();
/* carga el registro A con el valor de la direccion apuntada por I */

void mov(u1 d);
/* mueve registro de A a B, de I a J, se introduce el destino */

void swp(u1 d);
/* idem al move, pero intercambiando valores */

/* todas las operaciones mueven las banderas */

void and();
/* A = and(A,B) */

void or();
/* A = or(A,B) */

void xor();
/* A = xor(A,B) */

void not();
/* A = not(A) */

void rcr();
/* A accareo a la derecha */

void lcr();
/* A acarreo izquierda */

void inc();
/* A incrementado */

void dec();
/* A decrementado */

/* flujo del programa */
/* todos los saltos de memoria relativos al inicio de la ram */

void jmp(u1 v);
/* salto a la direccion de memoria especificada (modifica LP) */

void ifj(u1 f,u1 v);
/* salto a una posicion de memoria si la bandera esta conectada */

void ifn(u1 f,u1 v);
/* salto a la posicion de memoria si la bandera no esta conectada */

void stp();
/* se conecta la bandera stop, corresponde a la instruccion 0 */

/* input/output */

void out(u1 chr);
/* se copia el registro en la posicion mas baja del video, si es como caracter directamente el valor, si no en tres numeros */

void clr();
/* se ponen a 0 todas las posiciones del video */

void fls();
/* se representa en la pantalla los valores (0 no representa nada) */

void inp(u1 chr);
/* se coge un valor y se introduce en el registro, si es como caracter guarda solo un valor, si no guarda todo el numero  */

/* inicio de la memoria */

void memini();
/* pone toda la memoria a 0 excepto LP que coge la primera direccion de la ram */

/* impresion de memoria */

void memprt();
/* imprime todo el mapa de memoria */





