////////////////////////////////////////////////////////////////////////////
//	Created 	: 05.12.2019
//	Author		: Vadim Stydnansky
//	Copyright (c) 2019 the GameRay project.
////////////////////////////////////////////////////////////////////////////

#include "Memory_BaseAllocator.h"

#include <stdlib.h>
#ifndef _WIN32
#include <string.h>
#include <malloc.h>
#endif

#ifndef _WIN32
#	include <new>
#endif

//#include "tbb/scalable_allocator.h"

namespace GameRay
{
	void* DefaultAllocator::allocate(size_t n)
	{
		return malloc(n);
	}


	void DefaultAllocator::deallocate(void* p)
	{
		free(p);
	}


	void* DefaultAllocator::reallocate(void* ptr, size_t size)
	{
		return realloc(ptr, size);
	}

	/*
	void* DefaultAllocator::allocate_scalable(size_t size)
	{
		 return scalable_malloc(size);
	}

	void DefaultAllocator::deallocate_scalable(void* ptr)
	{
		 scalable_free(ptr);
	}

	void* DefaultAllocator::reallocate_scalable(void* ptr, size_t size)
	{
		 return scalable_realloc(ptr, size);
	}
	*/

#ifdef _WIN32
	void* DefaultAllocator::allocate_aligned(size_t size, size_t align)
	{
		return _aligned_malloc(size, align);
	}


	void DefaultAllocator::deallocate_aligned(void* ptr)
	{
		_aligned_free(ptr);
	}


	void* DefaultAllocator::reallocate_aligned(void* ptr, size_t size, size_t align)
	{
		return _aligned_realloc(ptr, size, align);
	}
#else
	void* DefaultAllocator::allocate_aligned(size_t size, size_t align)
	{
		return _aligned_malloc(align, size);
	}


	void DefaultAllocator::deallocate_aligned(void* ptr)
	{
		free(ptr);
	}


	void* DefaultAllocator::reallocate_aligned(void* ptr, size_t size, size_t align)
	{
		if (size == 0)
		{
			free(ptr);
			return nullptr;
		}
		void* newptr = _aligned_malloc(align, size);
		if (newptr == nullptr)
		{
			return nullptr;
		}
		memcpy(newptr, ptr, malloc_usable_size(ptr));
		free(ptr);
		return newptr;
	}
#endif

}
