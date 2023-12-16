#include <stdio.h>

int array[10];
int count = 0;

void initArray()
{
    for (int i = 0; i < 10; i++)
    {
        array[i] = 0;
    }
}

void printArray()
{
    printf("%d\t : \t", count);
    for (int i = 0; i < 10; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void push()
{
    printf("\nPush\n");
    ++count;
    int index = 9;
    if (array[index] == 0)
    {
        array[index] = 1;
    }
    else
    {
        while (array[index] != 0)
        {
            array[index] = 0;
            index--;
        }
        array[index] = 1;
    }
    printArray();
}

void pop()
{
    printf("\nPop\n");
    --count;
    int index = -1;
    for (int i = 9; i >= 0; i--)
    {
        if (array[i] == 1)
        {
            index = i;
            break;
        }
    }
    if (index == 9)
    {
        array[index] = 0;
    }
    else
    {
        array[index] = 0;
        for (int i = (index + 1); i <= 9; i++)
        {
            array[i] = 1;
        }
    }
    printArray();
}

int main()
{
    initArray();
    printArray();
    push();
    push();
    push();
    push();
    push();
    push();
    push();
    push();
    push();
    push();
    pop();
    pop();
    push();
}