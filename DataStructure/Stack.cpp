#include "Stack.h"
template<class KeyType>

Stack<KeyType>::Stack(int MaxStackSize){
    stack = new KeyType[MaxStackSize];
    top = -1;
}
