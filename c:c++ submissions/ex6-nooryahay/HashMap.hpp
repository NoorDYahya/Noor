//
// Created by noor dar yahya on 11/06/2022.
//

#ifndef EX6_NOORYAHYA_HASHMAP_HPP
#define EX6_NOORYAHYA_HASHMAP_HPP

#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <functional>

#define HASH_MAP_INITIAL_CAP 16
#define HASH_MAP_GROWTH_FACTOR 2
#define HASH_MAP_MIN_LOAD_FACTOR 0.25
#define HASH_MAP_MAX_LOAD_FACTOR 0.75

template<class KeyT, class ValueT>
class HashMap
{
private:

    std::vector<std::pair<KeyT, ValueT>> *buckets_;
    int size_;
    int capacity_;


public:


    class ConstIterator;

    ConstIterator begin() const
    { return ConstIterator(this, 0); }

    ConstIterator end() const
    { return ConstIterator(this, 1); }

    ConstIterator cbegin() const
    { return ConstIterator(this, 0); }

    ConstIterator cend() const
    { return ConstIterator(this, 1); }

    int hash_map_func(const KeyT &k)
    {

        return std::hash<KeyT>()(k) && (capacity_ - 1);
    }

    HashMap()
    {

        size_ = 0;
        capacity_ = HASH_MAP_INITIAL_CAP;
        buckets_ = nullptr;

    }

    HashMap(std::vector<KeyT> &keys, std::vector<ValueT> &vals)
    {
        if (keys.size() != vals.size())
        {
            throw std::out_of_range("There is no matching number of vals"
                                    " and"
                                    " keys.");
        }
        capacity_ = HASH_MAP_INITIAL_CAP;
        size_ = 0;
        buckets_ = new std::vector<std::pair<KeyT, ValueT>>
        [HASH_MAP_INITIAL_CAP];
        for (size_t i = 0; i < keys.size(); i++)
        {
            bool t = insert(keys[i], vals[i]);
            if (!t)
            {
                int k = hash_map_func(keys[i]);
                for (auto &v : buckets_[k])
                {
                    if (v.first == keys[i])
                    {
                        v.second = vals[i];
                    }
                }
            }
        }


    }

    HashMap(const HashMap<KeyT, ValueT> &hash_map)
    {
        if (hash_map.empty())
        {
            size_ = hash_map.size_;
            capacity_ = hash_map.capacity_;
        } else
        {
            size_ = hash_map.size_;
            capacity_ = hash_map.capacity_;
            buckets_ = new std::vector<std::pair<KeyT, ValueT>>[capacity_];
            for (int i = 0; i < capacity_; i++)
            {
                for (auto &v : hash_map.buckets_[i])
                {
                    buckets_[i].push_back(v);
                }
            }
        }


    }

    virtual ~HashMap()
    {

        if (size_ != 0)
        {
            size_ = 0;
            delete[] buckets_;
        }
    }
    int calculate_cap(int resize);
    HashMap &operator=(const HashMap<KeyT, ValueT> &hash_map);

    ValueT &operator[](const KeyT &k);

    const ValueT &operator[](const KeyT &k) const;

    int size() const
    { return size_; }

    int capacity() const
    { return capacity_; }

    bool empty() const
    { return size_ == 0; }

    bool insert(const KeyT &key, const ValueT &val);

    double get_load_factor()
    {

        double t = (double) size_ / capacity_;
        return t;
    }

    bool contains_key(const KeyT &k);

    ValueT &at(const KeyT &k);

    ValueT &at(const KeyT &k) const;

    int bucket_size(const KeyT &k);

    int bucket_index(const KeyT &k);

    virtual bool erase(const KeyT &k);

    bool operator==(const HashMap<KeyT, ValueT> &lhs);

    bool operator!=(const HashMap<KeyT, ValueT> &lhs);

    void clear();


    class ConstIterator
    {

    private:
        const HashMap<KeyT, ValueT> *hash_;
        int bucket_ind;// cuurent bucket index
        int pair_ind;
    public:
        friend class HashMap<KeyT,ValueT>;
        typedef const std::pair<KeyT, ValueT> const_value_type;
        typedef const std::pair<KeyT, ValueT> &const_reference;
        typedef const std::pair<KeyT, ValueT> *const_pointer;
        typedef const std::forward_iterator_tag iterator_category;

