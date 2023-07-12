
#include "table.h"

int main() {
    Table table = tableCreate();

    int count = 0;
    printf("Input how many rows do you want to insert: ");
    scanf("%d", &count);

    for (int i = 0; i < count; ++i) {
        printf("Row %d:\n", i);

        char *charKey = (char*) calloc(256, sizeof(char));
        printf("Input key string: \n");
        scanf("%s", charKey);

        int intKey = 0;
        printf("Input key int: \n");
        scanf("%d", &intKey);

        char *value = (char*) calloc(256, sizeof(char));
        printf("Input value string: \n");
        scanf("%s", value);

        tablePush(&table, charKey, intKey, value);

        free(charKey);

        printf("\n");
    }

    tablePrint(table);
    printf("\n");
    table = tableQSort(table);
    tablePrint(table);

    int search = 1;
    while (search) {
        char *charKey = (char*) calloc(256, sizeof(char));
        int intKey = 0;
        printf("\n Search for: \n");
        scanf("%s", charKey);
        scanf("%d", &intKey);

        printf("Found string: %s\n", tableBinarySearch(table, charKey, intKey));
        free(charKey);

        printf("Do you want to continue the search? (0/1): \n");
        scanf("%d", &search);
    }

    tableDestroy(&table);
}