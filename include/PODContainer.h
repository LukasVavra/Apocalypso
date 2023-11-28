#pragma once

#include <functional>
#include <algorithm>
#include <assert.h>
#include <map>

using Cache = std::map<long unsigned, int>;

template <typename T, size_t SIZE>
class PODContainer
{
public:
    /**
     * Add POD with initial value(s)
     * First item in POD must be long unsigned id
     */
    template <typename... Args>
    void add(Args &&...args)
    {
        assert(idx < SIZE && "Array index overflow");
        arr[idx] = {std::forward<Args>(args)...};
        ++idx;
    }

    /**
     * Search for id and get array index
     */
    inline int find(long unsigned id)
    {
        for (int i = 0; i < idx; i++)
        {
            if (arr[i].id == id)
            {
                return i;
            }
        }
        return -1;
    }

    /**
     * Remove POD with provided index
     *  reminder: array is not sorted anymore
     */
    inline void remove_index(int index)
    {
        assert(index >= 0 && index < idx);
        arr[index] = arr[--idx];
    }

    inline void remove(long unsigned id)
    {
        if (cache.count(id) > 0 && arr[cache[id]].id == id)
        {
            remove_index(cache[id]);
            cache.erase(id);
            return;
        }
        auto index = find(id);
        if (index >= 0)
        {
            remove_index(index);
            if (cache.count(id))
            {
                cache.erase(id);
            }
        }
    }

    /**
     * Get item ptr by id using cache
     */
    inline T *get(long unsigned id)
    {
        if (cache.count(id) > 0 && arr[cache[id]].id == id)
        {
            return &arr[cache[id]];
        }
        auto index = find(id);
        if (index < 0)
        {
            return nullptr;
        }
        cache[id] = index;
        return &arr[index];
    }

    inline size_t length()
    {
        return idx;
    }

    /**
     * Sort container with provided comparator
     */
    inline void sort(std::function<bool(const T &, const T &)> f)
    {
        std::sort(arr, arr + idx, f);
    }

    /**
     * Return forward iterator
     */
    inline auto begin()
    {
        return std::begin(arr);
    } // store index in cache

    /**
     * Return end iterator
     */
    inline auto end()
    {
        return std::begin(arr) + idx;
    }

private:
    int idx = 0;
    T arr[SIZE];
    Cache cache;
};