        ConstIterator(const HashMap<KeyT, ValueT> *hash, bool end)
        {
            this->hash_ = hash;
            if (hash_->size_ == 0)
            {
                bucket_ind = hash_->capacity_ + 1;
            } else
            {
                if (end)
                {

                    bucket_ind = -1 ;
                    pair_ind = -1;

                } else
                {
                    for (int i = 0; i < hash_->capacity_; i++)
                    {
                        if (!(hash_->buckets_[i].empty()))
                        {

                            bucket_ind = i;
                            pair_ind = 0;
                            break;
                        }
                    }
                }
            }
        }

        ConstIterator(const ConstIterator &it)
        {
            hash_ = it.hash_;
            bucket_ind = it.bucket_ind;
            pair_ind = it.pair_ind;
        }

        const_reference operator*() const
        {
            if(pair_ind!=-1 && bucket_ind!=-1)
            {
                return hash_->buckets_[bucket_ind][pair_ind];
            }

        }

        const_pointer operator->() const
        { return &(*(*this)); }

        ConstIterator &operator++()
        {
            pair_ind++;
            auto t = (hash_->buckets_[bucket_ind]).size();
            if (t <= pair_ind)
            {
                for (int i = bucket_ind + 1; i < hash_->capacity_; i++)
                {
                    if (!(hash_->buckets_[i].empty()))
                    {
                        bucket_ind = i;
                        pair_ind = 0;
                        return *this;
                    }
                }
                bucket_ind = -1;
                pair_ind =-1;
                return *this;
            }
            return *this;

        }

        ConstIterator operator++(int)
        {
            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const ConstIterator &a)
        {
            return a.hash_ == hash_ && a.bucket_ind == bucket_ind && a.pair_ind
            ==pair_ind;
        };

