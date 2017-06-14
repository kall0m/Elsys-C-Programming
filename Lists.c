#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack_t {
	struct list_t *data;
	int size;
	int capacity;
};

struct node_t {
	int value;
	struct node_t *next;
};

struct list_t {
	struct node_t *head;
};

struct stack_t init();
void push(struct stack_t*, int);
void pop(struct stack_t*);
int top(struct stack_t);
int stack_size(struct stack_t);

void insert_before(struct list_t*, int);
struct node_t* create(int);
void remove_before(struct list_t*);
void insert_after(struct list_t*, int);
void remove_after(struct list_t*);
int get(struct list_t, int);
void destroy(struct list_t*);
int size(struct list_t);
int empty(struct list_t);
struct list_t copy(struct list_t);

int are_ballanced(char*);

int main() {
	struct list_t l;
	struct node_t *n = create(5);
	l.head = n;

	//printf("%d\n", l.head->value); //5

	//insert_before(&l, 6);
	//printf("\n%d\n", l.head->value); //6
	//printf("%d\n", l.head->next->value); //5

	//remove_before(&l);
	//printf("\n%d\n", l.head->value);

	insert_after(&l, 7);
	insert_after(&l, 8);
	//insert_after(&l, 9);
	//printf("\n%d\n", l.head->value); // 5
	//printf("%d\n", l.head->next->value); // 7
	//printf("%d\n", l.head->next->next->value); // 8
	//printf("%d\n", l.head->next->next->next->value); // 9

	//remove_after(&l);
	//printf("\n%d\n", l.head->value); // 5
        //printf("%d\n", l.head->next->value); // 7
        //printf("%d\n", l.head->next->next->value); // 8
	// ! printf("%d\n", l.head->next->next->next->value); //NULL

	//insert_after(&l, 6);
	//insert_after(&l, 9);

	//printf("\n%d\n", get(l, 1));
	//printf("\n%d\n", get(l, 2));
	//printf("\n%d\n", get(l, 3));
	//printf("\n%d\n", get(l, 4));
	//printf("\n%d\n", get(l, 5));

	//printf("\n%d\n", size(l));

	//printf("\n%d\n", empty(l));

	//struct list_t copy_of_list = copy(l);

	//printf("\n%d\n", copy_of_list.head->value);
	//printf("%d\n", copy_of_list.head->next->value); // 7
        //printf("%d\n", copy_of_list.head->next->next->value); // 8

	//remove_before(&copy_of_list);

	//printf("\n%d\n", copy_of_list.head->value);
	//printf("\n%d\n", l.head->value);

	//destroy(&l);

	//printf("\n%d\n", empty(l));

	char *brackets;// = "({})(([{}()])";

	while(1) {
		scanf("%s", brackets);

		if(are_ballanced(brackets)) {
			printf("Yes\n");
		}	
		else {
			printf("No\n");
		}
	}

	return 0;
}

int are_ballanced(char *str) {
	struct stack_t s = init();

	for(int i = 0; i < strlen(str); i++) {
		if(str[i] == '(' || str[i] == '[' || str[i] == '{') {
			push(&s, str[i]);
		}
		else if(str[i] == ')' || str[i] == ']' || str[i] == '}') {
			if(stack_size(s) == 0) {
				return 0;
			}
			if((top(s) == '(' && str[i] == ')') || (top(s) == '[' && str[i] == ']') || (top(s) == '{' && str[i] == '}')) {
				pop(&s);
			}
			else {
				return 0;
			}
		}
	}

	return stack_size(s) == 1;
}

int top(struct stack_t stack) {
	return stack.data->head->value;
}

int stack_size(struct stack_t stack) {
	return size(*(stack.data));
}

void pop(struct stack_t *stack) {
	remove_before(stack->data);
}

void push(struct stack_t *stack, int elem) {
	insert_before(stack->data, elem);
}

struct stack_t init() {
	struct stack_t st;

	st.data = malloc(sizeof(struct list_t));

	struct node_t *n = create(0);
        st.data->head = n;

	st.size = 0;

	st.capacity = 1000000;

	return st;
}

struct list_t copy(struct list_t list) {
	struct node_t *list_elem = list.head;

	struct list_t copy_of_list;
	copy_of_list.head = create(list_elem->value);

	for(int i = 0; i < size(list) - 1; i++) {
		list_elem = list_elem->next;
		insert_after(&copy_of_list, list_elem->value);
	}

	return copy_of_list;
}

int empty(struct list_t list) {
	return size(list) == 0;
}

int size(struct list_t list) {
	int listSize = 0;

	while(list.head != NULL) {
		listSize++;
		list.head = list.head->next;
	}

	return listSize;
}

void destroy(struct list_t *list) {
	//struct node_t *current;

	while(list->head != NULL) {
		/*current = list->head;
		list->head = list->head->next;
		free(current);*/
		//remove_after(list);
		remove_before(list);
	}
}

int get(struct list_t list, int pos) {
	int count = 0;
	struct node_t *current = list.head;

	while(current != NULL) {
		count++;
		if(count == pos) {
			return current->value;
		}
		current = current->next;
	}

	return 0;
}

void remove_after(struct list_t *list) {
	struct node_t *last = list->head;

	if(last->next == NULL) {
		remove_before(list);
		return;
	}

	while(last->next->next != NULL) {
		last = last->next;
	}

	free(last->next);
	last->next = NULL;
}

void insert_after(struct list_t *list, int elem) {
	struct node_t *last = list->head;
	
	while(last->next != NULL) {
		last = last->next;
	}

	struct node_t *new_elem = create(elem);

	last->next = new_elem;
}

void remove_before(struct list_t *list) {
	struct node_t *removed = list->head;
	list->head = removed->next;

	free(removed);
}

struct node_t* create(int value) {
	struct node_t *new_elem = malloc(sizeof(struct node_t));

	new_elem->value = value;
	new_elem->next = NULL;

	return new_elem;
}

void insert_before(struct list_t *list, int elem) {
	struct node_t *inserted_elem = create(elem);
	
	inserted_elem->next = list->head;
	list->head = inserted_elem;
}
