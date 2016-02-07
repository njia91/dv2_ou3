//Written by Johan Eliasson <johane@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) at Ume� University.
//Usage exept those listed above requires permission by the author.

#include <stdlib.h>
#include "tree_3cell.h"
/*
Datatypen Bin�rt tr�d enligt definitionen p� sidan 225 i Lars-Erik Janlert,
Torbj�rn Wiberg Datatyper och algoritmer 2., [rev.] uppl.,Lund,
Studentlitteratur, 2000, x, 387 s. ISBN 91-44-01364-7

Till skillnad mot gr�nsytan i boken s� saknas operationen empty.
*/

/*
Syfte: Skapa ett nytt bin�rt tr�d med en rotnod
Returv�rde: pekare till det nyskapade tr�det
Kommentarer:
*/
binary_tree *binaryTree_create() {
    binary_tree *tree=calloc(1,sizeof(binary_tree));
    tree->root=calloc(1,sizeof(node));
    return tree;
}

/*
Syfte: Installera en minneshanterare f�r tr�det s� att den kan ta �ver
       ansvaret f�r att avallokera minnet f�r v�rdena d� de ej finns kvar
       i tr�det mer.
Parametrar: t - tr�det
            f - en funktionspekare till en funktion som tar in ett v�rde
                av typen data (void pekare) och avallokerar minnet f�r v�rdet
                den pekar p� (ett av den typ av v�rden som lagras i tr�det).
Kommentarer: B�r anropas direkt efter att tr�det skapats om funktionaliteten
             ska anv�ndas. Tr�det funkar �ven utan att denna funktion anropas,
             men det �r d� upp till anv�ndaren av datatypen att avallokera allt
             minne f�r datat som lagras i tr�det.
*/
void binaryTree__setMemHandler(binary_tree *t, memFreeFunc *f) {
    t->freeFunc=f;
}

/*
Syfte: H�mta positionen f�r rotnoden
Parametrar: tr�det
Returv�rde: positionen f�r rotnden
Kommentarer:
*/
binaryTree_pos binaryTree_root(binary_tree *tree) {
    return tree->root;
}

/*
Syfte: Kontrollera om en nod i tr�det har ett v�nsterbarn
Parametrar: tree - tr�det
            n - positionen som man vill unders�ka om den har ett v�nsterbarn
Returv�rde: true om et v�nsterbarn fanns, false annars
Kommentarer:
*/
bool binaryTree_hasLeftChild(binary_tree *tree,binaryTree_pos n) {
    return n->leftChild!=NULL;
}

/*
Syfte: Kontrollera om ett h�gerbarn finns till en given nod
Parametrar: tree - tr�det
            n - positionen som man vill unders�ka om den har ett h�gerbarn
Returv�rde: true om et h�gerbarn fanns, false annars
Kommentarer:
*/
bool binaryTree_hasRightChild(binary_tree *tree,binaryTree_pos n) {
    return n->rightChild!=NULL;
}

/*
Syfte: H�mta h�gra barnets position f�r en given nod
Parametrar: tree - tr�det
            n - positionen vars h�gerbarn man vill h�mta
Returv�rde:  positionen f�r h�gerbarnet
Kommentarer: Ej definierad om ett h�gerbarn inte finns
*/
binaryTree_pos binaryTree_rightChild(binary_tree *tree,binaryTree_pos n) {
    return n->rightChild;
}

/*
Syfte: H�mta v�nstra barnets position f�r en given nod
Parametrar: tree - tr�det
            n - positionen vars v�nsterbarn man vill h�mta
Returv�rde: positionen f�r v�nsterbarnet
Kommentarer: Ej definierad om ett v�nsterbarn inte finn
*/
binaryTree_pos binaryTree_leftChild(binary_tree *tree,binaryTree_pos n) {
    return n->leftChild;
}

/*
Syfte: H�mta positionen f�r f�r�ldern
Parametrar: tree - tr�det
            n - positionen vars f�r�lder man vill h�mta
Returv�rde: positionen f�r f�r�ldern
Kommentarer: Ej definierad f�r rotnoden
*/
binaryTree_pos binaryTree_parent(binary_tree *tree,binaryTree_pos n) {
    return n->parent;
}

