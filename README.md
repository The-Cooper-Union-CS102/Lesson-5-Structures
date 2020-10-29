# Structures

Structures are a C concept that you can use to organize your data.  In all
of our previous examples, we usually passed two related pieces of data as
two separate units into a function.  For example, whenever we had to process
an array, we also passed it's length.  When we wanted to find a Pythagorean
triple, we passed three different ints separately.  You can imagine other
cases where this becomes excessive, for example, when storing information
about a person or a user of a system, we would naturally want sone way
of grouping the related information.  This is where structures come into
play.

## Structure Syntax

A structure is defined with the following syntax:

```
struct STRUCT_TAG {
    TYPE_1 MEMBER_1;
    TYPE_2 MEMBER_2;
    ...
    TYPE_N MEMBER_N;
};
```

The text following `struct` is called the *structure tag* which can be used
to reference it later.  The text following types within the braces are
called *members*.  Let's take a look at a simple example, creating a
structure that represents a simple two dimensional point.

```c
// snippets/simpleStruct.c
#include <stdio.h>

struct Point {
    int x;
    int y;
};

int main() {
    return 0;
}
```


```
```


A variable of structure type can be declared and initialized similar to
an array:

```
struct STRUCT_TAG VAR_NAME = {MEMBER_1, MEMBER_2, ... MEMBER_N};
```

which is demonstrated in the following code.

```c
// snippets/declareStruct.c
#include <stdio.h>

struct Point {
    int x;
    int y;
};

int main() {
    struct Point pt = {3, 4};
}
```


```
```


To access the values of the members of a struct, you can use the *structure
member operator*, also called the *dot operator*.

```
TYPE_1 VAR = STRUCT_VAR.MEMBER_1;
```

This is demonstrated in the following code.

```c
// snippets/accessStruct.c
#include <stdio.h>

struct Point {
    int x;
    int y;
};

int main() {
    struct Point pt = {3, 4};
    printf("(%d, %d)\n", pt.x, pt.y);
}
```


```
(3, 4)
```


One very useful property of structs is that you can compose them as many
times as you want.  That is, the members of a struct can be structs themselves.
This is demonstrated below, where we create a line struct from two points,
and access the individual members by using the member operator twice.

### Problem

How can we define a structure representing a circle?

## Structures And Functions

Structures interact with functions in basically the same way that regular
variables do.  They can be regular arguments, and return values from functions,
and they can also be initialized from a function call.  First, let's create
a function that can initialize a point.

```c
// snippets/functionStruct.c
#include <stdio.h>

struct Point {
    int x;
    int y;
};

struct Point makePoint(int x, int y) {
    struct Point p;
    p.x = x;
    p.y = y;
    return p;
}

int main() {
    struct Point pt = makePoint(3, 4);
    printf("(%d, %d)\n", pt.x, pt.y);
}
```


```
(3, 4)
```


You can see it pretty much works as expected.  Note however that this
method of creating a new struct allows the programmer to enter some common
boilerplate code into the creation of the struct.

Now we show some code demonstrating the use of a struct as an argument by
adding two points together.

```c
// snippets/argumentStruct.c
#include <stdio.h>

struct Point {
    int x;
    int y;
};

struct Point makePoint(int x, int y) {
    struct Point p;
    p.x = x;
    p.y = y;
    return p;
}

struct Point addPoints(struct Point p1, struct Point p2) {
    struct Point p;
    p.x = p1.x + p2.x;
    p.y = p1.y + p2.y;
    return p;
}

int main() {
    struct Point p1 = makePoint(3, 4);
    struct Point p2 = makePoint(4, 5);
    struct Point pt = addPoints(p1, p2);
    printf("(%d, %d)\n", pt.x, pt.y);
}
```


```
(7, 9)
```


Now, just as we went over pointers for regular variables in the last session,
so too can you have pointers to structs.  In fact, if you have a large struct
containing many members, it can be much more efficient to pass a pointer to
that struct rather the struct itself.  Let's look at the simple example of
using a struct pointer to modify a point in place.

