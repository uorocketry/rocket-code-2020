#include "common/utils.h"

uint64_t utils::getMonotonicTimeStamp()
{
    return std::chrono::duration_cast<time_point::duration>(std::chrono::steady_clock::now().time_since_epoch())
        .count();
}