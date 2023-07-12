#include "tree.h"

Tree* createTree(Symbol value) {
    Tree* newTree = (Tree*)malloc(sizeof(Tree));
    newTree->value = value;
    newTree->parent = NULL;
    newTree->left = NULL;
    newTree->right = NULL;
    return newTree;
}

char oppToChar(Operator op) {
    switch(op) {
        case OP_MINUS:
        case OP_PLUS:
        case OP_MULTIPLY:
        case OP_DIVIDE:
        case OP_POW:
            return op;
        case OP_UNARY_MINUS:
            return '-';
    }
    return -1;
}

void printTree(Tree* tree, int lvl){
    if(tree->value.type == symb_OP) {
        printTree(tree->right, lvl + 1);
    }
    for (int i = 0; i < lvl; i++) {
        printf("\t");
    }
    switch(tree->value.type) {
        case symb_NUMBER:
            printf("%.2lf\n", tree->value.data.number);
            break;
        case symb_VAR:
            if(tree->value.data.op == '-'){
                printf("-\n");
                printTree(tree->right, lvl + 1);
            } else {
                printf("%c\n", tree->value.data.c);
            }
            break;
        case symb_OP:
            if(tree->value.data.op == OP_UNARY_MINUS) {
                printf("-\n");
                printTree(tree->right, lvl + 1);
            } else {
                printf("%c\n", oppToChar(tree->value.data.op));
            }
            break;
        default:
            fprintf(stderr, "Error");
            return;
    }
    if (tree->value.type == symb_OP) {
        printTree(tree->left, lvl + 1);
    }
}

Tree* newNode(Tree* t, Symbol value) {
    if (t == NULL) {
        return createTree(value);
    } 
    if (value.data.c < t->value.data.c) {
        t->left = newNode(t->left, value);
    } else if (value.data.c > t->value.data.c) {
        t->right = newNode(t->right, value);
    }
    return t;
}

void clearTree(Tree* tree) {
    if (tree == NULL) {
        return;
    }
    clearTree(tree->left);
    clearTree(tree->right);
    free(tree);
}

void initStack(stack* s) {
    s->top = NULL;
    s->size = 0;
}

bool stackEmpty(stack* s) {
    return s->size == 0;
}

int stackSize(stack* s) {
    return s->size;
}

void stackPushTree(stack* s, Tree* value) {
    stackNode* tmp = malloc(sizeof(stackNode));
    tmp->type = TREE;
    tmp->value.treeValue = value;
    tmp->prev = s->top;
    s->top = tmp;
    s->size++;
}

void stackPushSymbol(stack* s, Symbol value) {
    stackNode* tmp = malloc(sizeof(stackNode));
    tmp->type = SYMBOL;
    tmp->value.symbolValue = value;
    tmp->prev = s->top;
    s->top = tmp;
    s->size++;
}

Tree* stackPopTree(stack* s) {
    if (stackSize(s) == 0) {
        printf("Error\n");
        return NULL;
    }
    stackNode* tmp = s->top;
    Tree* result = tmp->value.treeValue;
    s->top = s->top->prev;
    free(tmp);
    s->size--;
    return result;
}

Symbol stackPopSymbol(stack* s) {
    if (stackSize(s) == 0) {
        printf("Error\n");
        Symbol emptySymbol;
        emptySymbol.type = symb_NONE;
        emptySymbol.data.c = '\0';
        return emptySymbol;
    }
    stackNode* tmp = s->top;
    Symbol result = tmp->value.symbolValue;
    s->top = s->top->prev;
    free(tmp);
    s->size--;
    return result;
}

void stackDestroy(stack* s) {
    while (!stackEmpty(s)) {
        stackNode* current = s->top;
        s->top = s->top->prev;
        free(current);
    }
    free(s);
}

Tree* stackTopTree(stack* s) {
    if (stackSize(s) == 0) {
        printf("Error\n");
        return NULL;
    }
    return s->top->value.treeValue;
}

Symbol stackTopSymbol(stack* s) {
    if (stackSize(s) == 0) {
        printf("Error\n");
        Symbol emptySymbol;
        emptySymbol.type = symb_NONE;
        emptySymbol.data.c = '\0';
        return emptySymbol;
    }
    return s->top->value.symbolValue;
}

