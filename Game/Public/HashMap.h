#pragma once
#include <list>
//
// a hash map
// you could use std::map or std::unordered_map if you want (but full marks for your own)
//
typedef unsigned int Hash;
template<class T, int SIZE>
class HashMap
{
public:

	HashMap()
	{
		// assume SIZE is a power of two
		mMask = SIZE - 1;
	}

	// TODO: Check before insert
	void InsertNoCheck(T& data)
	{
		int index = Translate(data->mHash);
		mBuckets[index].push_back(data);
	}

	const T Find(Hash hash) const
	{
		int index = Translate(hash);
		const std::list<T>& bucket = mBuckets[index];

		for (auto& value : bucket)
		{
			if (value->mHash == hash)
			{
				return value;
			}
		}

		return nullptr;
	}

	void Delete(T data)
	{
		int index = Translate(data->mHash);
		const std::list<T>& bucket = mBuckets[index];

		for (auto& value : bucket)
		{
			if (value == data)
			{
				delete value;
			}
		}
	}

private:

	int Translate(Hash hash) const
	{
		return (hash & mMask);
	}

private:

	Hash mMask;

	// you should use your own linked list class for full marks
	std::list<T> mBuckets[SIZE];
};
