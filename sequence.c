#include "sequence.h"
#include <stdlib.h>
#include <stdio.h>

Sequence init() {
	Sequence arb = calloc(1, sizeof(AVL));
	if(!arb) return NULL;
	arb->root = NULL;
	arb->n = 0;
	return arb;
}

TArb alocNode(int index, Type value) {
	TArb newNode = calloc(1, sizeof(TNod));
	if(!newNode) return NULL;
	newNode->index = index;
	newNode->info = value;
	newNode->height = 1;
	newNode->st = NULL;
	newNode->dr = NULL;
	return newNode;
}

int get_height(TArb root) {
	if(root == NULL)
		return 0;
	return root->height;
}

TArb rotate_left(TArb root) {
	
	TArb x = root->dr;
	TArb aux = x->st;

	root->dr = aux;
	x->st = root;

	int x_st = get_height(x->st);
	int x_dr = get_height(x->dr);
	int r_st = get_height(root->st);
	int r_dr = get_height(root->dr);

	root->height = 1 + (r_st > r_dr ? r_st : r_dr);
	x->height = 1 + (x_st > x_dr ? x_st : x_dr); 

	return x;
}

TArb rotate_right(TArb root) {
	TArb x = root->st;
	TArb aux = x->dr;

	root->st = aux;
	x->dr = root;

	int x_st = get_height(x->st);
	int x_dr = get_height(x->dr);
	int r_st = get_height(root->st);
	int r_dr = get_height(root->dr);

	root->height = 1 + (r_st > r_dr ? r_st : r_dr);
	x->height = 1 + (x_st > x_dr ? x_st : x_dr); 

	return x;
}

TArb getMiniNode(TArb root) {
	TArb p = root;
	while(p->st != NULL) {
		p = p->st;
	}
	return p;
}

TArb getMaxiNode(TArb root) {
	TArb p = root;
	while(p->dr != NULL) {
		p = p->dr;
	}
	return p;
}

TArb insert_aux(TArb root, int index, Type item) {
	if(root == NULL) {
		return alocNode(index, item);
	}
	else if(index > root->index) {
		root->dr = insert_aux(root->dr, index, item);
	}
	else if (index < root->index) {
		root->st = insert_aux(root->st, index, item);
	}
	else {
		return root;
	}

	root->height = 1 + (get_height(root->st) > get_height(root->dr) ? get_height(root->st) : get_height(root->dr));

	int balance_factor = get_height(root->st) - get_height(root->dr);

	if(balance_factor > 1) {
		if(index < root->st->index) {
			return rotate_right(root);
		}
		else {
			root->st = rotate_left(root->st);
			return rotate_right(root);
		}
	}
	else if (balance_factor < -1) {

		if(index > root->dr->index) {
			return rotate_left(root);
		}
		else {
			root->dr = rotate_right(root->dr);
			return rotate_left(root);
		}
	}

	return root;
}

TArb delete_aux(TArb root, int index) {
	if(root == NULL)
		return root;

	if(index > root->index) {
		root->dr = delete_aux(root->dr, index);
	}
	else if(index < root->index) {
		root->st = delete_aux(root->st, index);
	}
	else {
		if(root->st == NULL && root->dr == NULL) {
			TArb aux = root;
			root = NULL;
			free(aux);
		}
		else if(root->st == NULL || root->dr == NULL) {
			TArb aux;
			if(root->st) aux = root->st;
			else aux = root->dr;

			root->info = aux->info;
			root->index = aux->index;
			root->dr = NULL;
			root->st = NULL;

			free(aux);
		}
		else {
			TArb aux = getMiniNode(root->dr);
			root->index = aux->index;
			root->info = aux->info;
			root->dr = delete_aux(root->dr, aux->index);
		}
	}

	if(root == NULL) return NULL;
	root->height = 1 + (get_height(root->st) > get_height(root->dr) ? get_height(root->st) : get_height(root->dr));

	int balance_factor = get_height(root->st) - get_height(root->dr);

	if(balance_factor > 1) {
		if(index < root->st->index) {
			return rotate_right(root);
		}
		else {
			root->st = rotate_left(root->st);
			return rotate_right(root);
		}
	}
	else if (balance_factor < -1) {

		if(index > root->dr->index) {
			return rotate_left(root);
		}
		else {
			root->dr = rotate_right(root->dr);
			return rotate_left(root);
		}
	}

	return root;

}

Sequence insert(Sequence data_structure, Type item, int index) {
	data_structure->root = insert_aux(data_structure->root, index, item);
	(data_structure->n)++;
	return data_structure;
}

Sequence delete(Sequence data_structure, int index) {
	data_structure->root = delete_aux(data_structure->root, index);
	(data_structure->n)--;
	return data_structure;
}

TArb search(TArb root, TArb ant, int index) {
	if(root == NULL) {
		return NULL;
	}

	if(root->index > index) {
		return search(root->st, root, index);
	}
	if(root->index < index) {
		return search(root->dr, root, index);
	}
	else {
		if(ant->st == root) {
			ant->st = NULL;
			return root;
		}
		else {
			ant->dr = NULL;
			return root;
		}
	}
	if(root == NULL) return NULL;
	root->height = 1 + (get_height(root->st) > get_height(root->dr) ? get_height(root->st) : get_height(root->dr));
}

Type lookup(Sequence data_structure, int index) {
	TArb p = data_structure->root;

	while(p != NULL) {

		if(p->index < index) {
			p = p->dr;
		}
		else if (p->index > index) {
			p = p->st;
		}
		else {
			return p->info;
		}
	}
	return -1; //index gresit;
}
Sequence set(Sequence data_structure, Type item, int index) {
	TArb p = data_structure->root;

	while(p != NULL) {

		if(p->index < index) {
			p = p->dr;
		}
		else if (p->index > index) {
			p = p->st;
		}
		else {
			p->info = item;
			break;
		}
	}
	return data_structure;
}

int size(Sequence data_structure) {
	return data_structure->n;
}

Sequence* split(Sequence data_structure, int index) {
	
	Sequence s1 = calloc(1, sizeof(AVL));
	if(!s1) return NULL;
	Sequence s2 = calloc(1, sizeof(AVL));
	if(!s1) return NULL;
	
	s1->n = index + 1;
	s2->n = size(data_structure) - index - 1;

	s1->root = data_structure->root;
	s2->root = search(s1->root, NULL, index);

	Sequence* result = calloc(2, sizeof(Sequence));
	result[0] = s1;
	result[1] = s2;
	return result;
}

void recompute_height(TArb root) {
	if(root == NULL)
		return;

	recompute_height(root->dr);
	root->height = get_height(root->st) > get_height(root->dr) ? get_height(root->st) : get_height(root->dr);
}


Sequence concat(Sequence data_structure1, Sequence data_structure2) {
	Sequence sq = calloc(1, sizeof(AVL));
	if(!sq) return NULL;

	sq->n = data_structure1->n + data_structure2->n;
	sq->root = getMaxiNode(data_structure1->root);

	TArb newNode = alocNode(sq->root->index, sq->root->info);

	data_structure1->root = delete_aux(data_structure1->root, sq->root->index);

	recompute_height(data_structure1->root);

	sq->root->height = get_height(data_structure1->root) > get_height(data_structure2->root)
	? get_height(data_structure1->root) : get_height(data_structure2->root);

	sq->root = newNode;

	sq->root->st = data_structure1->root;
	sq->root->dr = data_structure2->root;

	data_structure1->root = sq->root;
	data_structure1->n = sq->n;

	return sq;
}

int main() {

}