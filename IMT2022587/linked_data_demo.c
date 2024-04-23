#include<stdio.h>
#include<stdlib.h>

#include"pds.h"
// Include the header file that contains the struct declarations for parent and child records

// Declare global variables for 10 parent and 10 child records

struct Author {
    int author_id;
    char author_name[50];
};

struct Publication {
    int publication_id;
    char publication_title[100];
};

void show_menu();
void setup_data();
void process_option(int option);
void process_option1();
void process_option2();
struct Author parent_records[10];
struct Publication child_records[10];

int main()
{
    // printf("hi\n");
    int option;
    setup_data();
    do {
        show_menu();
        scanf("%d", &option);
        process_option(option);
    } while (option != 0);
    return 0;
}

void show_menu()
{
    printf("\nLINKED DATA DEMO\n\n");
    printf("0. Exit\n");
    printf("1. Add linked data\n");
    printf("2. Get linked data\n");
    printf("\nEnter option: ");
}

void setup_data() {
    // Statically create 10 parent and 10 child records individually
    int status1 = pds_create("author", "publication");

    int status2 = pds_open("author", "publication", sizeof(struct Author), sizeof(struct Publication));

    for (int i = 0; i < 10; i++) {
        parent_records[i].author_id = i + 1;
        sprintf(parent_records[i].author_name, "Author%d", i + 1);
        put_rec_by_key(parent_records[i].author_id, &parent_records[i]);
        child_records[i].publication_id = i + 1;
        sprintf(child_records[i].publication_title, "Publication%d", i + 1);
        put_linked_rec_by_key(child_records[i].publication_id, &child_records[i]);
    }
}

void process_option(int option)
{
    switch (option) {
        case 0:
            // do nothing
            break;
        case 1:
            process_option1();
            break;
        case 2:
            process_option2();
            break;
        default:
            printf("Invalid option\n");
            break;
    }
}

void process_option1()
{
    int parent_key, child_key;
    printf("Enter parent key and child key for linking: ");
    scanf("%d%d", &parent_key, &child_key);
    // TODO: Call appropriate PDS functions here to link the two records
    struct Author c1;
    struct Publication c;
    int r1 = get_rec_by_ndx_key(parent_key, &c1);
    int r2 = get_linked_rec_by_key(child_key, &c);

    if (r1 == 0 && r2 == 0) {
        pds_link_rec(parent_key, child_key);
    }
    else if (r1 != 0) {
        printf("Enter correct key of parent\n");
    }
    else if (r2 != 0) {
        printf("Enter correct key of child\n");
    }
}

void process_option2()
{
    int parent_key;
    printf("Enter parent key: ");
    scanf("%d", &parent_key);
    int linked_keys_result[100];
    int size;
    // TODO: Call appropriate PDS functions here to fetch array of child keys
    // Call your PDS functions to display the list of child keys retrieved for the given parent key
    // Display all field values of each child record in a nicely formatted manner
    pds_get_linked_rec(parent_key, linked_keys_result, &size);

    for (int i = 0; i < size; i++) {
        struct Publication *c = malloc(sizeof(struct Publication));
        get_linked_rec_by_key(linked_keys_result[i], c);
        printf("\nid is %d , title is %s\n", c->publication_id, c->publication_title);
    }
}

