#pragma once

#include "Internal/Graphics/Backends/vk.h"

namespace GLEEC::Internal::Graphics::vk
{
    struct pNextable
    {
        VkStructureType structureType;
        void* pNext = nullptr;
    };

    struct pNextChain
    {
        void* base = nullptr;
        void* tail = nullptr;

        pNextChain() = default;

        void add(void* newTail)
        {
            if (base == nullptr)
            {
                base = reinterpret_cast<pNextable*>(newTail);
            }

            else
            {
                reinterpret_cast<pNextable*>(tail)->pNext = newTail;
            }

            tail = newTail;
        }

        void add_front(void* newHead)
        {
            if (tail == nullptr)
            {
                tail = reinterpret_cast<pNextable*>(newHead);
            }

            else
            {
                reinterpret_cast<pNextable*>(newHead)->pNext =
                    reinterpret_cast<pNextable*>(base);
            }

            base = newHead;
        }

        template <typename T>
        void add(T& newTail)
        {
            add(&newTail);
        }

        template <typename T>
        void add_front(T& newHead)
        {
            add_front(&newHead);
        }

        void apply(void* info)
        {
            reinterpret_cast<pNextable*>(info)->pNext = base;
        }

        template <typename T>
        void apply(T& info)
        {
            info.pNext = base;
        }
    };
}
