#include "Serializer.hpp"
#include "Data.hpp"

int main()
{
    Data data("Hello Kakiba!");
    Data *ptr = &data;
    uintptr_t rawPtr = Serializer::serialize(ptr);
    std::cout << "rawPtr: " << rawPtr << std::endl;
    std::cout << "DataPtr: " << ptr << std::endl;
    std::cout << "DataValue: " << ptr->getData() << std::endl;
    Data *ptr2 = Serializer::deserialize(rawPtr);
    std::cout << "DeserializedPtr: " << ptr2 << std::endl;
    std::cout << "DeserializedValue: " << ptr2->getData() << std::endl;
    std::cout << "rawPtr == DeserializedPtr: " << (rawPtr == (uintptr_t)ptr2) << std::endl;
    std::cout << "DataValue == DeserializedValue: " << (ptr->getData() == ptr2->getData()) << std::endl;
    
}