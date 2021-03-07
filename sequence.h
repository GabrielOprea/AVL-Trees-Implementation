typedef int Type;


typedef struct node{
    Type info;
    int index;
    int height;
    struct node *st;
    struct node *dr;
}TNod, *TArb;

typedef struct sequence {
	int n;
	TNod* root;
} *Sequence, AVL;

/*
* Returneaza structura vida
*/
Sequence init();
/*
* Insereaza un element în structura pe pozitia index
*/
Sequence insert(Sequence data_structure, Type item, int index);
/*
* Sterge elementul de pe pozitia index din structura
*/
Sequence delete(Sequence data_structure, int index);
/*
* Returneaza valoarea elementului de pe pozitia index
*/
Type lookup(Sequence data_structure, int index);
/*
* Înlocuieste valoarea elementului de pe pozitia index
*/
Sequence set(Sequence data_structure, Type item, int index);
/*
* Returneaza dimensiunea structurii
*/
int size(Sequence data_structure);
/*
* Returneaza cele doua structuri rezultate în urma divizarii
* (rezultatul este retinut într-un Sequence* cu 2 elemente)
*/
Sequence* split(Sequence data_structure, int index);
/*
* Returneaza structura rezultatata dupa concatenare
*/
Sequence concat(Sequence data_structure1, Sequence data_structure2);