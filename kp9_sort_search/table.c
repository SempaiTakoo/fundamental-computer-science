
#include "table.h"

Table tableCreate() {
    Table table;
    table.data = (Item*) calloc(0, sizeof(Item));
    table.size = 0;
    return table;
}

Table tableCopy(Table table) {
    Table temp = tableCreate();
    for (int i = 0; i < table.size; ++i) {
        char *value = (char*) calloc(256, sizeof(char));
        strcpy(value, table.data[i].value);
        tablePush(&temp, table.data[i].key.charKey, table.data[i].key.intKey, value);
    }
    return temp;
}

void tablePush(Table *table, char *charKey, int intKey, char *value) {
    Key ck = { .intKey = intKey };
    for (int i = 0; i < KEY_LENGHT && i < (int) strlen(charKey); ++i) {
        ck.charKey[i] = charKey[i];
    }
    Item i = { .key = ck, .value = value };
    table->data = (Item*) realloc(table->data, sizeof(Item) * (table->size + 1));
    table->size++;
    table->data[table->size - 1] = i;
}

static void tableQuickSort(Table *table, int l, int r) {
    char *pivot_value = table->data[l].value;
    Key pivot_key = table->data[l].key;
    int l_init = l, r_init = r;
    while (l < r) {
        while (
            (
                strcmp(pivot_key.charKey, table->data[r].key.charKey) < 0 ||
                (
                    strcmp(pivot_key.charKey, table->data[r].key.charKey) == 0 &&
                    pivot_key.intKey <= table->data[r].key.intKey
                )
            ) && (l < r)
        ) r--;
        if (l != r) {
            table->data[l].value = table->data[r].value;
            table->data[l].key = table->data[r].key;
            l++;
        }
        while (
            strcmp(pivot_key.charKey, table->data[l].key.charKey) > 0 &&
            (l < r)
        ) l++;
        if (l != r) {
            table->data[r].value = table->data[l].value;
            table->data[r].key = table->data[l].key;
            r--;
        }
    }
    table->data[l].key = pivot_key;
    table->data[l].value = pivot_value;
    int pivot = l;
    l = l_init;
    r = r_init;
    if (l < pivot) tableQuickSort(table, l, pivot - 1);
    if (r > pivot) tableQuickSort(table, pivot + 1, r);
}

Table tableQSort(Table table) {
    Table temp = tableCopy(table);
    tableQuickSort(&temp, 0, temp.size - 1);
    return temp;
}

char *tableBinarySearch(Table table, char *charKey, int intKey) {
    int l = 0, r = table.size - 1, m = (l + r) / 2;
    while (l <= r) {
        m = (l + r)/2;
        char *curCharKey = table.data[m].key.charKey;
        int curIntKey = table.data[m].key.intKey;
        if (strcmp(charKey, curCharKey) == 0 && intKey == curIntKey)
            return table.data[m].value;
        if (strcmp(charKey, curCharKey) > 0 || (strcmp(charKey, curCharKey) == 0 && intKey < curIntKey))
            l = m + 1;
        else
            r = m - 1;
    }
    return NULL;
}


void tablePrint(Table table) {
    printf("| Key%*s| Value\n", KEY_LENGHT + 11 - 3, "");
    for (int i = 0; i < table.size; ++i) {
        printf("| %*s%11d| %s\n", KEY_LENGHT, table.data[i].key.charKey, table.data[i].key.intKey, table.data[i].value);
    }
}


void tableDestroy(Table *table) {
    for (int i = 0; i < table->size; ++i) {
        table->data[i].key.charKey[0] = '\0';
        table->data[i].key.intKey = 0;
        free(table->data[i].value);
    }
    free(table->data);
}