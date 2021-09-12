//
// Created by peng on 2021/9/12.
//

#include "Caches.h"

Caches::Caches() : size(4 * 1024) {
    this->value = static_cast<char *>(malloc(this->size));
    this->seek = 0;
}

Caches::~Caches() {
    if (!this->value) return;
    delete value;
    this->value = nullptr;
    this->seek = 0;
}

long Caches::sizes() {
    return this->size;
}
