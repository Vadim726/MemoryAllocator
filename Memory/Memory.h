#pragma once

#include "Common/Building.h"
#include "Common/TypeDefs.h"
#include "Memory_BaseAllocator.h"

namespace GameRay
{
	class grMemory
	{
	public:
		explicit grMemory(DefaultAllocator& source);
		~grMemory();

		void* allocate(size_t size);
		void deallocate(void* ptr);
		void* reallocate(void* ptr, size_t size);

		void* allocate_scalable(size_t size);
		void deallocate_scalable(void* ptr);
		void* reallocate_scalable(void* ptr, size_t size);

		void* allocate_aligned(size_t size, size_t align);
		void deallocate_aligned(void* ptr);
		void* reallocate_aligned(void* ptr, size_t size, size_t align);

		DefaultAllocator& getSourceAllocator() { return m_source; }

	private:
		DefaultAllocator& m_source;
		volatile i32 m_allocation_count;
	};

}

extern GAMERAY_CORE_API GameRay::grMemory Memory;

template <class T>
inline T* alloc(size_t count)
{
	return (T*)Memory.allocate(count * sizeof(T));
}

template <class T>
inline void dealloc(T*& ptr) noexcept
{
	if (ptr)
	{
		Memory.deallocate((void*)ptr);
		ptr = nullptr;
	}
}
