#include <stdio.h>
#include <string.h>

#define MAX_PARTS 100
#define NAME_LEN 50

// structure to represent a part
typedef struct {
    int number;
    char name[NAME_LEN + 1];
    int on_hand;
} part;

// global variables
part inventory[MAX_PARTS];
int num_parts = 0;

// function prototypes
int find_part(int number);
void insert(void);
void search(void);
void update(void);
void print(void);

int main(void) {
    char code;

    printf("Welcome to the Inventory Management System\n");
    printf("Commands: i (insert), s (search), u (update), p (print), q (quit)\n\n");

    for (;;) {
        printf("Enter operation code: ");
        scanf(" %c", &code);

        switch (code) {
            case 'i':
                insert();
                break;
            case 's':
                search();
                break;
            case 'u':
                update();
                break;
            case 'p':
                print();
                break;
            case 'q':
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Illegal code\n");
        }
        printf("\n");
    }

    return 0;
}

// find a part by part number; returns index if found, -1 if not found
int find_part(int number) {
    int i;

    for (i = 0; i < num_parts; i++) {
        if (inventory[i].number == number) {
            return i;
        }
    }
    return -1;
}

// insert a new part into the inventory
void insert(void) {
    int part_number;

    if (num_parts == MAX_PARTS) {
        printf("Database is full; can't add more parts.\n");
        return;
    }

    printf("Enter part number: ");
    scanf("%d", &part_number);

    if (find_part(part_number) >= 0) {
        printf("Part already exists.\n");
        return;
    }

    inventory[num_parts].number = part_number;

    printf("Enter part name: ");
    scanf(" %[^\n]", inventory[num_parts].name);  // read line with spaces

    printf("Enter quantity on hand: ");
    scanf("%d", &inventory[num_parts].on_hand);

    num_parts++;
    printf("Part inserted successfully.\n");
}

// search for a part and display its information
void search(void) {
    int i, number;

    printf("Enter part number: ");
    scanf("%d", &number);

    i = find_part(number);
    if (i >= 0) {
        printf("Part name: %s\n", inventory[i].name);
        printf("Quantity on hand: %d\n", inventory[i].on_hand);
    } else {
        printf("Part not found.\n");
    }
}

// update the quantity of a part
void update(void) {
    int i, number, change;

    printf("Enter part number: ");
    scanf("%d", &number);

    i = find_part(number);
    if (i >= 0) {
        printf("Enter change in quantity on hand: ");
        scanf("%d", &change);
        inventory[i].on_hand += change;
        printf("Part updated successfully.\n");
        printf("New quantity on hand: %d\n", inventory[i].on_hand);
    } else {
        printf("Part not found.\n");
    }
}

// print all parts in the inventory
void print(void) {
    int i;

    if (num_parts == 0) {
        printf("No parts in inventory.\n");
        return;
    }

    printf("Part Number  Part Name                    Quantity\n");
    printf("----------- ---------------------------- --------\n");

    for (i = 0; i < num_parts; i++) {
        printf("%-11d %-28s %8d\n",
               inventory[i].number,
               inventory[i].name,
               inventory[i].on_hand);
    }

    printf("\nTotal parts in inventory: %d\n", num_parts);
}
