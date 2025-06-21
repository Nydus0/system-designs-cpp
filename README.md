# design-patterns-cpp

Describes several implementations of design patterns with specific custom features.

Object Pool :
- fast pool element access by key
- RAII with unique_ptr
- concept guard for pool elements (elements must have a reset() function)

Thread Pool:
- pool manager assigns pool requests to threadpools, depending on pool type
- thread pool receives functions and arguments separately and binds them to execute its task

