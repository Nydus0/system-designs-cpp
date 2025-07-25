# design-patterns-cpp

Describes several implementations of c++ patterns with specific custom features.

- Auto-singleton:
  * singleton class in modern c++ style
  * provides an optional manual deletion of the singleton class 

- BiMap:
  * simple bimap
    * ensure 1 to 1 key/value
    * O(log(N)) search for keys and values
    * O(log(N)) removals
  * multi bimap : 
    * allow multiple keys and multiple values
    * O(log(N)) search for keys and values
    * removals are longer (logarithmic search then loop on the several matches)

- Object pool:
  * fast pool element access by key
  * RAII with unique_ptr
  * concept guard for pool elements (elements must have a reset() function)

- Thread pool:
  * pool manager assigns pool requests to threadpools, depending on pool type
  * thread pool receives functions and arguments separately and binds them to execute its task

- Thread safe containers:
  * vector : stores data with read/write locks methods
  * fifo : implements a queue with a wait mechanism


## Build Instructions
This project uses [CMake](https://cmake.org/) for compilation.  
It generates a library from the directory **modules**.

## Running Tests
Test suite uses the [GoogleTest](https://github.com/google/googletest) framework (automatically downloaded via CMake when building).  
Run Cmake target "tests".

## License
This project is licensed under the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.html).  
By using or modifying this code, you agree to release any derivative work under the same license.