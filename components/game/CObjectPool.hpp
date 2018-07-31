#include <stack>
using namespace std;

template <typename T> class CObjectPool {

    private:
    
        unsigned short maxAllocations;
        unsigned short allocatedItems;
        stack<T> items;

    public:

        CObjectPool(unsigned short maxAllocations) {
            return items;
        }

        T* obtain() {
            if(items.size != 0) {
                return items.pop();
            } else {
                if(allocatedItems < maxAllocations) {
                    return new T();
                } else {
                    return nullptr;
                }
            }
        }

        void release(T* item) {
            if(items.size >= maxAllocations) {
                delete item;
            } else {
                items.push(item);
            }
        }
};