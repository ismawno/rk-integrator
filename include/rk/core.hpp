#ifndef RK_CORE_HPP
#define RK_CORE_HPP

#if !defined(HAS_DEBUG_LOG_TOOLS) && !defined(HAS_DEBUG_MACROS)
#define HAS_DEBUG_MACROS
#define DBG_SET_LEVEL(...)
#define DBG_SET_PATTERN(...)

#define DBG_TRACE(...)
#define DBG_DEBUG(...)
#define DBG_INFO(...)
#define DBG_WARN(...)
#define DBG_ERROR(...)
#define DBG_CRITICAL(...)
#define DBG_FATAL(...)

#define DBG_ASSERT_TRACE(...)
#define DBG_ASSERT_DEBUG(...)
#define DBG_ASSERT_INFO(...)
#define DBG_ASSERT_WARN(...)
#define DBG_ASSERT_ERROR(...)
#define DBG_ASSERT_CRITICAL(...)
#define DBG_ASSERT_FATAL(...)
#endif

#if !defined(HAS_PROFILE_TOOLS) && !defined(HAS_PROFILE_MACROS)
#define HAS_PROFILE_MACROS
#define PERF_BEGIN_SESSION(...)
#define PERF_END_SESSION(...)
#define PERF_SCOPE(...)
#define PERF_FUNCTION(...)
#define PERF_PRETTY_FUNCTION(...)
#define PERF_SET_MAX_FILE_MB(...)
#define PERF_SET_EXTENSION(...)
#endif

#ifdef HAS_ALLOCATORS
#include "mem/stack_allocator.hpp"
#include "mem/block_allocator.hpp"
#include <vector>

namespace rk
{
    template <typename T>
    using stk_vector = std::vector<T, mem::stack_allocator<T>>;

    template <typename T>
    using blk_vector = std::vector<T, mem::block_allocator<T>>;
}
#else

#include <memory>
namespace rk
{
    template <typename T>
    using stk_vector = std::vector<T>;

    template <typename T>
    using blk_vector = std::vector<T>;
}

#endif

#endif