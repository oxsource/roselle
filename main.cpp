#include "Caches.h"
#include "MMaps.h"
#include "Swaps.h"
#include "Roselle.h"

int main() {
    const char *path = "/Users/peng/Desktop/logcat.txt";
//    //test caches
//    auto *caches = new Caches();
//    caches->sink("hello worlds", 0);
//    printf("caches sizes: %ld", caches->sizes());
//    printf("caches frees: %ld", caches->frees());
//    delete caches;
//    //test mmaps
//    auto *mmaps = new MMaps(path, 10 * 1024);
//    mmaps->sink("this is a goods.", 0);
//    printf("mmaps sizes: %ld", mmaps->sizes());
//    printf("mmaps frees: %ld", mmaps->frees());
//
//    delete mmaps;
//    //test swaps
//    auto *swaps = new Swaps(path, 10 * 1024);
//    swaps->sink("this is a love.", 0);
//    delete swaps;

    auto *rose = new Roselle(path, 6 * 1024);
    char chs[40];
    for (int i = 0; i < 500; i++) {
        sprintf(chs, "%04d this is a log.\n", i);
        rose->sink(chs, 0);
    }
    rose->flush();
    delete rose;
    return 0;
}
