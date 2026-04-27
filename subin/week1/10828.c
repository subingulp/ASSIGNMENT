#include <stdio.h> // my own yappaaroo or study of her code
#include <stdlib.h>
#include <string.h>
// Memory is never "empty": When you declare int data[100];, 
// C just grabs a block of memory. That memory already has "leftover" numbers 
// in it from whatever program was using that RAM before (we call this "garbage values").
#define MAX_STACK_SIZE 100 //백준 문제에서는 10000으로 MAX 해야해서 10001으로 수정해야함
// 100으로 정의해서 overflow 발생 가능성이 큼. also we do 10001 just as a safety buffer to prevent off by one errors
typedef int element;

typedef struct { 
    element data[MAX_STACK_SIZE];
    int top;
} StackType; // stacktype is a box that holds the bookshelf(data)
//the bookmark that tells me where the last book is (top)
void init_stack(StackType* s) {
    s->top = -1; // if u set it to top = 0 pc thinks theres a piece of data
    //sitting on the 0 spot basically garbage data
}

int is_empty(StackType* s) {
    return (s->top == -1);
}

int is_full(StackType* s) {
    return (s->top == MAX_STACK_SIZE - 1);
}

void push(StackType* s, element item) {
    if (is_full(s)) return;
    s->data[++(s->top)] = item;
} // better to print error if the user pushes more than memory. ("stack overflow")

// int push(StackType* s, element item) {
//     if (is_full(s)) {
//         return 0; // 0 means "Fail"
//     }
//     s->data[++(s->top)] = item;
//     return 1; // 1 means "Success"
// } go to main

element pop(StackType* s) {
    if (is_empty(s)) return -1;
    return s->data[(s->top)--];
}

element peek(StackType* s) {
    if (is_empty(s)) return -1;
    return s->data[s->top];
}

int main(void)
{
    StackType s;
    init_stack(&s);

    int n;
    scanf_s("%d", &n);

    for (int i = 0; i < n; i++)
    {
        char user[10];
        scanf_s("%s", user); // scanf is the standard. scanf_s will likely result in compile error cuz its 
        // for ms specific security enhanced

        if (strcmp(user, "push") == 0)
        {
            int data;
            scanf_s("%d", &data);
            push(&s, data);
        }
//      if (strcmp(user, "push") == 0) {
//          int data;
//          scanf("%d", &data);
//          if (push(&s, data) == 0) {
//               printf("Error: Stack is full!\n");
//          }
//      }
        else if (strcmp(user, "pop") == 0)
        {
            printf("%d\n", pop(&s));
        }
        else if (strcmp(user, "top") == 0)
        {
            printf("%d\n", peek(&s));
        }
        else if (strcmp(user, "size") == 0)
        {
            printf("%d\n", s.top + 1);
        }
        else if (strcmp(user, "empty") == 0)
        {
            printf("%d\n", is_empty(&s));
        }
    }

    return 0;
}

// Is -> always faster than .?
// It's not that the symbol -> is faster than .. The speed comes from how the data is passed to the function.
// Passing with . (By Value): When you call is_full(s), C makes a copy of the entire stack. If your stack is huge (like 10,000 items), 
// the computer has to work hard to copy all 10,000 items into the function.
// Passing with -> (By Pointer): When you call is_full(&s), you are only passing an address (the "map"). 
// Whether your stack has 10 items or 10 million items, the address is always the same tiny size (8 bytes).
// The Verdict: In C, we almost always use pointers (->) for structs. It’s faster, uses less memory, 
// and allows the function to actually change the original data instead of just a copy.
