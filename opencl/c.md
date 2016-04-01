# C

OpenCL C is a C99 variant in which kernels must be written.

<https://en.wikipedia.org/wiki/OpenCL#OpenCL_C_language>

C99 extensions:

- new qualifiers
- new types, in particular short vector types and image types: <https://www.khronos.org/registry/cl/sdk/2.1/docs/man/xhtml/dataTypes.html>
- new built-in functions

C99 restrictions: <https://www.khronos.org/registry/cl/sdk/2.1/docs/man/xhtml/restrictions.html>

- pointers to functions are not allowed

## Qualifiers

<https://www.khronos.org/registry/cl/sdk/1.1/docs/man/xhtml/qualifiers.html>

### __global

### __local

Shared across the work group.

### __constant

### __private

Default qualifier for arguments and local function variables: <https://www.khronos.org/registry/cl/sdk/2.1/docs/man/xhtml/global.html>

### __kernel

Marks a function that can be called from the host.

Must return `void`, <https://www.khronos.org/registry/cl/sdk/2.1/docs/man/xhtml/restrictions.html>

<https://www.khronos.org/registry/cl/sdk/2.1/docs/man/xhtml/restrictions.html>:

> Arguments to kernel functions declared in a program that are pointers must be declared with the __global, __constant, or __local qualifier. 

## Built-in functions

- <https://www.khronos.org/registry/cl/sdk/2.1/docs/man/xhtml/integerFunctions.html>
- <https://www.khronos.org/registry/cl/sdk/2.1/docs/man/xhtml/workItemFunctions.html>
- synchronization, e.g. `work_group_barrier` (ex `barrier`)

 Those may in particular take vector type arguments.
