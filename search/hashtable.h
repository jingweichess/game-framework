#pragma once

#include <cstdint>
#include <vector>

#include "../types/depth.h"
#include "../types/hash.h"
#include "../types/score.h"

using HashtableAge = std::uint8_t;
using HashtableDepth = std::int8_t;

enum HashtableEntryType : std::uint8_t {
    HASHENTRYTYPE_NONE,
    HASHENTRYTYPE_EXACT_VALUE,
    HASHENTRYTYPE_LOWER_BOUND,
    HASHENTRYTYPE_UPPER_BOUND
};

struct HashtableEntry {
    union {
        struct {
            Hash hashValue;
            Score score;
            HashtableDepth depthLeft;
            HashtableAge age;
            HashtableEntryType hashtableEntryType;
            std::uint8_t custom;
        };
#if defined(USE_M128I)
        __m128i vector;
#endif
    };
};

static_assert(sizeof(HashtableEntry) == 16);

class Hashtable
{
protected:
    HashtableEntry* hashEntryList = nullptr;

    std::uint32_t hashEntryCount;
    HashtableAge currentAge;
public:
    Hashtable();
    ~Hashtable();

    void incrementAge();

    void initialize(std::uint32_t entryCount);

    void insert(Hash hashValue, Score score, Depth currentDepth, Depth depthLeft, HashtableEntryType hashtableEntryType, std::uint8_t custom);

    void reset();

    Score scoreFromHash(Score score, Depth currentDepth) const;
    Score scoreToHash(Score score, Depth currentDepth) const;

    HashtableEntryType search(Hash hashValue, Score& score, Depth currentDepth, Depth& depthLeft, std::uint8_t& custom) const;
};
