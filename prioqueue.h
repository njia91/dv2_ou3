//Written by Lena Kallin Westin <kallin@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) and DV2: Algoritmer och
// probleml�sning at Ume� University.
//Usage exept those listed above requires permission by the author.

#include "list_2cell.h"

/*
Datatypen Priok� enligt definitionen p� sidan 293 i Lars-Erik Janlert,
Torbj�rn Wiberg Datatyper och algoritmer 2., [rev.] uppl.,Lund,
Studentlitteratur, 2000, x, 387 s. ISBN 91-44-01364-7

Implementerar priok� med hj�lp av en datatypen lista

Som standard s� �r anv�ndaren av datatypen ansvarig f�r att avallokera
minnet f�r datav�rdena. Genom att anropa pqueue_setMemHandler och till denna
skicka med en funktion f�r att avallokera ett dataobjekt s� kommer k�n
ta �ver ansvaret f�r minneshanteringen och automatiskt avallokera v�rdena
d� de tas bort fr�n k�n. OBS i detta fall s� m�ste anv�ndaren kopiera
v�rdena om de ska finnas kvar efter att ha tagits bort fr�n k�n.
*/

#ifndef __PRIOQUEUE_H
#define __PRIOQUEUE_H
#include <stdlib.h>
typedef void *VALUE;

/* Type for function comparing two data (see create for details)*/
typedef int CompareFunction(VALUE,VALUE);


#ifndef __MEMFREEDATAFUNC
#define __MEMFREEDATAFUNC
typedef void memFreeFunc(VALUE);
#endif
typedef struct MyPQ {
	list *pq;
	CompareFunction *cf;
} MyPQ;

typedef MyPQ pqueue;

/*
Syfte: Skapa en ny priok�
Parametrar: compare_function - Pointer to a function that is called for comparing
                     two priorities. The function should return 0 if the left
                     parameter has lower priority than the right parameter and >0
                     otherwize
Returv�rde: Den nyskapade priok� (pqueue *)
Kommentarer: D� man anv�nt priok�n f�rdigt s� m�ste minnet f�r priok�n
             avallokeras via funktionen pqueue_free
*/
pqueue *pqueue_empty(CompareFunction *compare_function);

/*
Syfte: Installera en minneshanterare f�r priok�n s� att den kan ta �ver
       ansvaret f�r att avallokera minnet f�r v�rdena d� de ej finns kvar
       i priok�n mer.
Parametrar: q - priok�n (pqueue *)
            f - en funktionspekare till en funktion som tar in ett v�rde
                av typen data (void pekare) och avallokerar minnet f�r v�rdet
                den pekar p� (ett av den typ av v�rden som lagras i priok�n).
Kommentarer: B�r anropas direkt efter att priok�n skapats om funktionaliteten
             ska anv�ndas. priok�n funkar �ven utan att denna funktion anropas,
             men det �r d� upp till anv�ndaren av datatypen att avallokera allt
             minne f�r datat som lagras i priok�n.
*/
void pqueue_setMemHandler(pqueue *q, memFreeFunc *f);

/*
Syfte: Ta bort f�rsta v�rdet i priok�n
Parametrar: q - priok�n (pqueue *)
Kommentarer: odefinierad f�r en tom priok�
*/
void pqueue_delete_first(pqueue *q);

/*
Syfte: H�mtar f�rsta v�rdet i priok�n
Parametrar: q - priok�n (pqueue *)
Returv�rde: v�rdet som fanns l�ngst ram i priok�n
Kommentarer: ej definierad f�r tom priok�.
*/
data pqueue_inspect_first(pqueue *q);

/*
Syfte: L�gga till ett v�rde p� r�tt st�lle utifr�n sin prioritet i priok�n
Parametrar: q - priok�n (pqueue *)
            d- v�rdet som ska l�ggas till (data)
Kommentarer:
*/
void pqueue_insert(pqueue *q,data d);

/*
Syfte: Konrollera om priok�n �r tom
Parametrar: q - priok�n (pqueue *)
Returv�rde: true om priok�n �r tom false annars
Kommentarer:
*/
bool pqueue_isEmpty(pqueue *q);

/*
Syfte: Avallokera minne f�r priok�n.
Parametrar: q - priok�n (pqueue *)
Kommentarer: Minne f�r ev v�rden i priok�n avallokeras bara om en funktion
             f�r detta �r satt via pqueue_setMemFunc. Annars �r det anv�ndarens
             uppgift att avallokera minnet f�r alla v�rden i priok�n.
*/
void pqueue_free(pqueue *q);

#endif