```c
// snippets/pointerStruct.c
#include <stdio.h>

struct Point {
    int x;
    int y;
};

void negatePoint(struct Point *p) {
    (*p).x = -(*p).x;
    (*p).y = -(*p).y;
}

int main() {
    struct Point pt = {3, 4};
    negatePoint(&pt);
    printf("(%d, %d)\n", pt.x, pt.y);
}
```


```
(-3, -4)
```


In this example, we first dereference the incoming struct pointer, then
access its member for both reading and writing.  If you think this syntax
is verbose, ugly, and in need of improvement, you are in good company.

In fact the creators of C thought the same, and so they added the *arrow
operator*, which is demonstrated below:

```c
// snippets/arrowStruct.c
#include <stdio.h>

struct Point {
    int x;
    int y;
};

void negatePoint(struct Point *p) {
    p->x = -p->x;
    p->y = -p->y;
}

int main() {
    struct Point pt = {3, 4};
    negatePoint(&pt);
    printf("(%d, %d)\n", pt.x, pt.y);
}
```


```
(-3, -4)
```


This code is exactly equivalent to the last example, but a lot simpler and
easy to read.  This can be especially useful when dealing with structs that
contain pointers to other structs, in which case the operator can be
applied twice.

### Problem

Make a sized array structure, along with functions to zero it out, find its
average via a pointer to it.

## Arrays of Structures

There are two possible methods of handling a large number of related data.
Consider tracking a group of students, their name and their grade.  One
could store an array of names and an array of grades.  However this may
not be ideal since it requires the programmer to keep track of their order
and ensure that they always match.  An alternative method would be to put
the name and grade in a structure, and then create an array of structs.  This
method is demonstrated below.

```c
// snippets/arrayOfStruct.c
#include <stdio.h>

struct Student {
    char *name;
    int grade;
};

int main() {
    struct Student students[] = {
        {"Ross", 90},
        {"Cory", 65},
        {"Gordon", 80},
        {"Deborah", 100},
    };
    printf("%s's grade: %d\n", students[0].name, students[0].grade);
}
```


```
Ross's grade: 90
```


Note that the extra curly braces we use to mark the start and end of the
structure elements are not actually necessary, and their inclusion it a matter
of style.

```c
// snippets/arrayOfStructLoop.c
#include <stdio.h>

struct Student {
    char *name;
    int grade;
};

int main() {
    struct Student students[] = {
        {"Ross", 90},
        {"Cory", 80},
        {"Gordon", 80},
        {"Deborah", 100},
    };
    int n;
    int numStudents = sizeof(students) / sizeof(struct Student);
    for (n = 0; n < numStudents; n++) {
        printf("%s's grade: %d\n", students[n].name, students[n].grade);
    }
}
```


```
Ross's grade: 90
Cory's grade: 80
Gordon's grade: 80
Deborah's grade: 100
```


Note that here we also use a new unary operator called `sizeof`.  This operator
yields the size of the object in bytes.  In order to get the number of objects
in the array, we simply divide the size of the array by the size of the objects
that compose it.  Note that this cannot be used to get the size of an array
passed into a function, as that is really a pointer, not an array.

### Problem

How can we sort the array by name, or by grade?  How can we sort it by grade
and then names on a tie?

## Self-referential Structures

As we showed before, structures can reference other structures, and in fact
they can even reference themselves.  They cannot literally contain one
of themselves, but they can contain a pointer to one of themselves.  We
demonstrated this by creating a "Node" struct which contains a pointer
to a node struct.

```c
// snippets/selfReference.c
#include <stdio.h>

struct Node {
    int value;
    struct Node *next;
};

int main() {
    struct Node n1 = {0, NULL};
    struct Node n2 = {0, &n1};
}
```


```
```


Now consider a seemingly simple request.  Take a user input of words separated
by spaces and create a node for each one, linking them together.  With what
we have seen so far, it is only possible to create a fixed number of nodes
each of which must be declared explicitly.  This precludes us from doing
anything based on the user input as it may be of variable length.  This
brings us to an important built in C function.

