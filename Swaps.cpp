//
// Created by peng on 2021/9/12.
//

#include "Swaps.h"

Swaps::Swaps(const char *path, long size) : path(path), size(size) {
    this->seek = 0;
    this->value = nullptr;
}

Swaps::~Swaps() = default;

long Swaps::sizes() {
    return this->size;
}

long Swaps::frees() {
    return this->size;
}

int Swaps::sink(const char *ins) {
    const int len = (int) strlen(this->path);
    if (len <= 0)return -1;
    const int fds = open(this->path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    LOGW("Swaps sink fds=%d\n", fds);
    if (fds < 0) return -1;
    const char *suffix = ".swap";
    char *chs = static_cast<char *>(malloc(len + strlen(suffix) + 2));
    strcpy(chs, this->path);
    strcat(chs, suffix);
    const int fdd = open(chs, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    free(chs);
    LOGW("Swaps sink fdd=%d\n", fdd);
    if (fdd < 0) {
        close(fds);
        return -1;
    }
    int reads;
    const int buf_size = 4 * 1024;
    char buf[buf_size];
    while ((reads = (int) read(fds, buf, buf_size))) {
        write(fdd, buf, reads);
    }
    close(fds);
    close(fdd);
    LOGW("Swaps close file.\n");
    return 1;
}

int Swaps::flush(char *outs, long length) {
    LOGW("Swaps flush do nothing.\n");
    return 0;
}