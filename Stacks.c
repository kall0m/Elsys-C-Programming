#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack_t {
	int *data;
	int size;
	int capacity;
};

struct stack_t stack_init(int);
void stack_destroy(struct stack_t*);
void push(struct stack_t*, int);
int is_full(struct stack_t);
void stack_resize(struct stack_t*);
int top(struct stack_t);
void pop(struct stack_t*);
int is_empty(struct stack_t);
int size(struct stack_t);
struct stack_t stack_copy(struct stack_t);
float rpn_solve(char*);
float check(int, int, char);

int main() {

	struct stack_t st = stack_init(5);
	push(&st, 1);
	printf("%d", top(st));
	push(&st, 2);
	push(&st, 3);
	push(&st, 4);
	push(&st, 5);

	//printf("\n%d", top(st));
	//printf("\n%d", size(st));
	pop(&st);
	//printf("\n%d", top(st));
	//printf("\n%d", size(st));

	/*struct stack_t copy = stack_copy(st);
	for(int i = 0; i < copy.size; i++) {
		printf("%d ", copy.data[i]);
	}*/

	//stack_destroy(&copy);
	stack_destroy(&st);

	char rpn[] = "9 5 2 + - 4 + 1 -";

	printf("\n%.2f", rpn_solve(rpn));

	return 0;
}

float check(int first, int second, char operation) {
	float result = 0.0;

	switch(operation) {
		case '+': result = first + second; break;
		case '-': result = first - second; break;
		case '*': result = first * second; break;
		if(second == 0) { break; }
		case '/': result = first / second; break;
	}

	return result;
}

float rpn_solve(char* rpn_exp) {
	struct stack_t steps = stack_init(2);

	for(int i = 0; i < strlen(rpn_exp); i++) {
		if(rpn_exp[i] == ' ') { continue; }
		else if(rpn_exp[i] >= '0' && rpn_exp[i] <= '9') {
			push(&steps, rpn_exp[i] - '0');
		}
		else if(rpn_exp[i] == '+' || rpn_exp[i] == '-' || rpn_exp[i] == '*' || rpn_exp[i] == '/') {
			if(size(steps) < 2) { return 0.0; }
			
			int second = top(steps);
			pop(&steps);
			int first =  top(steps);
			pop(&steps);

			push(&steps, (int)check(first, second, rpn_exp[i]));
		}
	}

	float result = top(steps);
	
	stack_destroy(&steps);

	return result;
}

struct stack_t stack_copy(struct stack_t stack) {
	struct stack_t result = stack_init(stack.capacity);

	for(int i = 0; i < stack.size; i++) {
		result.data[i] = stack.data[i];
	}
	result.size = stack.size;

	return result;
}

int size(struct stack_t stack) {
	return stack.size;
}

int is_empty(struct stack_t stack) {
	return stack.size == 0;
}

void pop(struct stack_t *stack) {
	if(is_empty(*stack)) {
		return;
	}
	stack->size--;
}

int top(struct stack_t stack) {
	if(is_empty(stack)) {
		return 0;
	}
	return stack.data[stack.size - 1];
}

void stack_resize(struct stack_t *stack) {
	stack->capacity *= 2;
	stack->data = realloc(stack->data, stack->capacity * sizeof(int));
}

int is_full(struct stack_t stack) {
	return stack.size == stack.capacity;
}

void push(struct stack_t *stack, int elem) {
	if(is_full(*stack)){
		stack_resize(stack);
	}

	stack->data[stack->size++] = elem;
}

void stack_destroy(struct stack_t *stack) {
	stack->size = 0;
	stack->capacity = 0;
	free(stack->data);
	stack->data = NULL;
}

struct stack_t stack_init(int initial_capacity){
	struct stack_t stack;

	stack.size = 0;
	stack.capacity = initial_capacity;
	stack.data = malloc(initial_capacity * sizeof(int));

	return stack;
}