## Memory Allocation

### `malloc`

In order to create objects based on user input, we need to do something called
"dynamically allocating memory".  This means that for once, the amount of space
we are going to use in a program is not known when we compile it.  This can
be achieved by using a built in C function called `malloc` (which is short for
*allocate memory*).  This function reserves a given amount of bytes for us, and
returns a void pointer to that location.  Let's look at a simpe example of
using `malloc` to create a single Node.

```c
// snippets/basicMalloc.c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node *next;
    char *str;
};

int main() {
    struct Node *np = (struct Node *) malloc(sizeof(struct Node));
    np->str = "Hello";
    np->next = NULL;
    printf("(%p, %s)\n", np->next, np->str);
}
```


```
(0x0, Hello)
```


Working from left to right of the malloc statement:
1. We are creating a pointer to a node
2. Because `malloc` returns a void pointer, we must cast as a node pointer
3. We specify the amount of bytes we want is the size of a node.

Beause we have a pointer to a node, we use the arrow operator to set its
members.  Note that we initialize the `next` pointer to `NULL` to signal
that there is no next node.  Otherwise, later code may try to dereference
this next node and cause an error.

Now, let's take a look at a more complex case: creating a node for each user
input, and linking them together.

```c
// snippets/storeInput.c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node *next;
    char *str;
};

int main(int argc, char *argv[]) {
    struct Node n = {NULL, ""};
    struct Node *sp = &n; // Starting pointer
    struct Node *cp = &n; // Current pointer
    int i;
    for (i = 1; i < argc; i++) {
        // Initialize new Node
        struct Node *new = (struct Node *) malloc(sizeof(struct Node));
        new->str = argv[i];
        new->next = NULL;
        // Set current pointer to next node
        cp->next = new;
        cp = cp->next;
    }
    // Print Nodes in order
    cp = sp;
    while (cp->next) {
        printf("(%p, %s)->", cp->next->next, cp->next->str);
        cp = cp->next;
    }
    printf("\n");
}
```


```

```


Now this code might be very hard to understand, and very intimidating to a
beginner, so let's go through it in detail.

1. Create an initial "root" node with no data.
2. Store a "start" pointer to the root so we can always find it.
3. Store a "current" pointer for the node we are looking at.
4. Loop over all user inputs
    1. Create a new node
    2. Store the text in the "new" node
    3. Store a null pointer in the "new" node
    4. Set the "next" of the "current" node to the "new" node
    5. Set the "current" node to the "new" node.
5. Reset the "current" pointer to the "start" pointer.
6. While the "current" pointer has a valid "next" pointer:
    1. Print the contents of the "next" pointer.
    2. Set the "current" pointer to the "next" pointer.

### `free`

Now, it's not obvious that we did something wrong in the last example, lets
think about it.  We asked our computer for a bunch of memory in which we can
store our nodes.  We asked for it, and we never gave it back.  We could
potentially keep asking for it over and over until our computer runs out of
memory or just refuses to give us more.  This will happen naturally if a
program which dynamically requests memory keeps running.

We can give the memory back to the computer with the `free` function.  The
`free` function is quite simple: it takes a pointer and returns nothing.  But
it has actually given all the memory we took for that particular pointer and
freed it, meaning it has given it back to the computer to use for other programs.
If you use `malloc` without a corresponding `free` that is called a **memory leak**
and that is typically very bad.

let's take a look at a simple example of using this.

```c
// snippets/free.c
#include <stdlib.h>
#include <stdio.h>

int main() {
    int *a = malloc(sizeof(int) * 8);
    a[7] = 5;
    printf("%d\n", a[7]);
    free(a); // 'a' is now a "Dangling Pointer"
    printf("%d\n", a[7]); // Anything could happen
    free(NULL); // Freeing a NULL pointer does nothing
}
```

### `realloc`

