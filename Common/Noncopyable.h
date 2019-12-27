#ifndef GAMERAY_NONCOPYABLE_H_
#define GAMERAY_NONCOPYABLE_H_

#include "Building.h"

namespace GameRay
{
	class GAMERAY_CORE_API Noncopyable
	{
	public:
		Noncopyable() = default;
		~Noncopyable() = default;
		Noncopyable(const Noncopyable&) = default;
		Noncopyable& operator=(Noncopyable&) = default;
	};
}

#endif
