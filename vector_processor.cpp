#include "vector_processor.h"
#include <limits>

int16_t VectorProcessor::computeSum(const std::vector<int16_t>& vector) {
    int32_t sum = 0;

    for (const auto& elem : vector) {
        sum += elem;

        if (sum > std::numeric_limits<int16_t>::max()) {
            return std::numeric_limits<int16_t>::max();
        }

        if (sum < std::numeric_limits<int16_t>::min()) {
            return std::numeric_limits<int16_t>::min();
        }
    }

    return static_cast<int16_t>(sum);
}
