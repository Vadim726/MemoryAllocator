////////////////////////////////////////////////////////////////////////////
//	Created 	: 05.12.2019
//	Author		: Vadim Studnansky
//	Copyright (c) 2019 the GameRay project.
////////////////////////////////////////////////////////////////////////////

#ifndef GAMERAY_MEMORY_ALLOCATORs_H_
#define GAMERAY_MEMORY_ALLOCATORs_H_

#include "Common/Building.h"
#include "Common/TypeDefs.h"
#include "Memory.h"

namespace GameRay
{
	class GAMERAY_CORE_API DefaultAllocator
	{
	public:
		void* allocate(size_t n);
		void deallocate(void* p);
		void* reallocate(void* ptr, size_t size);

		//void* allocate_scalable(size_t size);
		//void deallocate_scalable(void* ptr);
		//void* reallocate_scalable(void* ptr, size_t size);

		void* allocate_aligned(size_t size, size_t align);
		void deallocate_aligned(void* ptr);
		void* reallocate_aligned(void* ptr, size_t size, size_t align);
	};

}

#endif
