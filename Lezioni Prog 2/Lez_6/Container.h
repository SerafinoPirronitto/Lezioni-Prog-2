#pragma once

template <typename T>
class IContainer
{
    static_assert(std::is_copy_constructible<T>::value && std::is_move_constructible<T>::value && std::is_copy_assignable<T>::value && std::is_move_assignable<T>::value);

public:
    virtual void insert(const T &element) = 0;
    virtual void insert(const T &element, size_t index) = 0;
    virtual T remove(const T &element) = 0;
    virtual T remove(size_t index) = 0;
    virtual void clear() = 0;
    virtual size_t size() const = 0;

    virtual ~IContainer() {};
};