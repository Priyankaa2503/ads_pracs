#include <stdio.h>

#define STACK_SIZE 10

int stack[STACK_SIZE];

int top = -1;

void push(int value)
{
    top++;
    if (top >= STACK_SIZE)
    {
        printf("Error : max stack size reached");
        return;
    }
    else
    {
        stack[top] = value;
    }
}

void pop()
{
    if (top == -1)
    {
        printf("Error : stack has no elements to pop");
    }
    else
    {
        top--;
    }
}

void multipop(int n)
{
    printf("Popping %d elements\n", n);
    if (top == -1)
    {
        printf("Error : stack has no elements to pop");
    }
    else if (n > top + 1)
    {
        printf("Error : stack has less than %d elements", n);
    }
    else
    {
        top -= n;
    }
}

void printStack()
{
    printf("Stack : ");
    for (int i = 0; i <= top; i++)
    {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int main()
{
    printf("Pushing 1, 2, 3, 4, 5\n");
    push(1);
    push(2);
    push(3);
    push(4);
    push(5);
    printStack();
    multipop(3);
    printStack();
    printf("Pushing 6, 7\n");
    push(6);
    push(7);
    printStack();
    multipop(2);
    printStack();
}