It is also a common operation to extend the amount of space you need.  One
simple way of achieving this would be to `malloc` a new larger size, then
copy all the contents of your smaller array into that, then free the original
array, and reset the original pointer to point to the new array.  However, 
this is a common enough operation that there is a built in function, `realloc`.

The `realloc` function finds enough space for your new size and copies over all
of your old stuff for you.  Here is an example:

```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    int *a = malloc(sizeof(int) * 8);
    a[7] = 5;
    a = realloc(a, sizeof(int) * 16);
    printf("%d\n", a[7]);
    a[15] = 15;
    printf("%d\n", a[15]);
}
```


## Typedef

You may notice that the use of structures can become verbose since you always
have to type `struct` before using one.  One simple way to remedy this is
to use the built in `typedef` keyword.  A simple example given below uses
`typedef` to define a `String` as `char *`

```c
// snippets/basicTypedef.c
#include <stdio.h>
#include <stdlib.h>

typedef char *String;

struct Node {
    struct Node *next;
    String str;
};

int main() {
    struct Node *np = (struct Node *) malloc(sizeof(struct Node));
    np->str = "Hello";
    np->next = NULL;
    printf("(%p, %s)\n", np->next, np->str);
}
```


```
(0x0, Hello)
```


As mentioned however, this can also be applied to structs as demonstrated
below.

```c
// snippets/basicTypedef.c
#include <stdio.h>
#include <stdlib.h>

typedef char *String;

struct Node {
    struct Node *next;
    String str;
};

int main() {
    struct Node *np = (struct Node *) malloc(sizeof(struct Node));
    np->str = "Hello";
    np->next = NULL;
    printf("(%p, %s)\n", np->next, np->str);
}
```


```
(0x0, Hello)
```


You can see the code is quite a bit simpler.  Note that `typedef` does not
actually create a new type, but essentially only serves as another name for
an existing type.

## Unions

Sometimes you have need for a variable which can take on one of several types.
For instance, you might want to handle either integers or floating point
numbers in numeric algorithms.  Unions are almost the same as a struct,
except that instead of holding all of the types given, they hold one of them
at a given time.  They have similar syntax as well, which is demonstrated
below.

```c
// snippets/basicUnion.c
#include <stdio.h>
#include <stdlib.h>

typedef union Number {
    int intVal;
    double doubleVal;
} Number;

Number timesTwo(Number n, int type) {
    Number m;
    if (type == 0) {
        m.intVal = 2*n.intVal;
    } else {
        m.doubleVal = 2*n.doubleVal;
    }
    return m;
}

int main() {
    Number n;
    Number m;
    n.intVal = 7;
    m = timesTwo(n, 0);
    printf("%d\n", m.intVal);
}
```


```
14
```


Note that this code still has the drawback that we have to communicate the
type that we want to process as an argument.  You can work around this issue
by including the type stored in the union as well as the union itself in
the same structure, as below.

```c
// snippets/structUnion.c
#include <stdio.h>
#include <stdlib.h>

typedef struct Number {
    int type;
    union {
        int intVal;
        double doubleVal;
    } vals;
} Number;

Number timesTwo(Number n) {
    Number m;
    m.type = n.type;
    if (n.type == 0) {
        m.vals.intVal = 2*n.vals.intVal;
    } else {
        m.vals.doubleVal = 2*n.vals.doubleVal;
    }
    return m;
}

int main() {
    Number n;
    Number m;
    n.type = 0;
    n.vals.intVal = 7;
    m = timesTwo(n);
    printf("%d\n", m.vals.intVal);
}
```


```
14
```

# Algorithms

As of this session, we have seen almost everything C has to offer!  It might
be hard to imagine, but with the tools we have been given, it is possible
to write any algorithm.  Yes, any algorithm you could possibly imagine can
be written with the tools we have learned.  Now it's just a matter of good
thinking and organization.  In this session we will go over some well known
data structures and algorithms.

## Linked List

