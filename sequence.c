#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sequence.h"

// --> complexitate O(1)
Sequence init()
{
	// Returneaza structura vida
	srand(time(NULL));
	Sequence new_seq = (Sequence)malloc(sizeof(struct sequence));
	new_seq->left = new_seq->right = NULL;
	new_seq->priority = rand()%1000000000 + 1; // echilibram arborele
	new_seq->tree_dim = 1; // un singur nod in arbore

	return new_seq;
}

// --> complexitate O(log n)
Sequence insert(Sequence* data_structure, Type item, int index)
{
	// Insereaza un element în structura pe pozitia index
	// Vom imparti arborele in doi arbori in locatia indicata folosind
	// functia my_split (O(log n) si ii vom concatena(O(log n)) la loc
	// abia dupa ce vom insera nodul dat
	Sequence *vec_seq;
	vec_seq = split(*data_structure, index);
	Sequence new_node = init();  // creem nodul pe care il vom introduce
	new_node->item = item;
	// lipim de nodul stang noul nod
	Sequence new_data_structure = concat(vec_seq[0], new_node);
	*data_structure = concat( new_data_structure,vec_seq[1]);

	return *data_structure;
}

// --> complexitate O(log n)
Sequence delete(Sequence* data_structure, int index)
{
	// Sterge elementul de pe pozitia index din structura
	// Efectuam impartiri succesive, vec_seq2[0] va contine elementul
	// pe care vrem sa il stergem
	// Realizam concatenarea celor doi arbori vec_seq1[0] si vec_seq2[1]
	// pentru a sterge elementul cu indexul respectiv
	Sequence *vec_seq1;
	vec_seq1 = split(*data_structure, index);
	Sequence *vec_seq2;
	vec_seq2 = split(vec_seq1[1], index);
	*data_structure = concat(vec_seq1[0], vec_seq2[1]);

	return *data_structure;
}

// --> complexitate O(log n)
Type lookup(Sequence data_structure, int index)
{
	// Returneaza valoarea elementului de pe pozitia index
	if (data_structure == NULL)  // structura nu contine nimic
		return -999999999;  // => nu gaseste nimic
	// radacina e in stanga, cautam indicele
	if (size(data_structure->left) + 1 > index)
		return lookup(data_structure->left, index);
	else if (size(data_structure->left) + 1  < index)
	{
		// daca este in partea dreapta, actualizam indecele
		int new_index = index - size(data_structure->left) - 1;
		// ne mutam in partea dreapta
		return lookup(data_structure->right, new_index);
	}
	else return data_structure->item;
}

// --> complexitate O(log n)
Sequence set(Sequence data_structure, Type item, int index)
{
	// Înlocuieste valoarea elementului de pe pozitia index
	if (data_structure == NULL) // structura nu contine nimic => nu avem ce schimba
		return NULL;
	my_set(data_structure, item, index);
	return data_structure; // returnam structura actualizata
}

// --> complexitate O(1)
int size(Sequence data_structure)
{
	// Returneaza dimensiunea structurii
	if (data_structure == NULL)
		return 0; // structura nu contine nimic => nu exista dimensiune
	else
		return data_structure->tree_dim;  // altfel, returnam marimea
		//retinuta in definitia oricarui nod din arbore
}

// --> complexitate O(log n)
Sequence* split(Sequence data_structure, int index)
{
	// Returneaza cele doua structuri rezultate în urma divizarii
	// * (rezultatul este retinut într-un Sequence* cu 2 elemente)
	Sequence* vec_seq = (Sequence *) malloc(2 * sizeof(Sequence));
	if (!data_structure)  // daca structura e goala, returnam NULL
	{
		vec_seq = NULL;
		return vec_seq;
	}
	my_split(data_structure, index, &vec_seq[0], &vec_seq[1]);

	return vec_seq;
}

