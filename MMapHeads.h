//
// Created by peng on 2021/9/12.
//

#ifndef LCT_MMAPHEADS_H
#define LCT_MMAPHEADS_H


class MMapHeads {
public:
    const char *fmt;

    const long size;

    MMapHeads(const char *fmt, long size);

    ~MMapHeads();
};


#endif //LCT_MMAPHEADS_H