void pushFront(node** head, Symbol data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = *head;
    newNode->prev = NULL;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void pushBack(node** head, Symbol data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    if (*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }
    node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
}

void deleteBack(node* head) {
    if (head == NULL) {
        printf("Error\n");
        return;
    }
    if (head->next == NULL) {
        free(head);
        head = NULL;
        return;
    }
    node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->prev->next = NULL;
    free(current);
}

void deleteFront(node* head) {
    if (head == NULL) {
        printf("Список пуст!\n");
        return;
    }
    node* temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    free(temp);
}

void printList(node* head) {
    node* current = head;
    while (current != NULL) {
        printf("%c ", current->data.data.c);
        current = current->next;
    }
    printf("\n");
}

void destroy(node* head) {
    node* current = head;
    while (current != NULL) {
        node* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}

int sizeList(node* head) {
    int count = 0;
    node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '*' || ch == '/' || ch == '^');
}

int getPriority(char ch) {
    if (ch == '*' || ch == '/')
        return 2;
    else if (ch == '+' || ch == '-')
        return 1;
    else
        return 0;
}

OperatorAssoc op_assoc(char op) {
    if (op == '+' || op == '-' || op == '*' || op == '/')
        return ASSOC_LEFT;
    else
        return ASSOC_RIGHT;
}

void next_symbol(Symbol* symbol, char input[]) {
    static int index = 0;
    char c = input[index];
    static SymbolType prev = symb_NONE;
    if (c == '\0') {
        symbol->type = symb_NONE;
        prev = symb_NONE;
        return;
    }
    if (isdigit(c)) {
        symbol->type = symb_NUMBER;
        symbol->data.number = c - '0';
        index++;
        while (isdigit(input[index])) {
            symbol->data.number = symbol->data.number * 10 + (input[index] - '0');
            index++;
        }
    } else if (isOperator(c)) {
        symbol->type = symb_OP;
        symbol->data.op = c;
        index++;
    } else if (isalpha(c)) {
        symbol->type = symb_VAR;
        symbol->data.c = c;
        index++;
    } else if (c == '(') {
        symbol->type = symb_LEFT_BR;
        symbol->data.c = c;
        index++;
    } else if (c == ')') {
        symbol->type = symb_RIGHT_BR;
        symbol->data.c = c;
        index++;
    } else if (c == '-') {
        symbol->type = symb_OP;
        if (prev == symb_OP || prev == symb_NONE) {
            symbol->data.op = OP_UNARY_MINUS;
        } else {
            symbol->data.op = OP_MINUS;
        }
        index++;
    } else {
        symbol->type = symb_NONE;
        index++;
    }
    prev = symbol->type;
}

void infixToPostfix(char exp[], node** expression) {
    stack* s = malloc(sizeof(stack));
    initStack(s);
    Symbol t;
    next_symbol(&t, exp);
    while (t.type != symb_NONE) {
        switch (t.type) {
            case symb_NONE:
                fprintf(stderr, "Error\n");
                return;

            case symb_OP:
                for (;;) {
                    if (stackEmpty(s))
                        break;
                    Symbol top = stackTopSymbol(s);
                    if (top.type != symb_OP)
                        break;

                    if ((op_assoc(t.data.op) == ASSOC_LEFT && getPriority(t.data.op) <= getPriority(top.data.op)) ||
                        (op_assoc(t.data.op) == ASSOC_RIGHT && getPriority(t.data.op) < getPriority(top.data.op))) {
                        pushBack(expression, top);
                        stackPopSymbol(s);
                    } else {
                        break;
                    }
                }
                stackPushSymbol(s, t);
                break;
            case symb_NUMBER:
            case symb_VAR:
                pushBack(expression, t);
                break;
            case symb_LEFT_BR:
                stackPushSymbol(s, t);
                break;
            case symb_RIGHT_BR:
                while (!stackEmpty(s) && stackTopSymbol(s).type != symb_LEFT_BR) {
                    pushBack(expression, stackPopSymbol(s));
                }
                if (stackEmpty(s)) {
                    fprintf(stderr, "Error\n");
                    return;
                }
                stackPopSymbol(s);
                break;
        }
        next_symbol(&t, exp);
    }

    while (!stackEmpty(s)) {
        if (stackTopSymbol(s).type == symb_LEFT_BR) {
            fprintf(stderr, "Error\n");
            return;
        }
        pushBack(expression, stackPopSymbol(s));
    }
    stackDestroy(s);
}

Tree* postfixToTree(node* postfix) {
    stack* s = malloc(sizeof(stack));
    initStack(s);
    for(node* current = postfix; current != NULL; current = current->next) {
        Symbol c = current->data;
        if (c.type != symb_OP) {
            Tree* tmp = createTree(c);
            stackPushTree(s, tmp);
        } else if (c.type == symb_OP) {
            Tree* right = stackPopTree(s);
            Tree* left = stackPopTree(s);
            Tree* op = createTree(c);
            op->left = left;
            op->right = right;
            stackPushTree(s, op);
        }
    }
    Tree* res = stackPopTree(s);
    stackDestroy(s);
    return res;
}

void simplifyFraction(Tree* node) {
    if (node == NULL)
        return;
    simplifyFraction(node->left);
    simplifyFraction(node->right);
    if (node->value.type == symb_OP && node->value.data.op == OP_DIVIDE) {
        Tree* numerator = node->left;
        Tree* denominator = node->right;
        if (denominator->value.data.op == OP_DIVIDE && numerator->value.data.op != OP_DIVIDE) {
            node->value.data.op = OP_MULTIPLY;
            node->right = denominator->right;
            node->left = denominator;
            denominator->right = denominator->left;
            denominator->left = numerator;
        } else if (numerator->value.data.op == OP_DIVIDE && denominator->value.data.op != OP_DIVIDE) {
            node->right = numerator;
            node->left = denominator;
            node->left = numerator->left;
            numerator->left = denominator;
            node->right->value.data.op = OP_MULTIPLY;
        } else if (denominator->value.data.op == OP_DIVIDE && numerator->value.data.op == OP_DIVIDE) {
            denominator->value.data.op = OP_MULTIPLY;
            Tree* rightRight = denominator->right;
            Tree* leftRight = numerator->right;
            denominator->right = leftRight;
            numerator->right = rightRight;
        }
    }
}

void treeToPostfix(Tree* node, char postfixExp[]) {
    if (node == NULL)
        return;
    treeToPostfix(node->left, postfixExp);
    treeToPostfix(node->right, postfixExp);
    if (node->value.type == symb_NUMBER || node->value.type == symb_VAR) {
        char str[2] = {node->value.data.c, '\0'};
        strcat(postfixExp, str);
        strcat(postfixExp, " ");
    } else if (node->value.type == symb_OP) {
        char str[2] = {node->value.data.op, '\0'};
        strcat(postfixExp, " ");
        strcat(postfixExp, str);
        strcat(postfixExp, " ");
    }
}

void treeToExpresion(Tree* tree) {
    switch (tree->value.type) {
        case symb_NUMBER:
            printf("%.2lf", tree->value.data.number);
            break;
        case symb_VAR:
            printf("%c", tree->value.data.c);
            break;
        case symb_OP:
            if (tree->value.data.op == OP_UNARY_MINUS) {
                printf("-");
                treeToExpresion(tree->right);
            } else {
                bool addParenthesesLeft = (tree->left->value.type == symb_OP && getPriority(tree->value.data.op) > getPriority(tree->left->value.data.op));
                bool addParenthesesRight = (tree->right->value.type == symb_OP && getPriority(tree->value.data.op) > getPriority(tree->right->value.data.op));
                if (tree->value.data.op == OP_DIVIDE && !addParenthesesLeft && !addParenthesesRight) {
                    addParenthesesLeft = (tree->left->value.type == symb_OP);
                    addParenthesesRight = (tree->right->value.type == symb_OP);
                }
                if (addParenthesesLeft) {
                    printf("(");
                }
                treeToExpresion(tree->left);
                if (addParenthesesLeft) {
                    printf(")");
                }
                printf("%c", oppToChar(tree->value.data.op));
                if (addParenthesesRight) {
                    printf("(");
                }
                treeToExpresion(tree->right);
                if (addParenthesesRight) {
                    printf(")");
                }
            }
            break;
        default:
            fprintf(stderr, "Error");
            return;
    }
}
