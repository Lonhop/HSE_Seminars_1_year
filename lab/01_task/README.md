# Task 1: UniquePtr Implementation

## Control Questions

### 1. What is the ID of successful submission?
156911195

### 2. What problem does std::unique_ptr solve compared to raw pointers?
`std::unique_ptr` solves several problems:

1)Automatic memory management: Ensures dynamically allocated objects are automatically deleted when the pointer goes out of scope

2)Exception safety: Prevents memory leaks when exceptions are thrown

3)Clear ownership semantics: Explicitly indicates sole ownership of a resource

4)Prevents double deletion: Since ownership is unique, there's no risk of multiple pointers trying to delete the same object

5)RAII compliance: Resources are properly managed through constructor/destructor pairs

### 3. Why is copying a std::unique_ptr prohibited? What would go wrong if copying were allowed?
Copying is prohibited because `std::unique_ptr` represents exclusive ownership. If copying were allowed:

1)Two pointers would point to the same object, leading to double deletion when both destructors run

2)It would be unclear which pointer actually owns the object

3)The semantics of unique ownership would be broken

4)Resource management would become unpredictable and error-prone

### 4. What is the difference between copying and moving an object in C++?

1)Copying: Creates a new object that is a duplicate of the source. For `unique_ptr`, this would create two pointers pointing to the same resource, which is why it's disabled.

2)Moving: Transfers resources from the source to the destination. The source is left in a valid but unspecified state. For `unique_ptr`, moving transfers ownership of the managed object without copying the resource itself.

### 5. What state is a UniquePtr left in after a move operation?
After a move operation, the moved-from `UniquePtr` is left in a valid but unspecified state, typically:

1)It becomes empty

2)It no longer owns any resource

3)It can be assigned a new value or destroyed safely

4)Calling methods like `Get()` returns nullptr

### 6. What is the purpose of the Release() method? Who becomes responsible for deleting the resource after calling it?
`Release()` relinquishes ownership of the managed object and returns the raw pointer to it. After calling `Release()`:

1)The `UniquePtr` becomes empty

2)The caller becomes responsible for manually deleting the returned pointer

3)It's useful when you need to transfer ownership to raw pointer code or when interfacing with C APIs

4)The smart pointer no longer manages the resource

### 7. How does the Reset() method differ from Release()?

1)`Release()`: Simply gives up ownership and returns the pointer without deleting the managed object. The caller must manually delete the returned pointer.

2)`Reset()`: Deletes the currently owned object and then takes ownership of the new pointer 

3)`Reset()` ensures proper cleanup of old resources, while `Release()` requires manual cleanup

4)`Reset()` can be called with no arguments to delete the managed object and become empty

### 8. Why must the destructor of UniquePtr delete the owned object?
The destructor must delete the owned object to fulfill the RAII principle:

1)The pointer was created to automatically manage a resource

2)If the destructor didn't delete the object, it would cause a memory leak

3)This automatic cleanup is the primary benefit of smart pointers

4)It ensures that resources are properly released regardless of how the scope is exited

### 9. In which cases is the explicit conversion operator to bool useful?
The explicit conversion to `bool` is useful for:

1)Checking if the pointer owns an object

2)Conditional expressions that require boolean context

3)Assertions and validation

4)Guard clauses

5)Preventing implicit conversions to integer types in unintended contexts

6)Container operations that check validity

### 10. Why does std::unique_ptr introduce almost no runtime overhead compared to raw pointers?
`std::unique_ptr` introduces minimal overhead because:

1)It's a zero-cost abstraction - the compiler can optimize away the wrapper

2)Most operations are simple pointer manipulations that get inlined

3)No reference counting or virtual function calls are involved

4)The destructor call is deterministic and can be inlined

5)Memory layout is identical to a raw pointer

6)All operations are compile-time resolved

### 11. When is it preferable to use std::unique_ptr instead of std::shared_ptr?
Prefer `std::unique_ptr` when:

1)You need exclusive ownership of a resource

2)You want minimal overhead and maximum performance

3)The resource has a clear, single owner

4)You don't need to share the resource between multiple objects

5)You're implementing move-only types

6)The ownership hierarchy is simple and well-defined

7)Working with polymorphic types in factory functions

8)Implementing pImpl idiom