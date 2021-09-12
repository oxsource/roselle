//
// Created by peng on 2021/9/12.
//

#include "Buffer.h"

Buffer::Buffer() {
    this->value = nullptr;
    this->next = nullptr;
    this->seek = 0;
}

Buffer::~Buffer() = default;

long Buffer::sizes() {
    return 0;
}

long Buffer::frees() {
    return this->sizes() - this->seek;
}

int Buffer::sink(const char *ins) {
    if (!this->value) return -1;
    const long length = (long) strlen(ins);
    if (length <= 0) return 0;
    if (this->frees() < length) return -1;
    memcpy(this->value + this->seek, ins, length);
    this->seek += length;
    return 1;
}

int Buffer::flush(char *outs, long length) {
    if (this->seek <= 0 || !this->value) return -1;
    if (length < this->seek) return -2;
    memcpy(outs, this->value, this->seek);
    memset(this->value, '\0', this->sizes());
    this->seek = 0;
    return 1;
}

int Buffer::flush(Buffer *buf) {
    return this->flush(buf->value, buf->seek);
}