#include "DynamicBuffer.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Construct a new dynamic buffer.
DynamicBuffer DB_Create(size_t elementSize, size_t mallocIncrements)
{
  return (DynamicBuffer)
  {
    .elementSize = elementSize,
    .mallocIncrements = mallocIncrements,
    .bufferSize = 0,
    .length = 0,
    .buffer = NULL,
  };
}

// Free a dynamic buffer.
void DB_Free(DynamicBuffer* buffer)
{
  free(buffer->buffer);
  buffer->bufferSize = 0;
  buffer->length = 0;
  buffer->buffer = NULL;
}

/// Resize a dynamic buffer to the given number of elements.
bool DB_Resize(DynamicBuffer* buffer, size_t newSize)
{
  if (newSize == 0)
  {
    DB_Free(buffer);
    return true;
  }

  if (newSize == buffer->bufferSize)
  {
    return true;
  }

  const size_t newSizeBytes = buffer->elementSize * newSize;
  void* newBuffer = realloc(buffer->buffer, newSizeBytes);

  if (!newBuffer)
  {
    fprintf(
      stderr, "Failed to resize dynamic buffer from %zu to %zu bytes\n",
      buffer->bufferSize * buffer->elementSize, newSizeBytes
    );
    return false;
  }

  buffer->buffer = newBuffer;
  buffer->bufferSize = newSize;

  return true;
}

/// Get a pointer to the n-th element in the buffer.
void* DB_Get(const DynamicBuffer buffer, size_t index)
{
  if (buffer.buffer == NULL) return NULL;
  if (index >= buffer.bufferSize) return NULL;

  const size_t offset = index * buffer.elementSize;

  return (void*)((char*)buffer.buffer + offset);
}

/// Push a new value to the end of the buffer. Handles resizing.
bool DB_Append(DynamicBuffer* buffer, void* elem)
{
  if (buffer->length >= buffer->bufferSize)
  {
    if (!DB_Resize(buffer, buffer->bufferSize + buffer->mallocIncrements)) return false;
  }
  
  void* slot = DB_Get(*buffer, buffer->length);
  if (!slot) return false;

  memcpy(slot, elem, buffer->elementSize);
  buffer->length++;

  return true;
}

/// Trim the buffer to the current length, and release the array to the caller.
/// The caller takes ownership and must handle freeing it themselves.
void* DB_Release(DynamicBuffer* buffer)
{
  if (!DB_Resize(buffer, buffer->length)) return NULL;
  void* array = buffer->buffer;

  buffer->bufferSize = 0;
  buffer->buffer = NULL;
  buffer->length = 0;

  return array;
}

