/**
 * @file vector_processor.cpp
 * @brief Обработка векторов.
 * 
 * Этот файл содержит функции для работы с векторами, включая вычисление суммы элементов.
 */
#include "vector_processor.h"
#include <limits>

/**
 * @brief Вычисляет сумму элементов вектора с учетом переполнения.
 * 
 * Возвращает сумму всех элементов вектора. Если результат выходит за пределы диапазона типа int16_t, возвращается максимальное или минимальное значение.
 * 
 * @param vector Вектор, элементы которого нужно сложить.
 * @return Сумма элементов вектора.
 */
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

