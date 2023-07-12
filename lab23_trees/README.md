# Отчёт по лабораторной работе №23 по курсу «Фундаментальная информатика»

<b>Студент группы:</b> <ins>М8О-108Б-22 Караев Тариел Жоомартбекович, № по списку 11</ins>

<b>Контакты e-mail:</b> <ins>idl76h@gmail.com</ins>

<b>Работа выполнена:</b> <ins>13.05.23</ins>

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Выходной контроль знаний с оценкой:</b> <ins>"отлично"</ins>

<b>Отчёт сдан</b> «13» <ins>мая</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins>5</ins>

<b>Подпись преподавателя:</b> ________________

## 1. Тема:
Динамические структуры данных. Обработка деревьев

## 2. Цель работы:
Составить программу на языке Си для построения и обработки дерева общего вида

## 3. Задание:
Проверить монотонность убывания ширины уровня дерева

## 4. Оборудование:
<b>Процессор:</b> 11th Gen Intel(R) Core(TM) i3-1115G4 @ 3.00GHz<br/>
<b>ОП:</b> 8 ГБ <br/>
<b>SSD:</b> 256 ГБ<br/>

## 5. Программное обеспечение:
<b>Операционная система семейства:</b> Windows 11 10.0.22000 <br/>
<b>Интерпретатор команд:</b> Powershell 5.1.22000.832 <br/>
<b>Система программирования:</b> gcc.exe (GCC) 10.3.0 <br/>
<b>Текстовый редактор:</b> Visual Studio Code версия 1.73.1 <br/>
<b>Местонахождение и имена файлов программ и данных на домашнем компьютере:</b> C:\Users\idl76> <br/>

## 6. Идея, метод, алгоритм решения задачи (в формах: словесной, псевдокода, графической [блок-схема, диаграмма, рисунок, таблица] или формальные спецификации с пред- и постусловиями):
Необходимо реализовать дерево общего вида на Си с основными функциями создания, вставки нового элемента и т. д. Также необходимо написать следующие более нестандартные функции:
- добавление нового узла
- текстовая визуализация дерева
- удаление узла
- проверка монотонности убывания ширины уровня дерева (вариант 11)

Отметим, что дерево общего вида представляет собой нелинейный список, где каждый узел имеет указатель на самого первого сына и левого, правого брата.
## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию]:
tree.h
~~~c
#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    struct TreeNode *parent, *leftBro, *rightBro, *son;
    int value;
};

typedef struct TreeNode TreeNode;

typedef struct {
    TreeNode *root;
    size_t size;
} Tree;

TreeNode *treeRoot(Tree *tree);
TreeNode *nodeParent(TreeNode *node);
TreeNode *nodeLeftBro(TreeNode *node);
TreeNode *nodeRightBro(TreeNode *node);
TreeNode *nodeLeftmostSon(TreeNode *node);

size_t treeSize(Tree *tree);

void treeCreate(Tree *tree);

bool treeInsert(Tree *tree, TreeNode *parent, int value);

void treeErase(Tree *tree, TreeNode *node);

void treePrintPreOrder(Tree *tree);

void treePrintPostOrder(Tree *tree);

int sonsCount(TreeNode *node);

bool IsMonotDecreasing(Tree *tree);

#endif
~~~

tree.c
~~~c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"
#include "stack.h"

size_t treeSize(Tree *tree) {
    return tree->size;
}

TreeNode *treeRoot(Tree *tree) {
    return tree->root;
}

TreeNode *nodeParent(TreeNode *node) {
    return node->parent;
}

TreeNode *nodeLeftBro(TreeNode *node) {
    return node->leftBro;
}

TreeNode *nodeRightBro(TreeNode *node) {
    return node->rightBro;
}

TreeNode *nodeLeftmostSon(TreeNode *node) {
    return node->son;
}

void treeCreate(Tree *tree) {
    tree->root = NULL;
    tree->size = 0;
}

bool treeInsert(Tree *tree, TreeNode *parent, int value) {
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
    if (node == NULL)
        return false;
    node->parent = parent;
    node->leftBro = NULL;
    node->son = NULL;
    node->value = value;
    if (parent != NULL) {
        node->rightBro = parent->son; 
        if (parent->son != NULL) {
            parent->son->leftBro = node;
        }
        parent->son = node;
    } else {
        node->rightBro = NULL;
        tree->root = node;
    }
    ++tree->size;
    return true;
}

static size_t nodeDelete(TreeNode *node) {
    size_t count = 1;
    TreeNode **cur = &node->son;
    while (*cur != NULL) {
        count += nodeDelete(*cur);
        cur = &(*cur)->rightBro;
    }
    free(node);
    return count;
}

