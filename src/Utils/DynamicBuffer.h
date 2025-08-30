#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct s_DynamicBuffer
{
  // Size of each element stored in the buffer.
  size_t elementSize;

  // Number of elements to additionally allocate for each time buffer expands.
  size_t mallocIncrements;
  
  // The current buffer size (in elements).
  size_t bufferSize;
  
  // The current length of the buffer:
  size_t length;
  
  // The malloced buffer itself.
  void* buffer;
} DynamicBuffer;


// Construct a new dynamic buffer.
DynamicBuffer DB_Create(size_t elementSize, size_t mallocIncrements);

// Free a dynamic buffer.
void DB_Free(DynamicBuffer* buffer);

/// Resize a dynamic buffer to the given number of elements.
bool DB_Resize(DynamicBuffer* buffer, size_t newSize);

/// Get a pointer to the n-th element in the buffer.
void* DB_Get(const DynamicBuffer buffer, size_t index);

/// Push a new value to the end of the buffer. Handles resizing.
bool DB_Append(DynamicBuffer* buffer, void* elem);

/// Trim the buffer to the current length, and release the array to the caller.
/// The caller takes ownership and must handle freeing it themselves.
void* DB_Release(DynamicBuffer* buffer);