/*
Syfte: H�mta en nods etikett
Parametrar: tree - tr�det
            n - positionen f�r noden
Returv�rde: v�rdet p� etiketten
Kommentarer:
*/
data binaryTree_inspectLabel(binary_tree *tree,binaryTree_pos n) {
    return n->label;
}

/*
Syfte: Kontrollera om en etikett finns i noden
Parametrar: tree - tr�det
            n - positionen f�r noden
Returv�rde: true om noden har en ettikett annars false
Kommentarer:
*/
bool binaryTree_hasLabel(binary_tree *tree,binaryTree_pos n) {
    return n->label!=NULL;
}

/*
Syfte: S�tta en etikett f�r en nod
Parametrar: tree - tr�det
            label - etiketten f�r noden
            n - positionen f�r noden
Kommentarer:
*/
void binaryTree_setLabel(binary_tree *tree,data label,binaryTree_pos n) {
    n->label=label;
}

/*
Syfte: S�tt in ett nytt barn till h�ger om en nod
Parametrar: tree - tr�det
            n - positionen f�r f�r�ldranoden
Returv�rde: positionen f�r den nya noden
Kommentarer: Om ett h�gerbarn redan fanns kommer detta tas bort.
*/
binaryTree_pos binaryTree_insertRight(binary_tree *tree,binaryTree_pos n) {
    binaryTree_pos p=calloc(1,sizeof(node));
    p->parent =n;
    if (n->rightChild!=NULL)
        binaryTree_deleteNode(tree,n->rightChild);
    n->rightChild=p;
    return p;
}

/*
Syfte: S�tt in ett nytt barn till h�ger om en nod
Parametrar: tree - tr�det
            n - positionen f�r f�r�ldranoden
Returv�rde: positionen f�r den nya noden
Kommentarer: Om ett v�nsterbarn redan fanns kommer detta tas bort.
*/
binaryTree_pos binaryTree_insertLeft(binary_tree *tree,binaryTree_pos n) {
    binaryTree_pos p=calloc(1,sizeof(node));
    p->parent=n;
    if (n->leftChild!=NULL)
        binaryTree_deleteNode(tree,n->leftChild);
    n->leftChild=p;
    return p;
}

/*
Syfte: Ta bort en nod ur tr�det
Parametrar: tree - tr�det
            n - positionen f�r noden
Returv�rde: position f�r f�r�ldranoden till noden som togs bort
Kommentarer: Om noden som ska tas bort har barn kommer �ven dessa tas bort.
             Ej definierad f�r rotnoden
*/
binaryTree_pos binaryTree_deleteNode(binary_tree *tree,binaryTree_pos n) {
    binaryTree_pos parent=n->parent;
    if(n->leftChild!=NULL) {
        binaryTree_deleteNode(tree,n->leftChild);
    }
    if(n->rightChild!=NULL) {
        binaryTree_deleteNode(tree,n->rightChild);
    }
    if(parent->rightChild==n) {
        parent->rightChild=NULL;
    }
    else {
        parent->leftChild=NULL;
    }
    if(tree->freeFunc && binaryTree_hasLabel(tree,n))
        tree->freeFunc(n->label);
    free(n);
    return parent;
}

/*
Syfte: Avallokera minnet f�r tr�det
Parametrar: tree - tr�det
Kommentarer: efter anropet s� �r tree ej l�ngre definierat
*/
void binaryTree_free(binary_tree *tree) {
    if( binaryTree_hasLeftChild(tree,tree->root))
        binaryTree_deleteNode(tree,tree->root->leftChild);
    if( binaryTree_hasRightChild(tree,tree->root))
        binaryTree_deleteNode(tree,tree->root->rightChild);
    if(tree->freeFunc && binaryTree_hasLabel(tree,tree->root))
        tree->freeFunc(tree->root->label);
    free(tree->root);
    free(tree);
}