// --> complexitate O(log n)
Sequence concat(Sequence data_structure1, Sequence data_structure2) {
	// Returneaza structura rezultata dupa concatenare
	if (data_structure1 == NULL && data_structure2 == NULL)
		return NULL;
		// Verificam daca una din structuri este cumva vida, in acest caz
	// o returnam pe cealalta
	if (data_structure1 == NULL)
		return data_structure2;
	if (data_structure2 == NULL)
		return data_structure1;
	Sequence new_seq;
	// alegem ca radacina cu prioritatea mai mare radacina arborelui concatenat
	if (data_structure1->priority > data_structure2->priority)
	{
		data_structure1->right = concat(data_structure1->right, data_structure2);
		// radacina concatenarii devine radacina lui data_structure1
		new_seq = data_structure1;
	}
	else
	{
		data_structure2->left = concat(data_structure1, data_structure2->left);
		new_seq = data_structure2;
	}
	// reinitializam dimensiunea arborelui
	new_seq->tree_dim = size(new_seq->left) + size(new_seq->right) + 1;

	return new_seq;
}

void my_split(Sequence data_structure, int index, Sequence* left_data_struct,
				Sequence* right_data_struct)
{
	// elementul din idex este retinut in arborele drept
	if (!data_structure)
	{
		*left_data_struct = *right_data_struct = NULL;
		return; // daca structura este goala, nu returnam nimic
	}
	Sequence aux;
	// cautam locatia in care vrem sa impartim arborele comparand indexul cu nr
	// de elemente retinute in subarborele stang, inclusiv cu radacina acestuia
	if (size(data_structure->left) + 1 > index)
	{
		// impartim la stanga si cautam locul din nou
		my_split(data_structure->left, index, left_data_struct, &aux);
		*right_data_struct = data_structure;
		(*right_data_struct)->left = aux;
	}
	else
	{
		// impartim la stanga si cautam locul din nou
		my_split(data_structure->right, index - size(data_structure->left) + 1
				, &aux, right_data_struct);
		*left_data_struct = data_structure;
		(*left_data_struct)->right = aux;
	}
	// reinitializam numarul de noduri
	data_structure->tree_dim = size(data_structure->left) +
									size(data_structure->right) + 1;
}

void my_set(Sequence data_structure, Type item, int index)
{
	// Înlocuieste valoarea elementului de pe pozitia index
	// Radacina e in stanga, cautam indicele in stanga
	if(size(data_structure->left) + 1 > index)
		my_set(data_structure->left, item, index);
	else if (size(data_structure->left) + 1 < index)
	{
		// daca este in partea dreapta, actualizam indecele
		int new_index = index - size(data_structure->left) - 1;
		// ne mutam in partea dreapta
		my_set(data_structure->right, item, new_index);
	} else {
	// atunci cand gasim indexul, modificam valoarea
	data_structure->item = item;
	}
}

void inorder(Sequence data_structure)
{
	//functie de afisare a arborelui in inordine
	if(data_structure == NULL)
		return;
	inorder(data_structure->left);
	printf("%d ", data_structure->item);
	inorder(data_structure->right);
}

int main()
{
	Sequence new_seq = init();
	new_seq->item = 1;

	new_seq = insert(&new_seq, 2, 2);
	new_seq = insert(&new_seq, 4, 3);
	new_seq = insert(&new_seq, 7, 2);
	new_seq = insert(&new_seq, 3, 3);
	new_seq = insert(&new_seq, 5, 4);
	new_seq = insert(&new_seq, 6, 5);
	new_seq = insert(&new_seq, 8, 4);
	printf("Arborele obtinut in urma inserarilor succesive\n");
	inorder(new_seq);

	new_seq = delete(&new_seq, 1);

	// Primul element din arbore are index = 0
	printf("\nArborele obtinut in stergerii elementului cu index=1\n");
	inorder(new_seq);

	printf("\nLookup pentru index=3   => %d\n", lookup(new_seq, 3));

	new_seq = set(new_seq, 8, 1);
	printf("Introducem in index=1 item=8\n");
	inorder(new_seq);

	printf("\nDimensiunea arborelui in urma operatiilor facute este:");
	printf("% d\n", size(new_seq));

	Sequence* vec_seq;
	vec_seq = split(new_seq, 3);
	printf("Functia split aplicata pe arborele curent in index=3\n");
	printf("Primul arbore rezultat: ");
	inorder(vec_seq[0]);
	printf("\nAl doilea arbore rezultat: ");
	inorder(vec_seq[1]);
	printf("\n");

	Sequence seq;
	seq = concat(vec_seq[0], vec_seq[1]);
	printf("Functia concat aplicata pe cei doi arbori obtinuti prin split:\n");
	inorder(seq);
	printf("\n");

	return 0;
}