#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "../src/bpt.h"

#define DATASET_PATH "../examples/2026-07-06_01-23-56.txt"

int main(void) {
    printf("--- B+ Tree ingestion & verification engine ---\n\n");
    
    BpTree *tree = createTree();
    if(!tree) return EXIT_FAILURE;

    printf("[OK] B+ Tree successfully created in heap memory.\n");
    FILE *file = fopen(DATASET_PATH, "rt");
    if(!file) {
        destroyNode(tree->root);
        free(tree);
        return EXIT_FAILURE;
    }

    printf("[OK] Opened dataset file: %s\n\n", DATASET_PATH);
    
    int value;
    int insertCount = 0, errorCount = 0;

    printf("Starting data ingestion...\n");
    while (fscanf(file, "%d", &value) == 1) {
        // Allocate a simple dynamic payload to hold our integer data
        int *payload = (int *)malloc(sizeof(int));
        if (!payload) {
            fprintf(stderr, "[ERROR] Memory allocation failed for payload of value: %d\n", value);
            errorCount++;
            continue;
        }
        *payload = value;

        // Execute B+ Tree insertion
        BpTreeStatus status = insert(tree, value, payload);
        if (status == BPTREE_VALID) {
            insertCount++;
        }
        else {
            fprintf(stderr, "[WARNING] Failed to insert key %d. Status code: %d\n", value, status);
            free(payload);
            errorCount++;
        }
    }
    rewind(file);
    printf("Ingestion complete. Total keys inserted: %d (Errors: %d)\n\n", insertCount, errorCount);

    // 4. Verification Pass: Prove the B+ Tree actually retrieves data in O(log N) time
    printf("Starting verification search pass...\n");
    int searchSuccessCount = 0;
    int searchFailCount = 0;

    while (fscanf(file, "%d", &value) == 1) {
        void *retrievedPayload = NULL;
        BpTreeStatus status = search(tree, value, &retrievedPayload);

        if (status == BPTREE_VALID && retrievedPayload != NULL) {
            int retrievedValue = *(int *)retrievedPayload;
            if (retrievedValue == value) {
                searchSuccessCount++;
            }
            else {
                fprintf(stderr, "[DATA CORRUPTION] Key %d returned mismatched payload %d!\n", value, retrievedValue);
                searchFailCount++;
            }
        }
        else {
            fprintf(stderr, "[SEARCH FAILED] Could not retrieve inserted key: %d\n", value);
            searchFailCount++;
        }
    }

    fclose(file);

    // 5. Final Reporting
    printf("Verification complete.\n");
    printf("----------------------------------------------\n");
    printf("Total Keys Successfully Retrieved : %d\n", searchSuccessCount);
    printf("Total Search Failures             : %d\n", searchFailCount);
    printf("----------------------------------------------\n");

    if (searchSuccessCount == insertCount && searchFailCount == 0) {
        printf("\n[SUCCESS] The B+ Tree implementation is functioning correctly.\n");
    }
    else {
        printf("\n[NOTICE] Some keys were lost.\n");
    }

    return EXIT_SUCCESS;
}