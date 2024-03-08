#include <common/Common.hpp>
#include <platform/new.hpp>

template <class T, typename R>
class InputHandler0 {
public:
    InputHandler0(T* pOwner, R (T::*pInputFunc)()) : owner(pOwner), handle(pInputFunc) {}
    virtual R operator()() { return (owner->*handle)(); }

    T* owner;
    R (T::*handle)();

    static InputHandler0* construct(T* pOwner, R (T::*pInputFunc)(), void* buffer) {
        return new(buffer) InputHandlerEx(pOwner, pInputFunc);
    }
};

template <class T, typename R, typename A1>
class InputHandler1 {
public:
    InputHandler1(T* pOwner, R (T::*pInputFunc)(A1)) : owner(pOwner), handle(pInputFunc) {}
    virtual R operator()(A1 arg1) { return (owner->*handle)(arg1); }

    T* owner;
    R (T::*handle)(A1);

    static InputHandler1* construct(T* pOwner, R (T::*pInputFunc)(A1), void* buffer) {
        return new(buffer) InputHandler1(pOwner, pInputFunc);
    }
};

template <class T, typename R, typename A1, typename A2>
class InputHandler2 {
public:
    InputHandler2(T* pOwner, R (T::*pInputFunc)(A1, A2)) : owner(pOwner), handle(pInputFunc) {}
    virtual R operator()(A1 arg1, A2 arg2) { return (owner->*handle)(arg1, arg2); }

    T* owner;
    R (T::*handle)(A1, A2);

    static InputHandler2* construct(T* pOwner, R (T::*pInputFunc)(A1, A2), void* buffer) {
        return new(buffer) InputHandler2(pOwner, pInputFunc);
    }
};

template <class T, typename R, typename A1, typename A2, typename A3>
class InputHandler3 {
public:
    InputHandler3(T* pOwner, R (T::*pInputFunc)(A1, A2, A3)) : owner(pOwner), handle(pInputFunc) {}
    virtual R operator()(A1 arg1, A2 arg2, A3 arg3) { return (owner->*handle)(arg1, arg2, arg3); }

    T* owner;
    R (T::*handle)(A1, A2, A3);

    static InputHandler3* construct(T* pOwner, R (T::*pInputFunc)(A1, A2, A3), void* buffer) {
        return new(buffer) InputHandler3(pOwner, pInputFunc);
    }
};
