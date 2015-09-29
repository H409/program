//*****************************************************************************
//
// flyweight
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _FLYWEIGHT_H_
#define _FLYWEIGHT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "common/base/base.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
namespace common
{
namespace base
{

template <class Key,class Data>
class Flyweight : public Base
{
private:
	using TData = std::shared_ptr<Data>;

public:
	TData Get(const Key& key)
	{
		auto it = container_.find(key);

		if(it == container_.end())
		{
			auto data = TData(Create(key));
			container_.insert(std::pair<Key,TData>(key,data));
			return data;
		}
		else
		{
			return it->second;
		}
	}

protected:
	// constructor
	Flyweight(void) = default;

	// destructor
	virtual ~Flyweight(void) = default;

private:
	std::map<Key,TData> container_;

	virtual Data* Create(const Key& key) = 0;
};

} // namespace base
} // namespace common

#endif // _FLYWEIGHT_H_

//---------------------------------- EOF --------------------------------------
