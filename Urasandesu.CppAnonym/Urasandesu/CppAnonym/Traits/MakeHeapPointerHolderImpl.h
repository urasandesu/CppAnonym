﻿/* 
 * File: MakeHeapPointerHolderImpl.h
 * 
 * Author: Akira Sugiura (urasandesu@gmail.com)
 * 
 * 
 * Copyright (c) 2014 Akira Sugiura
 *  
 *  This software is MIT License.
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */


#pragma once
#ifndef URASANDESU_CPPANONYM_TRAITS_MAKEHEAPPOINTERHOLDERIMPL_H
#define URASANDESU_CPPANONYM_TRAITS_MAKEHEAPPOINTERHOLDERIMPL_H

#ifndef URASANDESU_CPPANONYM_SIMPLEHEAP_H
#include <Urasandesu/CppAnonym/SimpleHeap.h>
#endif

#ifndef URASANDESU_CPPANONYM_UTILITIES_HEAPDELETER_H
#include <Urasandesu/CppAnonym/Utilities/HeapDeleter.h>
#endif

#ifndef URASANDESU_CPPANONYM_TRAITS_MAKEHEAPPOINTERHOLDERIMPLFWD_H
#include <Urasandesu/CppAnonym/Traits/MakeHeapPointerHolderImplFwd.h>
#endif

namespace Urasandesu { namespace CppAnonym { namespace Traits {

    template<
        class T, 
        template<class, class, class> class PointerHolderImpl,
        class Tag
    >
    struct MakeHeapPointerHolderImpl
    {
        typedef SimpleHeap<T, Tag> object_heap_type;
        typedef Utilities::HeapDeleter<object_heap_type> object_deleter_type;
        struct deleter_type;
        typedef PointerHolderImpl<T, object_deleter_type, deleter_type> type;
        typedef SimpleHeap<type, Tag> heap_type;
        struct deleter_type : 
            Utilities::HeapDeleter<heap_type>
        {
            typedef Utilities::HeapDeleter<heap_type> base_type;
                
            deleter_type(heap_type &heap) : 
                base_type(heap)
            { }

            template<class T>
            void operator()(T *p) 
            { 
                base_type::operator()(p);
            }
        };
    };

}}}   // namespace Urasandesu { namespace CppAnonym { namespace Traits {

#endif  // #ifndef URASANDESU_CPPANONYM_TRAITS_MAKEHEAPPOINTERHOLDERIMPL_H
