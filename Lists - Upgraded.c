#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_t {
	int value;
	struct node_t *next;
};

struct list_t {
	struct node_t *head;
};

struct node_t* create(int);
void display(struct list_t);
void insert_before(struct list_t*, int);
void remove_before(struct list_t*);
void insert_after(struct list_t*, int);
void remove_after(struct list_t*);
int get(struct list_t, int);
void insert_pos(struct list_t*, int, int);
void remove_pos(struct list_t*, int);
void destroy_list(struct list_t*);
int size(struct list_t);
int empty(struct list_t);
struct list_t copy(struct list_t);

int main() {

	struct node_t *n = create(4);
	struct list_t l;
	l.head = n;

	insert_before(&l, 3);
	insert_before(&l, 2);
	insert_before(&l, 1);

	/*display(l);

	remove_before(&l);

	display(l);

	insert_after(&l, 5);

	display(l);

	remove_after(&l);
	
	display(l);

	printf("%d\n", get(l, 2));

	insert_pos(&l, 1, 16);

	display(l);*/

	//remove_pos(&l, 1);

	display(l);

	//printf("%d ", size(l));

	struct list_t copied_l = copy(l);

	insert_pos(&copied_l, 2, 21);

	display(copied_l);

	display(l);

	destroy_list(&l);

	destroy_list(&copied_l);

	return 0;
}

struct list_t copy(struct list_t list) {
	struct node_t *current_elem = list.head;

	struct list_t copy;

	copy.head = create(current_elem->value);

	for(int i = 0; i < size(list) - 1; i++) {
		current_elem = current_elem->next;
		insert_after(&copy, current_elem->value);
	}

	return copy;
}

int empty(struct list_t list) {
	if(size(list)) {
		return 0;
	}
	else {
		return 1;
	}
}

int size(struct list_t list) {
	struct node_t *current_num = list.head;

	int size = 0;

	while(current_num != NULL) {
		size++;

		current_num = current_num->next;
	}

	return size;
}

void destroy_list(struct list_t *list) {
	//struct node_t *current_elem = list->head;

	while(list->head != NULL) {
		//remove_after(list);
		remove_before(list);

		//current_elem = current_elem->next;
	}
}

void remove_pos(struct list_t *list, int position) {
	int count = -1;

        struct node_t *current_elem = list->head;

        while(current_elem != NULL) {
                count++;

                if(count == position - 1) {
                        free(current_elem->next);
			current_elem->next = current_elem->next->next;
                        return;
                }

                current_elem = current_elem->next;
        }

}

void insert_pos(struct list_t *list, int position, int elem_value) {
	int count = -1;

        struct node_t *current_elem = list->head;

	struct node_t *inserted_elem = create(elem_value);

        while(current_elem != NULL) {
                count++;

                if(count == position - 1) {
			inserted_elem->next = current_elem->next;
			current_elem->next = inserted_elem;
			return;
                }

                current_elem = current_elem->next;
        }
}

int get(struct list_t list, int position) {
	int count = -1;

	struct node_t *current_elem = list.head;

	while(current_elem != NULL) {
		count++;
		if(count == position) {
			return current_elem->value;
		}

		current_elem = current_elem->next;
	}

	return -1;
}

void remove_after(struct list_t *list) {
	if(list->head->next == NULL) {
		remove_before(list);
		return;
	}

	struct node_t *current_elem = list->head;

	while(current_elem->next->next != NULL) {
		current_elem = current_elem->next;
	}

	free(current_elem->next);

	current_elem->next = NULL;
}

void insert_after(struct list_t *list, int elem_value) {
	struct node_t *current_elem = list->head;

	while(current_elem->next != NULL) {
		current_elem = current_elem->next;
	}

	struct node_t *inserted_elem = create(elem_value);

	current_elem->next = inserted_elem;
}

void remove_before(struct list_t *list) {
	struct node_t *removed = list->head;
	
	list->head = removed->next;

	free(removed);
}

void insert_before(struct list_t *list, int elem_value) {
	struct node_t *inserted_elem = create(elem_value);

	inserted_elem->next = list->head;
	list->head = inserted_elem;
}

void display(struct list_t list) {
	struct node_t *current_elem = list.head;

	while(current_elem != NULL) {
		printf("%d ", current_elem->value);

		current_elem = current_elem->next;
	}

	printf("\n");
}

struct node_t* create(int value) {
	struct node_t *new_elem = malloc(sizeof(struct node_t));

	new_elem->value = value;
	new_elem->next = NULL;

	return new_elem;
}
