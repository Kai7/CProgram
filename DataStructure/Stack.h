template<class KeyType>
#define DefaultSize 1024

class Stack{
public:
    Stack(int MaxStackSize = DefaultSize);
    bool isFull();
    bool isEnpty();
    void push(const KeyType& item);
    KeyType *pop(KeyType&);
private:
    int top;
    KeyType *stack;
    int maxSize;
};
