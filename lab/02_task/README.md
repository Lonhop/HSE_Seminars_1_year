# Task 2: SharedPtr Implementation

## Control Questions

### 1. What is the ID of successful submission?
156915140

### 2. What problem does std::shared_ptr solve compared to raw pointers?
`std::shared_ptr` solves several problems:

1)Automatic memory management with shared ownership semantics

2)Reference counting to track how many pointers own an object

3)Automatic deletion when the last owner is destroyed

4)Thread-safe reference counting

5)Prevents dangling pointers and double deletion

6)RAII compliance for shared resources

7)Enables weak pointers to break cyclic dependencies

### 3. How does shared ownership differ from unique ownership?

1)Unique ownership: One pointer exclusively owns the resource. When the pointer is destroyed, the resource is immediately deleted. Cannot be copied, only moved. Simple and efficient with no overhead.

2)Shared ownership: Multiple pointers can own the same resource. The resource is deleted only when the last owner is destroyed. Can be copied, which increments reference count. Has overhead for reference counting and thread safety.

### 4. What is a reference counter and how is it used in std::shared_ptr?
A reference counter is a separate dynamically allocated integer that tracks how many `shared_ptr` instances own a particular object. It is:

1)Incremented when a new `shared_ptr` shares ownership

2)Decremented when a `shared_ptr` is destroyed or reset

3)Checked to determine when to delete the managed object

4)Stored in a control block separate from the managed object

5)Typically implemented with atomic operations for thread safety

### 5. What happens to the managed object when one of several SharedPtr instances is destroyed?
When a `SharedPtr` is destroyed:
1. The reference counter is decremented by 1

2. If the counter becomes 0
    
    2.1)The managed object is deleted
    
    2.2)The control block  is deleted
3. If the counter is still > 0:

    3.1)The object continues to exist

    3.2)Other `SharedPtr` instances still have valid ownership

### 6. What is the difference between copy construction and move construction for SharedPtr?

1)Copy construction: Creates a new `SharedPtr` that shares ownership with the source. Reference counter is incremented. Both pointers now own the object.

2)Move construction: Transfers ownership from source to destination. Reference counter is not changed. Source becomes null. More efficient as no atomic increment needed.

### 7. Why must the reference counter be decremented in the destructor?
The destructor must decrement the reference counter to maintain accurate ownership count. If we didn't decrement:

1)The counter would never reach 0 even when all owners are gone

2)Managed objects would never be deleted

3)Resources would be held indefinitely

4)The program would have undefined behavior due to resource exhaustion

### 8. In which cases is the explicit conversion operator to bool useful?
The explicit conversion to bool is useful for:

1)Checking if the pointer owns an object

2)Conditional expressions

3)Assertions

4)Guard clauses

5)Container operations

6)Preventing implicit conversions to integers in unintended contexts

### 9. Why does std::shared_ptr usually have higher overhead than std::unique_ptr?
`std::shared_ptr` has higher overhead because:

1)Memory overhead: Stores both object pointer and reference counter pointer 

2)Dynamic allocation: Reference counter must be allocated on the heap separately

3)Atomic operations: Thread-safe reference counting requires atomic increments/decrements with memory barriers

4)Control block: May store additional data like custom deleters and weak counters

5)Cache effects: Object and control block may be in different cache lines

6)Virtual dispatch: Some implementations use virtual functions for type erasure

### 10. When is it preferable to use std::shared_ptr instead of std::unique_ptr?
Prefer `std::shared_ptr` when:

1)Multiple objects need to share ownership of a resource

2)The resource lifetime is determined by the last user

3)You have complex ownership graphs

4)Implementing the Observer pattern or slot systems

5)Working with callback systems where ownership is unclear

6)The resource needs to be cached and shared across components

7)Need weak pointers to break reference cycles

8)In multithreaded environments with shared data

9)When ownership lifetime is truly unpredictable