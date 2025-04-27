#include <stdio.h>

#include "SortedLinkedList.h"

int main(void)
{
    SLL_Controller ctrl = SLL_NewController();
    // puts("--- Initial Values ---");
    // SLL_Print(&ctrl);
    // SLL_ReversePrint(&ctrl);

    // puts("--- Insertion Operations ---");
    // SLL_Insert(&ctrl, 4);
    // SLL_Print(&ctrl);
    // SLL_ReversePrint(&ctrl);
    // puts("--------------------");

    // SLL_Insert(&ctrl, 2);
    // SLL_Print(&ctrl);
    // SLL_ReversePrint(&ctrl);
    // puts("--------------------");
    
    // SLL_Insert(&ctrl, 6);
    // SLL_Print(&ctrl);
    // SLL_ReversePrint(&ctrl);
    // puts("--------------------");

    // SLL_Insert(&ctrl, 5);
    // SLL_Print(&ctrl);
    // SLL_ReversePrint(&ctrl);
    // puts("--------------------");

    SLL_Insert(&ctrl, 4);
    SLL_Insert(&ctrl, 2);
    SLL_Insert(&ctrl, 6);
    SLL_Insert(&ctrl, 5);

    // SLL_Element* foundElement = SLL_Find(&ctrl, 5);
    // if(foundElement) printf("Found: %d\n", foundElement->Value);
    // if(!foundElement) printf("Element does not exist\n");
    
    // foundElement = SLL_Find(&ctrl, 10);
    // if(foundElement) printf("Found: %d\n", foundElement->Value);
    // if(foundElement) printf("Element does not exist\n");

    puts("--- Initial Values ---"); // {2, 4, 5, 6}
    SLL_Print(&ctrl);
    SLL_ReversePrint(&ctrl);

    puts("--- Removal Operations ---");

    SLL_Remove(&ctrl, 10); // {2, 4, 5, 6}
    SLL_Print(&ctrl);
    SLL_ReversePrint(&ctrl);
    puts("--------------------");

    SLL_Remove(&ctrl, 5); // {2, 4, 6}
    SLL_Print(&ctrl);
    SLL_ReversePrint(&ctrl);
    puts("--------------------");

    SLL_Remove(&ctrl, 2); // {4, 6}
    SLL_Print(&ctrl);
    SLL_ReversePrint(&ctrl);
    puts("--------------------");

    SLL_Remove(&ctrl, 6); // {4}
    SLL_Print(&ctrl);
    SLL_ReversePrint(&ctrl);
    puts("--------------------");

    SLL_Remove(&ctrl, 4); // {}
    SLL_Print(&ctrl);
    SLL_ReversePrint(&ctrl);
    puts("--------------------");

    puts("--- Insertion Operations ---");
    SLL_Insert(&ctrl, 4);
    SLL_Print(&ctrl);
    SLL_ReversePrint(&ctrl);
    puts("--------------------");

    SLL_Insert(&ctrl, 2);
    SLL_Print(&ctrl);
    SLL_ReversePrint(&ctrl);
    puts("--------------------");
    
    SLL_Insert(&ctrl, 6);
    SLL_Print(&ctrl);
    SLL_ReversePrint(&ctrl);
    puts("--------------------");

    SLL_Insert(&ctrl, 5);
    SLL_Print(&ctrl);
    SLL_ReversePrint(&ctrl);
    puts("--------------------");

    SLL_Free(&ctrl);
    printf("--- Freed the controller! ---\n");
    SLL_Print(&ctrl);
    SLL_ReversePrint(&ctrl);
    puts("--------------------");
    return 0;
}