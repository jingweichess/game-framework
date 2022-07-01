#pragma once

#include <cstdint>

template <std::uint32_t width, std::uint32_t height>
class ButterflyTable
{
protected:
    std::uint32_t scores[width][height];
public:
    ButterflyTable()
    {
        this->reset();
    }

    ~ButterflyTable()
    {

    }

    std::uint32_t add(std::uint32_t x, std::uint32_t y, std::uint32_t score)
    {
        std::uint32_t history = this->scores[x][y] + score;

        this->scores[x][y] = history;

        return history;
    }

    std::uint32_t get(std::uint32_t x, std::uint32_t y) const
    {
        return this->scores[x][y];
    }

    void reset()
    {
        for (std::uint32_t i = 0; i < width; i++) {
            for (std::uint32_t j = 0; j < height; j++) {
                this->scores[i][j] = 0;
            }
        }
    }
};
