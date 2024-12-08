#ifndef VECTOR_PROCESSOR_H
#define VECTOR_PROCESSOR_H

#include <vector>
#include <cstdint>

class VectorProcessor {
public:
    int16_t computeSum(const std::vector<int16_t>& vector);
};

#endif // VECTOR_PROCESSOR_H

