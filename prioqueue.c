//Written by Lena Kallin Westin <kallin@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) and DV2: Algoritmer och
// probleml�sning at Ume� University.
//Usage exept those listed above requires permission by the author.

#include <stdio.h>
#include "prioqueue.h"

/*
priok� implementerad med hj�lp av riktad lista. Kr�ver implementation av lista som �verenst�mmer med gr�nssninttet f�r listan som anv�nds p� kursen f�r att fungera.
*/

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
pqueue *pqueue_empty(CompareFunction *compare_function){
    MyPQ *prioq = calloc(sizeof (MyPQ),1);
    if (!prioq)
        return NULL;
    prioq->pq=list_empty();
    prioq->cf = compare_function;
    return (pqueue *)prioq;
}

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
void pqueue_setMemHandler(pqueue *q, memFreeFunc *f) {
    MyPQ *prioq = (MyPQ*)q;
    list_setMemHandler(prioq->pq,f);
}

/*
Syfte: Ta bort f�rsta v�rdet i priok�n
Parametrar: q - priok�n (pqueue *)
Kommentarer: odefinierad f�r en tom priok�
*/
void pqueue_delete_first(pqueue *q){
    MyPQ *prioq = (MyPQ*)q;
    list_remove(prioq->pq,list_first(prioq->pq));
}

/*
Syfte: H�mtar f�rsta v�rdet i priok�n
Parametrar: q - priok�n (pqueue *)
Returv�rde: v�rdet som fanns l�ngst ram i priok�n
Kommentarer: ej definierad f�r tom priok�.
*/
data pqueue_inspect_first(pqueue *q){
    MyPQ *prioq = (MyPQ*)q;
    return list_inspect(prioq->pq,list_first(prioq->pq));
}

/*
Syfte: L�gga till ett v�rde p� r�tt st�lle utifr�n sin prioritet i priok�n
Parametrar: q - priok�n (pqueue *)
            d- v�rdet som ska l�ggas till (data)
Kommentarer:
*/
void pqueue_insert(pqueue *q,data d){
    MyPQ *prioq = (MyPQ*)q;
    int placed = 0;
    list_position pos =list_first(prioq->pq);

    if (list_isEmpty(prioq->pq)){
        list_insert(prioq->pq, d, list_first(prioq->pq));
    }else{
        while(!placed && pos!=list_end(prioq->pq)){
            if(prioq->cf(d, list_inspect(prioq->pq, pos))){
                    placed = 1;
                    list_insert(prioq->pq, d, pos);
            }
            pos = list_next(prioq->pq, pos);
        }
        if (!placed){
            list_insert(prioq->pq, d, pos);
        }
    }
}

/*
Syfte: Konrollera om priok�n �r tom
Parametrar: q - priok�n (pqueue *)
Returv�rde: true om priok�n �r tom false annars
Kommentarer:
*/
bool pqueue_isEmpty(pqueue *q){
    MyPQ *prioq = (MyPQ*)q;
    return list_isEmpty(prioq->pq);
}

/*
Syfte: Avallokera minne f�r priok�n.
Parametrar: q - priok�n (pqueue *)
Kommentarer: Minne f�r ev v�rden i priok�n avallokeras bara om en funktion
             f�r detta �r satt via pqueue_setMemFunc. Annars �r det anv�ndarens
             uppgift att avallokera minnet f�r alla v�rden i priok�n.
*/
void pqueue_free(pqueue *q){
    MyPQ *prioq = (MyPQ*)q;
    list_free(prioq->pq);
    free(prioq);
}