We motivate our discussion with the problem: Given two very large numbers
as an input, print their sum.  We will assume the numbers are too large to
fit into any of the predefined classes of integer and therefore we will need
a new way of storing them.  There might be better ways, but as one of the
simpler solutions, we will store a number as a linked list, each node
representing one digit.  We can re-use some of our code from the previous
session.

```c
// snippets/linkedList.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct Node {
    struct Node *next;
    int digit;
} Node;

Node *makeNode(Node *np, int digit) {
    Node *newPtr = (Node *) malloc(sizeof(Node));
    newPtr->next = np;
    newPtr->digit = digit;
    return newPtr;
}

int len(Node *np) {
    int n = 0;
    while (np) {
        n += 1;
        np = np->next;
    }
    return n;
}

Node *add(Node *a, Node *b) {
    int carry = (a->digit + b->digit) > 9;
    int value = (a->digit + b->digit) % 10;
    Node *rs = makeNode(NULL, value);
    Node *r = rs;
    Node z = {NULL, 0};
    Node *zp = &z;
    while (a->next || b->next || carry) {
        a = (a->next) ? a->next : zp;
        b = (b->next) ? b->next : zp;
        r->next = makeNode(NULL, (a->digit + b->digit + carry) % 10);
        carry = (a->digit + b->digit + carry) > 9;
        r = r->next;
    }
    return rs;
}

void printList(Node *np) {
    int index = len(np);
    char c[index+1];
    for (int n = 0; n < index+1; n++) {
        c[n] = '\0';
    }
    while (np) {
        c[--index] = np->digit + '0';
        np = np->next;
    }
    printf("%s\n", c);
}

Node *fromString(char *string) {
    int len = strlen(string);
    Node *sp = makeNode(NULL, string[len-1] - '0');
    Node *np = sp;
    for (int i = len - 2; i >= 0; i--) {
        np->next = makeNode(NULL, string[i] - '0');
        np = np->next;
    }
    return sp;
}

int main(int argc, char *argv[]) {
    assert(argc == 3);
    Node *ap = fromString(argv[1]);
    Node *bp = fromString(argv[2]);
    printList(ap);
    printList(bp);
    Node *sum = add(ap, bp);
    printList(sum);
}
```


```
```


Some questions:
* What are some flaws, or things missing in this code?
* What other functions could we add?

## Stack

We motivate our discussion with the problem: Given a string of mixed
parentheses, determine if it's balanced.  For example, `(){[]}` is balanced,
while `[(])` is not.

```c
// snippets/stack.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct Node {
    struct Node *next;
    char symbol;
} Node;

typedef struct Stack {
    Node *sentinel;
    Node *top;
} Stack;

Stack *makeStack() {
    Stack *sp = (Stack *) malloc(sizeof(Stack));
    Node *np = (Node *) malloc(sizeof(Node));
    np->next = NULL;
    np->symbol = '!';
    sp->sentinel = np;
    sp->top = np;
    return sp;
}

void push(Stack *sp, char c) {
    // Initialize new Node
    Node *np = (Node *) malloc(sizeof(Node));
    np->next = sp->top;
    np->symbol = c;
    // Add it to the Stack
    sp->top = np;
}

char pop(Stack *sp) {
    char c = sp->top->symbol;
    free(sp->top);
    sp->top = sp->top->next;
    return c;
}

int empty(const Stack *sp) {
    return (sp->top->next == NULL);
}

void printNode(Node *n) {
    printf("(%p, '%c')\n", n->next, n->symbol);
}

void printStack(const Stack *sp) {
    printf("---Stack Start---\n");
    Node *np = sp->top;
    while (np->next) {
        printNode(np);
        np = np->next;
    }
    printf("---Stack End---\n");
}

void freeStack(Stack *sp) {
    Node *np = sp->top;
    Node *tnp = np;
    while (np) {
        tnp = np->next;
        free(np);
        np = tnp;
    }
    free(sp);
}

int balanced(const char *str) {
    Stack *sp = makeStack();
    char c;
    for (; (c = *str); str++) {
        if (c == '(' || c == '[') {
            push(sp, c);
        }
        if (c == ')') {
            if (sp->top->symbol == '(') {
                pop(sp);
            } else {
                push(sp, c);
            }
        }
        if (c == ']') {
            if (sp->top->symbol == '[') {
                pop(sp);
            } else {
                push(sp, c);
            }
        }
    }
    int retval = empty(sp);
    freeStack(sp);
    return retval;
}

int main() {
    assert(balanced("()())") == 0);
    assert(balanced("(a)b") == 1);
    assert(balanced("(ab") == 0);
    assert(balanced("[(])") == 0);
    assert(balanced("[]()") == 1);
    assert(balanced("[a(cd)b]-(f{h}g)") == 1);
    assert(balanced("[a(cd)b]-[(f{h}g)") == 0);
}
```