        bool operator!=(const ConstIterator a)
        { return !(*this == a); };
    };
};

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT> &
HashMap<KeyT, ValueT>::operator=(const HashMap<KeyT, ValueT> &hash_map)
{
    if (this == &hash_map)
    {
        return *this;
    }
    size_ = hash_map.size_;
    capacity_ = hash_map.capacity_;
    auto tmp_buket = new std::vector<std::pair<KeyT, ValueT>>[capacity_];
    for (int i = 0; i < capacity_; i++)
    {
        for (auto &v : hash_map.buckets_[i])
        {
            tmp_buket[i].push_back(v);
        }
    }
    delete[] buckets_;
    buckets_ = tmp_buket;
    return *this;

}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::insert(const KeyT &key, const ValueT &val)
{
    if (contains_key(key))
    {
        return false;
    }
    const std::pair<KeyT, ValueT> pair = std::make_pair(key, val);
    size_++;
    if (get_load_factor() > HASH_MAP_MAX_LOAD_FACTOR)
    {

        int old_cap = capacity_;
        capacity_ = calculate_cap(0);
        auto tmp = new std::vector<std::pair<KeyT, ValueT>>
        [capacity_];
        for (int i = 0; i < old_cap; i++)
        {
            if (!buckets_[i].empty())
            {
                for (auto &m : buckets_[i])
                {
                    int ind_1 = hash_map_func(m.first);
                    tmp[ind_1].push_back(m);

                }
            }
        }
        delete[] buckets_;
        int ind = hash_map_func(key);
        std::swap(buckets_, tmp);
        buckets_[ind].push_back(pair);
        return true;


    }
    int ind = hash_map_func(key);
    if (size_ == 1 && capacity_ == HASH_MAP_INITIAL_CAP)
    {
        buckets_ = new std::vector<std::pair<KeyT, ValueT>>[capacity_];
    }
    buckets_[ind].push_back(pair);
    return true;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::contains_key(const KeyT &k)
{
    if (size_ == 0)
    {
        return false;
    }
    int ind = hash_map_func(k);
    for (auto &v : buckets_[ind])
    {
        if (v.first == k)
        {
            return true;
        }
    }
    return false;
}


template<class KeyT, class ValueT>
ValueT &HashMap<KeyT, ValueT>::operator[](const KeyT &k)
{
    std::pair<KeyT,ValueT> *p ;

    if (!contains_key(k))
    {
        int t = hash_map_func(k);
        insert(k, ValueT());
        for (auto &v : buckets_[t])
        {
            if (v.first == k)
            {
                p = &v;
                break;
            }
        }
        return p->second;


    } else
    {

        int ind = hash_map_func(k);
        for (auto &v : buckets_[ind])
        {
            if (v.first == k)
            {
                p =&v;
                break;

            }
        }
        return p->second;

    }


}

template<class KeyT, class ValueT>
const ValueT &HashMap<KeyT, ValueT>::operator[](const KeyT &k) const
{

    int ind = hash_map_func(k);
    if (!contains_key(k))
    {
        return ValueT();
    }
    for (const auto &v : buckets_[ind])
    {
        if (v.first == k)
        {
            return v.second;
        }
    }

}

template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::bucket_size(const KeyT &k)
{
    if (!contains_key(k))
    {
        throw std::runtime_error("Key is not found");
    }
    int ind = hash_map_func(k);
    int a = buckets_[ind].size();
    return a;
}
template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::calculate_cap(int resize)
{
    if(resize)
    {
        while (get_load_factor() < HASH_MAP_MIN_LOAD_FACTOR && capacity_ >1)
        {
            capacity_ /= 2;
        }
        return capacity_;
    }
    while (get_load_factor() > HASH_MAP_MAX_LOAD_FACTOR )
    {
        capacity_ *= 2;
    }
    return capacity_;

}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::erase(const KeyT &k)
{

    if (!contains_key(k))
    {
        return false;
    }
    int ind = hash_map_func(k);
    for (const auto &v : buckets_[ind])
    {

        if (v.first == k)
        {
            buckets_[ind].erase(
                    std::remove(buckets_[ind].begin(), buckets_[ind]
                            .end(), v), buckets_[ind].end());
            size_--;
            if(size_ == 0)
            {
                capacity_ = 1;
                return true;
            }
            if (get_load_factor() < HASH_MAP_MIN_LOAD_FACTOR)
            {

                int old_cap = capacity_;
                capacity_ = calculate_cap(1);
                auto tmp = new std::vector<std::pair<KeyT, ValueT>>
                [capacity_ ];

                for (int i = 0; i < old_cap; i++)
                {
                    if (!buckets_[i].empty())
                    {
                        for (auto &m : buckets_[i])
                        {
                            int ind_1 = hash_map_func(m.first);
                            tmp[ind_1].push_back(m);

                        }
                    }
                }

                std::swap(buckets_, tmp);

                return true;
            }
        }
    }
    return false;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::operator==(const HashMap<KeyT, ValueT> &lhs)
{
    if (size_ != lhs.size_)
    {
        return false;
    }
    if (size_ == 0 && lhs.size_ == 0)
    {
//        empty buckets ;
        return true;
    }
    for (int i = 0; i < lhs.capacity_; i++)
    {

        for (auto &v: lhs.buckets_[i])
        {
            if (!contains_key(v.first))
            {
                return false;
            }
            int k = hash_map_func(v.first);
            for (auto &c: buckets_[k])
            {
                if (c.first == v.first)
                {
                    if (c.second != v.second)
                    {
                        return false;
                    }
                }
            }
        }

    }
    return true;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::operator!=(const HashMap<KeyT, ValueT> &lhs)
{
    return !((*this).operator==(lhs));
}

template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::bucket_index(const KeyT &k)
{
    if (!contains_key(k))
    {
        throw std::runtime_error("Key is not found");
    }
    return  hash_map_func(k);
}

template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::clear()
{
    for (int i = 0; i < capacity_; i++)
    {

        buckets_[i].clear();
    }
    size_ = 0;
}

template<class KeyT, class ValueT>
ValueT &HashMap<KeyT, ValueT>::at(const KeyT &k)
{
    if (!contains_key(k))
    {
        throw std::runtime_error("Key is not found");
    }
    return (*this)[k];
}

template<class KeyT, class ValueT>
ValueT &HashMap<KeyT, ValueT>::at(const KeyT &k) const
{
    if (!contains_key(k))
    {
        throw std::runtime_error("Key is not found");
    }
    return (*this)[k];
}



#endif //EX6_NOORYAHYA_HASHMAP_HPP
