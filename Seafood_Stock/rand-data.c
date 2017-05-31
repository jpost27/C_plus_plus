#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

static char *stock = "stock";
static char *buy = "buy";
static char *shrimp = "shrimp";
static char *lobster = "lobster";
static char *crab = "crab";
static char *swordfish = "swordfish";
void init_random(void);
int get_random(int, int);

void init_random() {
    srandom(getpid() + time(0));
}
char *random_event(char *a, char *b, int div) {
    if (get_random(1, 100) < div)
        return a;
    else
        return b;
}
char *random_date_increasing(int n, char *line) {
    static int month = 1;
    static int day = 1;
    static int year = 2016;
    int chance = get_random(1,100);
    int changed = 0;
    if (chance < 20) {
        month = month % 12 + 1;
        changed = 1;
    }

    int divisor = 31;
    switch (month) {
        case 2:
            if (year % 4 == 0 && year % 100 != 0 ||
                year % 400 == 0)
                divisor = 29;
            break;
        case 4: case 6: case 9: case 11:
            divisor = 30;
            break;
        default:
            break;
    }
    if (changed) {
        day = 1;
    } else {
        chance = get_random(1,100);
        if (chance < 30) {
            day = day % divisor + 1;
            if (day == 1) {
                month = month % 12 + 1;
                changed = 1;
            }
        }
    }

    if (month == 1 && changed) year++;

    snprintf(line, n, "%02d/%02d/%4d", month, day, year);
    return line;
}

char *random_date(int n, char *line) {
    int month = get_random(1,12);
    int day = get_random(1,31);
    int year = get_random(1,3);
    if (year == 1)
        year = 2012;
    else if (year == 2)
        year = 2013;
    else
        year = 2014;
    snprintf(line, n, "%02d/%02d/%4d", month, day, year);
    return line;
}
char *random_item(char *a, char *b, char *c, char *d) {
    int i = get_random(1, 100);
    if (i < 25)
        return a;
    else if (i < 50)
        return b;
    else if (i < 75)
        return c;
    else
        return d;
}
void usage(char *arg) {
    printf("Usage: %s\n", arg);
}
int get_random(int m, int n) {
    if (n < m) { int t = m; m = n; n = t; }
    return (int)(random() % (n-m+1) + m);
}
int main(int argc, char *argv[]) {
    // if (argc != 2) { fprintf(stderr, "usage %s N\n", argv[0]); exit(1); }
    int c = '?';
    int error = 0;
    int count = 25;
    int lower = 1;
    int upper = 10;
    while ((c = getopt(argc,argv,":n:l:u:")) != EOF) {
        if (c == ':') {
#           ifdef DEBUG
                printf("illegal ");
#           endif
            c = optopt;
            error = 1;
            exit(1);
        }
        switch (c) {
            case 'n':
                count = atoi(optarg);
                break;
            case 'l':
                lower = atoi(optarg);
                break;
            case 'u':
                upper = atoi(optarg);
                break;
            default:
                usage(argv[0]);
                exit(1);
        }
    }
    init_random();
    char *line = malloc(11*sizeof(char));
    for (int i = 0, j = 0; i < count; i++) {
        char *event = random_event(stock, buy, 30);
        char *date  = 0;
        if (strcmp(event, stock) != 0 && j < 5) {
            i--;
            continue;
        }
        j++;
        if (strcmp(event, buy) == 0) {
            date  = random_date_increasing(11, line);
        } else {
            date  = random_date(11, line);
        }
        char *item  = random_item(shrimp, lobster, crab, swordfish);
        int num  = 1;
        if (strcmp(event, buy) == 0) {
            if (strcmp(item, shrimp) == 0) {
                num     = get_random(10,50);
            } else if (strcmp(item, lobster) == 0) {
                num     = get_random(2,4);
            } else if (strcmp(item, crab) == 0) {
                num     = get_random(1,5);
            } else { // strcmp(item, swordfish) == 0
                num     = get_random(1,5);
            }
        } else {
            num     = get_random(1,5);
        }
        printf("%s %s %s %d\n", event, date, item, num);
  }
}