```
```


## Binary Search Tree

We motivate our discussion with a simple problem.  How can we determine if
an array of strings contains a duplicate?  For example, 

`{"cat", "dog", "cat"}` contains a duplicate, while `{"cat", "dog", "bat"}`
does not.  One simple solution would be create a double for loop over the array
and simply check if any pair of words contains the same word.  However this
is very slow for long lists.  (In fact the running time is roughly proportional
to the square of the list length)

```c
// snippets/binarySearchTree.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAXLEN 256
#define MAXWORDS 100000

char *lines[MAXWORDS];

typedef struct BstNode {
    char *string;
    struct BstNode *less;
    struct BstNode *more;
} BstNode;

BstNode *makeBstNode(char *string) {
    BstNode *np = (BstNode *) malloc(sizeof(BstNode));
    np->less = NULL;
    np->more = NULL;
    np->string = string;
    return np;
}

void insert(BstNode *np, char *string) {
    int cmp = strcmp(string, np->string);
    if (cmp < 0) { // string < np->string
        if (np->less == NULL) {
            BstNode *new = makeBstNode(string);
            np->less = new;
        } else {
            insert(np->less, string);
        }
    } else if (cmp > 0) { // string > np->string
        if (np->more == NULL) {
            BstNode *new = makeBstNode(string);
            np->more = new;
        } else {
            insert(np->more, string);
        }
    }
}

int contains(BstNode *np, char *string) {
    int cmp = strcmp(string, np->string);
    if (cmp == 0) {
        return 1;
    }
    BstNode *nextNode = (cmp < 0) ? np->less : np->more;
    if (nextNode == NULL) {
        return 0;
    } else {
        return contains(nextNode, string);
    }
}

int naiveDupCheck(char *a[], int len) {
    int m, n;
    for (m = 0; m < len; m++) {
        for (n = m+1; n < len; n++) {
            if (strcmp(a[m], a[n]) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int dupCheck(char *a[], int len) {
    BstNode *bstp = makeBstNode(a[0]);
    int n;
    for (n = 1; n < len; n++) {
        if (contains(bstp, a[n])) {
            return 1;
        }
        insert(bstp, a[n]);
    }
    return 0;
}

int loadLines(char *filename) {
    int lineno = 0;
    char line[MAXLEN];
    FILE *fp = fopen(filename, "r");
    printf("Starting loading in words...\n");
    while (fgets(line, MAXLEN, fp) > 0) {
        int len = strlen(line);
        assert(line[len-1] == '\n' && "Input too long!");
        line[len-1] = '\0'; // Strip newline
        char *newline = (char *) malloc(sizeof(char) * len);
        strcpy(newline, line);
        lines[lineno] = newline;
        lineno += 1;
    }
    return lineno;
}

int main(int argc, char *argv[]) {
    int argnum = 1;
    int useFast = 0;
    char *filename;
    while (argnum < argc) {
        if (strcmp(argv[argnum], "--fast") == 0) {
            useFast = 1;
        }
        if (strcmp(argv[argnum], "-i") == 0) {
            argnum += 1;
            filename = argv[argnum];
        }
        argnum += 1;
    }
    assert(filename && "Filename must be provided with -i");
    int lineno = loadLines(filename);
    printf("Done loading in words...\n");
    if (useFast) {
        printf("Starting fast duplicate check...\n");
        printf("Duplicate? %d\n", dupCheck(lines, lineno));
    } else {
        printf("Starting naive duplicate check...\n");
        printf("Duplicate? %d\n", naiveDupCheck(lines, lineno));
    }
}
```


