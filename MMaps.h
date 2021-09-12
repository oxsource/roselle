//
// Created by peng on 2021/9/12.
//

#ifndef LCT_MMAPS_H
#define LCT_MMAPS_H

#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "Buffer.h"
#include "MMapHeads.h"

class MMaps : public Buffer {
private:
    const char *path;
    const long size;
    int fd;
    MMapHeads *heads;

    void prepare();

public:
    MMaps(const char *path, long size);

    ~MMaps();

    long sizes() override;

    long frees() override;

    int sink(const char *ins) override;
};


#endif //LCT_MMAPS_H
