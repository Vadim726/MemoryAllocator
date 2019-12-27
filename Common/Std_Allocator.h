////////////////////////////////////////////////////////////////////////////
//	Created 	: 05.12.2019
//	Author		: Vadim Studnansky
//	Copyright (c) 2019 the GameRay project.
////////////////////////////////////////////////////////////////////////////

#ifndef GAMERAY_STD_ALLOCATOR_H_
#define GAMERAY_STD_ALLOCATOR_H_

#include "Building.h"
#include "Memory/Memory.h"

namespace GameRay
{
	namespace Std
	{
		template <typename T>
		class StdAlloc final : public Memory::IAllocator
		{
		public:
			using reference = T &;
			using const_reference = const T &;
			using value_type = T;

			template <class Other>
			struct rebind { using other = StdAlloc<Other>; };

			void* address(reference ref) const { return &ref; }
			const void* address(const_reference ref) const { return &ref; }

			StdAlloc() = default;
			StdAlloc(const StdAlloc<T>&) = default;

			template <class Other>
			StdAlloc(const StdAlloc<Other>&) { }
			template <class Other>
			StdAlloc& operator=(const StdAlloc<Other>&) { return *this; }

			static void* allocate(size_t n) { return alloc<T>(n); }
			static void deallocate(void* p) { dealloc(p); }

			template <class U, class... Args>
			static void construct(U* ptr, Args&& ... args) { new (ptr) U(std::forward<Args>(args)...); }

			static constexpr size_t max_size()
			{
				constexpr auto count = std::numeric_limits<size_t>::max() / sizeof(T);
				return count > 0 ? count : 1;
			}
		};

		template <class T, class Other>
		bool operator==(const StdAlloc<T>&, const StdAlloc<Other>&)
		{
			return true;
		}

		template <class T, class Other>
		bool operator!=(const StdAlloc<T>&, const StdAlloc<Other>&)
		{
			return false;
		}

	}
}

#endif
