#include "hashtable.h"

Hashtable::Hashtable()
{
	this->currentAge = 0;
	this->hashEntryCount = 0;
	this->hashEntryList = nullptr;
}

Hashtable::~Hashtable()
{
	if (this->hashEntryList != nullptr) {
		delete[] this->hashEntryList;
	}
}

void Hashtable::incrementAge()
{
	this->currentAge++;
}

void Hashtable::initialize(std::uint32_t entryCount)
{
	if (this->hashEntryList != nullptr) {
		delete[] this->hashEntryList;
		this->hashEntryList = nullptr;
	}

	HashtableEntry* newHashEntryList = new HashtableEntry[entryCount];

	this->hashEntryList = newHashEntryList;
	this->hashEntryCount = entryCount;

	this->reset();
}

void Hashtable::insert(Hash hashValue, Score score, Depth currentDepth, Depth depthLeft, HashtableEntryType hashtableEntryType, std::uint8_t custom)
{
	std::uint32_t position = hashValue & (this->hashEntryCount - 1);
	HashtableEntry* oldHashtableEntry = this->hashEntryList + position;

	if (oldHashtableEntry->hashValue == hashValue) {
		HashtableAge oldHashtableAge = oldHashtableEntry->age;
		HashtableDepth oldHashtableDepth = oldHashtableEntry->depthLeft;

		if (this->currentAge == oldHashtableAge
			&& depthLeft <= oldHashtableDepth) {
			return;
		}
	}

	HashtableEntry hashtableEntry;

	hashtableEntry.hashValue = hashValue;
	hashtableEntry.score = this->scoreToHash(score, currentDepth);
	hashtableEntry.depthLeft = depthLeft;
	hashtableEntry.age = this->currentAge;
	hashtableEntry.hashtableEntryType = hashtableEntryType;
	hashtableEntry.custom = custom;

#if defined(USE_M128I)
	(*oldHashtableEntry).vector = hashtableEntry.vector;
#else
	*oldHashtableEntry = hashtableEntry;
#endif
}

void Hashtable::reset()
{
	HashtableEntry hashtableEntry;
	hashtableEntry.hashValue = EmptyHash;

	for (std::uint32_t i = 0; i < this->hashEntryCount; i++) {
		this->hashEntryList[i] = hashtableEntry;
	}
}

Score Hashtable::scoreFromHash(Score score, Depth currentDepth)
{
	if (score >= WIN_SCORE - Depth::MAX) {
		return score - currentDepth;
	}
	else if (score <= -WIN_SCORE + Depth::MAX) {
		return score + currentDepth;
	}

	return score;
}

Score Hashtable::scoreToHash(Score score, Depth currentDepth)
{
	if (score >= WIN_SCORE - Depth::MAX) {
		return score + currentDepth;
	}
	else if (score <= -WIN_SCORE + Depth::MAX) {
		return score - currentDepth;
	}

	return score;
}

HashtableEntryType Hashtable::search(Hash hashValue, Score& score, Depth currentDepth, Depth& depthLeft, std::uint8_t& custom)
{
	std::uint32_t position = hashValue & (this->hashEntryCount - 1);
	HashtableEntry* hashtableEntry = this->hashEntryList + position;

	if (hashValue != hashtableEntry->hashValue) {
		return HashtableEntryType(HASHENTRYTYPE_NONE);
	}

	custom = hashtableEntry->custom;
	depthLeft = (Depth)hashtableEntry->depthLeft;
	score = this->scoreFromHash(hashtableEntry->score, currentDepth);

	return hashtableEntry->hashtableEntryType;
}
