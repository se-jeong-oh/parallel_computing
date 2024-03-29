#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"

/*
char stack_op[50];
int stack_num[50];
int top_num = -1;
int top_op = -1;

void push_op(char key);
void push_num(int key);
char pop_op(void);
int pop_num(void);
int optCheck(char opt1, char opt2);
int calFunc(int num1, int num2, char op);
*/
int main() {
	char string[50] = "5-3**2*2";
	int result;
	int flag = 0;
	for(int i = 0; i < strlen(string); i++) {
		if (string[i] == '+' || string[i] == '*' || string[i] == '-' || string[i] == '/') {
			if (string[i] == '*') {
				if (string[i+1] == '*') {
					string[i]=' ';
					i+=1;
					string[i] = '^';
				}
			}
			while(1) {
				if (top_op == -1 || optCheck(string[i], stack_op[top_op]) == 1) {
					push_op(string[i]);
					break;
				}
				else {
					char opt = pop_op();
					int num1 = pop_num();
					int num2 = pop_num();
					result = calFunc(num1, num2, opt);
					push_num(result);
				}
			}
		}
		else {
			if (flag == 1) {
				push_num(-atoi(&string[i]));
				flag = 0;
			}
			else
				push_num(atoi(&string[i]));
		}
	}
	while(top_op != -1) {
		char opt = pop_op();
		int num1 = pop_num();
		int num2 = pop_num();
		result = calFunc(num1, num2, opt);
		push_num(result);
	}
	printf("equation = %s, result : %d\n", string, result);
}
/*
int calFunc(int num1, int num2, char op) {
	int result;
	printf("%d %c %d\n", num1, op, num2);
	switch(op) {
		case '+': result = num1 + num2; break;
		case '*': result = num1 * num2; break;
		case '/': result = num2 / num1; break;
		case '^': result = pow(num2, num1); break;
		case '-': result = num2 - num1; break;
	}
	return result;
}
int optCheck(char opt1, char opt2) {
	// if returns 1, opt1 > opt2 (ex opt1 = *, opt2 = +)
	// else returns 0
	if (opt1 == '^' && opt2 != '^') 
		return 1;
	else {
		if (opt1 == '*' || opt1 == '/')
			if(opt2 == '+' || opt2 == '-')
				return 1;
			else 
				return 0;
		else 
			return 0;
	}
}
void push_op(char key) {
	top_op++;
	stack_op[top_op] = key;
}
void push_num(int key) {
	top_num++;
	stack_num[top_num] = key;
}
char pop_op(void) {
	if (top_op <= -1)
		return -1;
	top_op--;
	return stack_op[top_op+1];
}
int pop_num(void) {
	if(top_num <= -1)
		return -1;
	top_num--;
	return stack_num[top_num+1];
}
*/
