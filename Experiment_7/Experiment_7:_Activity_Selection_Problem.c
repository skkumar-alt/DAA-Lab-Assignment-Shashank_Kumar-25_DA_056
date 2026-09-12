#include <stdio.h>

typedef struct {
    int start;
    int finish;
} Activity;

void sortActivities(Activity a[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j].finish > a[j + 1].finish) {
                Activity temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, i;
    
    printf("Enter number of activities: ");
    scanf("%d", &n);

    Activity a[n];

    printf("Enter start and finish times:\n");
    for (i = 0; i < n; i++) {
        scanf("%d %d", &a[i].start, &a[i].finish);
    }

    sortActivities(a, n);

    printf("Selected Activities:\n");

    i = 0;
    printf("(%d,%d) ", a[i].start, a[i].finish);

    int lastFinish = a[i].finish;

    for (i = 1; i < n; i++) {
        if (a[i].start >= lastFinish) {
            printf("(%d,%d) ", a[i].start, a[i].finish);
            lastFinish = a[i].finish;
        }
    }

    return 0;
}
