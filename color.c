#include <stdio.h>

int main() {
    unsigned int i = 0xffffffef;
    unsigned char *c =(char*)&i;
    for (int i=0;i<4;i++) {
        printf("%d\n",c[i]);
    }
}