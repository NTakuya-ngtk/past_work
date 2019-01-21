
#include "textformatter.h"


void ps(const char *str, int fonttype) {

    if (fonttype >= 3) {
        fprintf(stderr, "フォント指定が間違っています。(ps)\n");
        exit(1);
    }

    switch (fonttype) {
        case COURIER:
            printf("(%s) C s\n", str);
            break;

        case COURIER_BOLD:
            printf("(%s) B s\n", str);
            break;

        case MINCHO:
            printf("(%s) K s\n", str);
            break;
    }
    return;
}

