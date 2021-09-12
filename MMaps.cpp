//
// Created by peng on 2021/9/12.
//

#include "MMaps.h"

MMaps::MMaps(const char *path, long size) : path(path), size(size) {
    LOGW("MMaps constructor path=%s, size=%ld.\n", path, size);
    //heads = max_length + \0 + \n, max support eight-digit number
    this->heads = new MMapHeads("%08ld\n", 8 + 2);
}

MMaps::~MMaps() {
    LOGW("MMaps destructor called.\n");
    if (this->value) {
        long tSize = this->size > 0 ? this->size : 0;
        munmap(this->value, tSize);
        this->value = nullptr;
        LOGW("MMaps destructor munmap.\n");
    }
    if (this->fd >= 0) {
        close(this->fd);
        this->fd = -1;
        LOGW("MMaps destructor close file.\n");
    }
}

void MMaps::prepare() {
    if (this->fd > 0) return;
    this->seek = -1;
    this->value = nullptr;
    this->fd = open(this->path, O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    LOGW("MMaps setup fd=%d\n", this->fd);
    if (this->fd < 0) return;
    //reset file size
    ftruncate(this->fd, this->size);
    lseek(this->fd, 0, SEEK_SET);
    //read file length
    char *seeks = (char *) malloc(this->heads->size);
    read(this->fd, seeks, this->heads->size);
    char *stops;
    this->seek = (long) ::strtol(seeks, &stops, 10);
    free(seeks);
    //mmap file
    lseek(this->fd, 0, SEEK_SET);
    void *buffer = mmap(nullptr, this->size, PROT_READ | PROT_WRITE, MAP_SHARED, this->fd, 0);
    this->value = MAP_FAILED == buffer ? nullptr : (char *) buffer;
    this->seek = this->value ? this->seek : -1;
    LOGW("MMaps setup: seek=%ld\n", this->seek);
}

long MMaps::sizes() {
    return this->fd < 0 || !this->value ? 0 : this->size - this->heads->size;
}

long MMaps::frees() {
    return this->fd < 0 || !this->value ? 0 : this->Buffer::frees();
}

int MMaps::sink(const char *ins) {
    this->prepare();
    if (this->fd < 0 || !this->value) return -1;
    const long length = (long) strlen(ins);
    if (length <= 0) return 0;
    if (this->frees() < length) return -1;
    char *body = this->value + this->heads->size;
    strcpy(body + this->seek, ins);
    this->seek += length;
    //update heads with format
    sprintf(this->value, this->heads->fmt, this->seek);
    return 1;
}