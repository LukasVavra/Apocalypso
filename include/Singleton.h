#pragma once

template <class T>
class Singleton
{
    public:
        inline static T& instance()
        {
            static T singleton;
            return singleton;
        }

    protected:
        Singleton<T>() = default;
        Singleton<T>(const Singleton<T>&) = delete;
        Singleton<T>& operator=(const Singleton<T>&) = delete;
        Singleton<T>(Singleton<T>&&) = delete;
        Singleton<T>& operator=(Singleton<T>&&) = delete;

};