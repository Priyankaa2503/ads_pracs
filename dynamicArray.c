#include <stdio.h>
#include <stdbool.h>
int ArraySize = 0;
int top = -1;
int array[100];
void initArray()
{
    for (int i = 0; i < 100; i++)
    {
        array[i] = -1;
    }
}
void printArray()
{
    printf("Array: \n");
    for (int i = 0; i < ArraySize; i++)
    {
        if (array[i] != -1)
            printf("%d ", array[i]);
        else
            printf("_ ");
    }
    printf("\n");
}
bool isArrayFull()
{
    for (int i = 0; i < ArraySize; i++)
    {
        if (array[i] == -1)
            return false;
    }
    return true;
}
void push(int value)
{
    top++;
    if (ArraySize == 0)
    {
        ArraySize = 1;
    }
    else
    {
        bool x = isArrayFull();
        if (x == true)
        {
            ArraySize = ArraySize * 2;
        }
    }
    array[top] = value;
    printArray();
}
void del(int value)
{
    int index = -1;
    if (top == -1)
    {
        printf("Error : array is empty");
        return;
    }
    for (int i = 0; i < top; i++)
    {
        if (array[i] == value)
            index = i;
    }
    if (index == -1)
    {
        printf("Error : element not found");
        return;
    }
    else
    {
        if (index == top)
        {
            array[index] = -1;
            top--;
        }
        else
        {
            while (index == top - 1)
            {
                int temp = array[index];
                array[index] = array[index + 1];
                array[index + 1] = temp;
                index++;
            }
            array[top] = -1;
            top--;
        }
        if ((ArraySize - top - 1) == (top + 1))
        {
            ArraySize = ArraySize / 2;
        }
        printArray();
    }
}
int main()
{
    initArray();
    push(1);
    push(2);
    push(3);
    push(4);
    push(5);
    del(4);
    push(3);
    push(4);
    push(5);
    push(6);
    push(8);
    return 0;
}