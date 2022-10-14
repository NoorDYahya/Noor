//
// Created by noor dar yahya on 13/06/2022.
//
#ifndef EX6_NOORYAHYA_DICTIONARY_HPP
#define EX6_NOORYAHYA_DICTIONARY_HPP

#include "HashMap.hpp"

class InvalidKey : public std::invalid_argument
{
public:
    explicit InvalidKey(const std::string &what_arg);
};


InvalidKey::InvalidKey(const std::string &what_arg) : std::invalid_argument(
        what_arg)
{

}

class Dictionary : public HashMap<std::string, std::string>
{

public:


    Dictionary()
    {};

    Dictionary(std::vector<std::string> &keys, std::vector<std::string> &vals)
            : HashMap<std::string, std::string>(keys, vals)
    {}

    using HashMap<std::string, std::string>::erase ;
     bool erase(const std::string &k) override
    {
        if (!contains_key(k))
        {
            throw InvalidKey("given key is not found");
        }
        return HashMap<std::string, std::string>::erase(k);

    }

    template<class Iter>
    void update(Iter begin, Iter end)
    {

            for (auto s = begin; s != end; ++s)
            {
                (*this)[s->first] = s->second;

            }

    }

    ~Dictionary() override
    {
        this->clear();
    }
};

#endif //EX6_NOORYAHYA_DICTIONARY_HPP
