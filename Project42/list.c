#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 100

typedef int element;
typedef struct {
    element array[MAX_LIST_SIZE];
    int size;
} ArrayListType;

void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init(ArrayListType* L)
{
    L->size = 0;
}

int is_empty(ArrayListType* L)
{
    return L->size == 0;
}

int is_full(ArrayListType* L)
{
    return L->size == MAX_LIST_SIZE;
}

element get_entry(ArrayListType* L, int pos)
{
    if (pos < 0 || pos >= L->size)
        error("위치 오류");
    return L->array[pos];
}

void print_list(ArrayListType* L)
{
    int i;
    for (i = 0; i < L->size; i++)
        printf("%d\n", L->array[i]);
}

void insert(ArrayListType* L, int pos, element item)
{
    if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
        int move_count = L->size - pos;
        for (int i = L->size - 1; i >= pos; i--)
            L->array[i + 1] = L->array[i];
        L->array[pos] = item;
        L->size++;
        printf("move: %d\n", move_count);
    }
    else {
        error("리스트가 가득 찼거나 잘못된 위치입니다.");
    }
}

element delete(ArrayListType* L, int pos)
{
    element item;
    if (pos < 0 || pos >= L->size)
        error("위치 오류");
    item = L->array[pos];
    int move_count = L->size - pos - 1;
    for (int i = pos; i < L->size - 1; i++)
        L->array[i] = L->array[i + 1];
    L->size--;
    printf("move: %d\n", move_count);
    return item;
}

int main()
{
    ArrayListType list;
    init(&list);

    int menu = -1;
    while (menu != 0) {
        printf("\nmenu\n");
        printf("(1) insert\n");
        printf("(2) delete\n");
        printf("(3) print\n");
        printf("(0) Exit\n");
        printf("enter the menu : ");
        scanf("%d", &menu);

        switch (menu) {
        case 1: {
            if (is_full(&list)) {
                printf("List is full.\n");
                break;
            }
            element item;
            int pos;
            printf("enter the number and position : ");
            scanf("%d %d", &item, &pos);
            insert(&list, pos, item);
            break;
        }
        case 2: {
            if (is_empty(&list)) {
                printf("List is empty.\n");
                break;
            }
            int pos;
            printf("enter the position to delete: ");
            scanf("%d", &pos);

            if (pos < 0 || pos >= list.size) {
                printf("Invalid position.\n");
                break;
            }

            delete(&list, pos);
            break;
        }
        case 3:
            print_list(&list);
            break;
        case 0:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid menu . Please try again.\n");
            break;
        }
    }

    return 0;
}
