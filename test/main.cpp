#include <iostream>

#include "object_pool/properties.h"
#include "object_pool/ObjectPool.h"

using namespace std;

int main() {

    std::cout << "=== test object pool ===" << std::endl;

    size_t poolSize = 100;
    ObjectPool<string, LargeObject> pool(poolSize);

    cout << " acquire object1 from pool " << endl;
    LargeObject* obj1 = pool.acquire("obj1");
    cout << " acquire object2 from pool " << endl;
    LargeObject* obj2 = pool.acquire("obj2");
    cout << " set object2 name attribute " << endl;
    obj2->setName("obj2");
    cout << " release object1 in pool " << endl;
    pool.release(obj1->name());
    cout << " object1 has been released " << endl;

    cout << " object2 in pool with name " << pool.get(obj2->name())->name() << endl;

    return 0;
}


