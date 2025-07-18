#include <iostream>

#include "modules/auto_singleton/properties.hpp"
#include "modules/auto_singleton/AutoSingleton.hpp"


#include "modules/object_pool/properties.hpp"
#include "modules/object_pool/ObjectPool.hpp"

#include "modules/thread_pool/properties.hpp"
#include "modules/thread_pool/ThreadPool.hpp"
#include "modules/thread_pool/pool_manager/PoolManager.hpp"
#include "modules/thread_pool/pool_manager/PoolRequest.hpp"

using namespace std;

int main() {

    std::cout << "=== test auto singleton ===" << std::endl;

    auto& service = AutoSingleton<MyService>::get();
    service.run();
    //optional: manually destroy early
    AutoSingleton<MyService>::destroy();

    std::cout << "=== end test auto singleton ===\n\n" << std::endl;



    std::cout << "=== test object pool ===" << std::endl;

    size_t poolSize = 100;
    ObjectPool<string, LargeObject> objectPool(poolSize);

    cout << " acquire object1 from pool " << endl;
    LargeObject* obj1 = objectPool.acquire("obj1");
    cout << " acquire object2 from pool " << endl;
    LargeObject* obj2 = objectPool.acquire("obj2");
    cout << " set object2 name attribute " << endl;
    obj2->setName("obj2");
    cout << " release object1 in pool " << endl;
    objectPool.release(obj1->name());
    cout << " object1 has been released " << endl;

    cout << " object2 in pool with name " << objectPool.get(obj2->name())->name() << endl;

    std::cout << "=== end test object pool ===\n\n" << std::endl;




    std::cout << "=== test thread pool ===" << std::endl;

    PoolManager manager;

    // Create the argument holders
    Arguments args;
    args.add(3);
    args.add(5);

    Arguments args2;
    args2.add(3);
    args2.add(4);

    Arguments args3;
    args3.add(string("Coco"));

    // Package them in a request
    const PoolRequest request(PoolRequest::POOL_TYPE::COMPUTE, args);
    const PoolRequest request2(PoolRequest::POOL_TYPE::LOGGING, args2);
    const PoolRequest request3(PoolRequest::POOL_TYPE::COMPUTE, args3);

    // Submit the function and get the result
    auto future = manager.submit(request, add);
    auto future2 = manager.submit(request2, print_sum);
    auto future3 = manager.submit(request3, greet);

    std::cout << "Result future1: " << future.get() << std::endl;
    std::cout << "Result future2: " << future2.get() << std::endl;
    std::cout << "Result future3: " << future3.get() << std::endl;

    std::cout << "=== end test thread pool ===" << std::endl;

    return 0;
}


