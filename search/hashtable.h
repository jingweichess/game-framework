#pragma once

#include <cstdint>
#include <vector>

#include "../types/depth.h"
#include "../types/hash.h"
#include "../types/score.h"

typedef std::uint8_t HashtableAge;
typedef std::int8_t HashtableDepth;
typedef std::uint8_t HashtableEntryType;

static constexpr HashtableEntryType HASHENTRYTYPE_NONE = 0;
static constexpr HashtableEntryType HASHENTRYTYPE_EXACT_VALUE = 1;
static constexpr HashtableEntryType HASHENTRYTYPE_LOWER_BOUND = 2;
static constexpr HashtableEntryType HASHENTRYTYPE_UPPER_BOUND = 3;

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

	Score scoreFromHash(Score score, Depth currentDepth);
	Score scoreToHash(Score score, Depth currentDepth);

	HashtableEntryType search(Hash hashValue, Score& score, Depth currentDepth, Depth& depthLeft, std::uint8_t& custom);
};
