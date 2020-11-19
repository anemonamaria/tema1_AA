typedef int Type;

//structura unui nod de arbore cartezian cu chei implicite
typedef struct sequence
{
	int priority, tree_dim;
	Type item;
	struct sequence* left;
	struct sequence* right;

} *Sequence;

Sequence init();
// Returneaza structura vida
Sequence insert(Sequence* data_structure, int item, int index);
// Insereaza un element în structura pe pozitia index
Sequence delete(Sequence* data_structure, int index);
// Sterge elementul de pe pozitia index din structura
Type lookup(Sequence data_structure, int index);
// Returneaza valoarea elementului de pe pozitia index
Sequence set(Sequence data_structure, Type item, int index);
// Înlocuieste valoarea elementului de pe pozitia index
int size(Sequence data_structure);
// Returneaza dimensiunea structurii
Sequence* split(Sequence data_structure, int index);
// Returneaza cele doua structuri rezultate în urma divizarii
// * (rezultatul este ret, inut într-un Sequence* cu 2 elemente)
Sequence concat(Sequence data_structure1, Sequence data_structure2);
// Returneaza structura rezultata dupa concatenare

// FUNCTII ADAUGATE
void my_split(Sequence data_structure, int index, Sequence* left_data_struct
                    , Sequence* right_data_struct);
// Returneaza cele doua structuri rezultate în urma divizarii
// ne usureaza lucru in C
void inorder(Sequence data_structure);
// afisarea in inordine a arborelui
void my_set(Sequence data_structure, Type item, int index);
// Înlocuieste valoarea elementului de pe pozitia index
// ne usureaza lucrul in C

