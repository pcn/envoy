#include "common/memory/stats.h"

#include <cstdint>

#ifdef TCMALLOC

#include "gperftools/malloc_extension.h"

namespace Envoy {
namespace Memory {

uint64_t Stats::totalCurrentlyAllocated() {
  size_t value = 0;
  MallocExtension::instance()->GetNumericProperty("generic.current_allocated_bytes", &value);
  return value;
}

uint64_t Stats::totalCurrentlyReserved() {
  size_t value = 0;
  MallocExtension::instance()->GetNumericProperty("generic.heap_size", &value);
  return value;
}

} // Memory
} // Envoy

#else

namespace Envoy {
namespace Memory {

uint64_t Stats::totalCurrentlyAllocated() { return 0; }
uint64_t Stats::totalCurrentlyReserved() { return 0; }

} // Memory
} // Envoy

#endif // #ifdef TCMALLOC