```
```


Some questions:
* What are some flaws, or things missing in this code?
* What other functions could we add?
* What is the expected run time for the contains function?
* What happens when we feed an ordered list of strings in?
* How might we generalize this data structure to more than just strings?

We can go a little bit further with the binary search tree, and store values
along with the keys.  For example consider the problem of counting the number
of occurences of a string in an array.

```c
// snippets/binarySearchTreeMap.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAXLEN 256
#define MAXLINES 100000

char *USERNAMES[MAXLINES];

typedef struct BstNode {
    char *key;
    int *value;
    struct BstNode *less;
    struct BstNode *more;
} BstNode;

BstNode *makeBstNode(char *key, int value) {
    BstNode *np = (BstNode *) malloc(sizeof(BstNode));
    np->less = NULL;
    np->more = NULL;
    np->key = key;
    np->value = (int *) malloc(sizeof(int));
    *(np->value) = value;
    return np;
}

void insert(BstNode *np, char *key, int value) {
    int cmp = strcmp(key, np->key);
    if (cmp < 0) { // key < np->key
        if (np->less == NULL) {
            BstNode *new = makeBstNode(key, value);
            np->less = new;
        } else {
            insert(np->less, key, value);
        }
    } else if (cmp > 0) { // key > np->key
        if (np->more == NULL) {
            BstNode *new = makeBstNode(key, value);
            np->more = new;
        } else {
            insert(np->more, key, value);
        }
    }
}

void print(BstNode *np) {
    if (np) {
        print(np->less);
        printf("%s: %d\n", np->key, *np->value);
        print(np->more);
    }
}

int *get(BstNode *np, char *key) {
    int cmp = strcmp(key, np->key);
    if (cmp == 0) {
        return np->value;
    }
    BstNode *nextNode = (cmp < 0) ? np->less : np->more;
    if (nextNode == NULL) {
        return NULL;
    } else {
        return get(nextNode, key);
    }
}

int loadUsernames(char *filename) {
    int lineno = 0;
    char line[MAXLEN];
    char* username;
    FILE *fp = fopen(filename, "r");
    while (fgets(line, MAXLEN, fp) > 0) {
        int len = strlen(line);
        assert(line[len-1] == '\n' && "Input too long!");
        line[len-1] = '\0'; // Strip newline
        username = (char *) malloc(sizeof(char) * len);
        strcpy(username, line);
        USERNAMES[lineno] = username;
        lineno += 1;
    }
    return lineno;
}

void printCount(char *strings[], int len) {
    int count = 0;
    BstNode *root = makeBstNode(strings[0], 1);
    for (int n = 1; n < len; n++) {
        char *string = strings[n];
        int *got;
        if ((got = get(root, string))) {
            (*got) += 1;
        } else {
            insert(root, string, 1);
        }
    }
    print(root);
}

int main(int argc, char *argv[]) {
    int argnum = 1;
    int useFast = 0;
    char *databaseFilename;
    char *usersFilename;
    while (argnum < argc) {
        if (strcmp(argv[argnum], "--fast") == 0) {
            useFast = 1;
        }
        if (strcmp(argv[argnum], "-u") == 0) {
            argnum += 1;
            usersFilename = argv[argnum];
        }
        argnum += 1;
    }
    assert(usersFilename && "users must be provided with -u");
    int lineno = loadUsernames(usersFilename);
    printf("Loaded %d lines.\n", lineno);
    printCount(USERNAMES, lineno);
    printf("Done loading in words...\n");
}
```


```
```