void treeErase(Tree *tree, TreeNode *node) {
    if (node->leftBro != NULL) {
        node->leftBro->rightBro = node->rightBro;
    } else if (node->parent != NULL) {
        node->parent->son = node->rightBro;
    } else {
        tree->root = NULL;
    }
    if (node->rightBro != NULL) {
        node->rightBro->leftBro = node->leftBro;
    }
    tree->size -= nodeDelete(node);
}

static void postOrder(TreeNode *node, int spaces) {
    if (node == NULL)
        return;
    postOrder(node->son, spaces + 2);
    for (int i = 0; i < spaces; ++i)
        printf(" ");
    printf("%d\n", node->value);
    postOrder(node->rightBro, spaces);
}

static void preOrder(TreeNode *node, int spaces) {
    if (node == NULL)
        return;
    for (int i = 0; i < spaces; ++i)
        printf(" ");
    printf("%d\n", node->value);
    preOrder(node->son, spaces + 2);
    preOrder(node->rightBro, spaces);
}

void treePrintPreOrder(Tree *tree) {
    preOrder(tree->root, 0);
}

void treePrintPostOrder(Tree *tree) {
    postOrder(tree->root, 0);
}

int nodeDepth(TreeNode *node) {
    TreeNode **cur = &node;
    int depth = 0;
    while (*cur != NULL) {
        ++depth;
        cur = &(*cur)->parent;
    }
    return depth;
}

int sonsCount(TreeNode *node) {
    TreeNode **cur = &node->son;
    int count = 0;
    while (*cur != NULL) {
        ++count;
        cur = &(*cur)->rightBro;
    }
    return count;
}

static int levelWidth(TreeNode *node, int level) {
    if (level == nodeDepth(node))
        return sonsCount(node);
    TreeNode **cur = &node->son;
    int sum = 0;
    while (*cur != NULL) {
        sum += levelWidth(*cur, level);
        cur = &(*cur)->rightBro;
    }
    return sum;
}

bool IsMonotDecreasing(Tree *tree) {
    int prev = sonsCount(tree->root), cur = prev;
    for (int level = 1; cur != 0; ++level) {
        prev = cur;
        cur = levelWidth(tree->root, level);
        if (cur > prev)
            return false;
    }
    return true;
}
~~~

main.c
~~~c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "tree.h"

#define MAXLEN 10

int main(void) {
    Tree mytree;
    treeCreate(&mytree);
    treeInsert(&mytree, NULL, 1);
    treeInsert(&mytree, treeRoot(&mytree), 4);
    treeInsert(&mytree, treeRoot(&mytree), 3);
    treeInsert(&mytree, treeRoot(&mytree), 2);
    treeInsert(&mytree, nodeLeftmostSon(treeRoot(&mytree)), 5);
    treeInsert(&mytree, nodeRightBro(nodeLeftmostSon(treeRoot(&mytree))), 7);
    treeInsert(&mytree, nodeRightBro(nodeLeftmostSon(treeRoot(&mytree))), 6);
    treeInsert(&mytree, nodeLeftmostSon(nodeRightBro(nodeLeftmostSon(treeRoot(&mytree)))), 11);
    treeInsert(&mytree, nodeLeftmostSon(nodeRightBro(nodeLeftmostSon(treeRoot(&mytree)))), 10);
    treeInsert(&mytree, nodeLeftmostSon(nodeRightBro(nodeLeftmostSon(treeRoot(&mytree)))), 9);
    treeInsert(&mytree, nodeRightBro(nodeRightBro(nodeLeftmostSon(treeRoot(&mytree)))), 8);
    printf("IsMonotDecreasing = %d \n", IsMonotDecreasing(&mytree));
    treeErase(&mytree, nodeRightBro(nodeLeftmostSon(treeRoot(&mytree))));
    printf("IsMonotDecreasing = %d \n", IsMonotDecreasing(&mytree));
    treePrintPreOrder(&mytree);
    printf("\n");
    treePrintPostOrder(&mytree);
    return 0;
}
~~~

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.  
<b>Подпись преподавателя</b> ________________

## 8. Распечатка протокола:
```bash
idl76@takoo /cygdrive/c/Users/idl76/Desktop/fundamental-computer-science-sempaitakoo/lab23
$ ./main.exe
IsMonotDecreasing = 0
IsMonotDecreasing = 1
1
  2
    5
  4
    8

    5
  2
    8
  4
1
```

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы:

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 13.05.23 | 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы.
- [Решённый контест](https://codeforces.com/contest/1811/my)

## 11. Выводы
В ходе выполнения работы были получены навыки реализации дерева общего вида и в некоторой степени двусвязного линейного списка. Попытки реализации обхода дерева общего вида без рекурсии не увенчались успехом, как и реализация in-order обхода.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> ________________