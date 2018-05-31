#pragma once
template <class T>
class Singleton {
protected:
	// Static member variable
	// The instace will be "stored""
	static T* mSingleton;
	Singleton() {
		mSingleton = nullptr;
	}
public:
	// Avoid Copy constructor
	Singleton(const Singleton& copy) = delete;
	// Avoid Copy assingment
	Singleton& operator = (const Singleton& copy) = delete;
	// Get the instance. If it is NULL create an instance
	// Otherwise return the instance
	static T* Instance()
	{
		if (mSingleton == nullptr)
		{
			mSingleton = new T();
		}
		return mSingleton;
	}
	static void DeleteInstance() {
		delete mSingleton;
	}
};