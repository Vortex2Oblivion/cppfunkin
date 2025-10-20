#pragma once

#include "object.hpp"
#include <algorithm>

namespace engine
{
    template <typename T = Object>
    class Group : public Object
    {
        static_assert(std::is_base_of<Object, T>::value, "T must inherit from Object");

    private:
        /* data */
    public:
        std::vector<T *> members = {};
        raylib::Vector2 position = raylib::Vector2(0, 0);
        Group(/* args */);
        Group(float x, float y);
        ~Group();
        virtual void remove(T *obj);
        virtual void add(T *obj);
        virtual void update(float delta);
        virtual void draw();
        virtual void draw(float x, float y);
        virtual void addToFront(T *obj);
    };
    template <typename T>
    engine::Group<T>::Group() : Object()
    {
    }

    template <typename T>
    engine::Group<T>::Group(float x, float y) : Object(x, y)
    {
    }

    template <typename T>
    engine::Group<T>::~Group()
    {
        while (members.begin() != members.end()) {
            typename std::vector<T*>::iterator iter = members.begin();
            delete *iter;
            members.erase(members.begin());
        }

        // for (auto member : members)
        // {
        //     if (!member->alive || member == nullptr)
        //     {
        //         continue;
        //     }
        //     remove(member);
        //     delete member;
        // }
        // members.clear();
    }

    template <typename T>
    void engine::Group<T>::draw(float x, float y)
    {
        for (auto member : members)
        {
            if (member == nullptr || !member->alive)
            {
                continue;
            }
            member->draw(position.x + x, position.y + y);
        }
    }

    template <typename T>
    void engine::Group<T>::draw()
    {
        draw(0, 0);
    }

    template <typename T>
    void engine::Group<T>::remove(T *obj)
    {
        members.erase(find(members.begin(), members.end(), obj));
    }

    template <typename T>
    void engine::Group<T>::addToFront(T *obj)
    {
        members.insert(members.begin(), obj);
    }

    template <typename T>
    void engine::Group<T>::add(T *obj)
    {
        members.push_back(obj);
    }

    template <typename T>
    void engine::Group<T>::update(float delta)
    {
        for (auto member : members)
        {
            if (member == nullptr || !member->alive)
            {
                continue;
            }
            member->update(delta);
        }
    }

} // namespace engine
