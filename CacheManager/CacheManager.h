//
// Created by magshimim on 8.1.2020.
//
#pragma once
#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

#include <list>
#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <list>

using namespace std;

template <class Object> class CacheManager {
protected:
    mutable pthread_mutex_t mutex;
public:
    virtual Object get(string) = 0;
    virtual void insert(string, Object) = 0;
    virtual bool isExsist(string) = 0;
    virtual ~CacheManager(){}
};

#endif //EX4_CACHEMANAGER_H
