﻿/* 
 * File: SimpleBlobTest.cpp
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


#include "stdafx.h"

#ifndef URASANDESU_CPPANONYM_COLLECTIONS_RAPIDVECTOR_HPP
#include <Urasandesu/CppAnonym/Collections/RapidVector.hpp>
#endif

#ifndef URASANDESU_CPPANONYM_SIMPLEBLOB_H
#include <Urasandesu/CppAnonym/SimpleBlob.h>
#endif

// Test.Urasandesu.CppAnonym.exe --gtest_filter=Urasandesu_CppAnonym_SimpleBlobTest.*
namespace {

    struct MyPOD1
    {
        BYTE byte1;
        BYTE byte2;
        BYTE byte3;
        BYTE byte4;
        BYTE byte5;
        BYTE byte6;
        BYTE byte7;
        BYTE byte8;
    };
    
    struct MyPOD2
    {
        INT int1;
        MyPOD1 pod1;
        PVOID pv;
        
        MyPOD2 *prev;
        MyPOD2 *next;
    };

    
    TEST(Urasandesu_CppAnonym_SimpleBlobTest, PutTTest_SucceedPath_01)
    {
        using namespace Urasandesu::CppAnonym;
        
        SimpleBlob sb;
        sb.Put<BYTE>(0x01);
        sb.Put<DWORD>(0x23456789);
        
        BYTE *pb = sb.Ptr();
        ASSERT_EQ(0x01, *pb++);
        ASSERT_EQ(0x89, *pb++);
        ASSERT_EQ(0x67, *pb++);
        ASSERT_EQ(0x45, *pb++);
        ASSERT_EQ(0x23, *pb++);
    }


    TEST(Urasandesu_CppAnonym_SimpleBlobTest, PutTTest_Iteration_01)
    {
        using namespace Urasandesu::CppAnonym;
        
        SimpleBlob sb;
        sb.Put<BYTE>(0x01);
        sb.Put<DWORD>(0x23456789);

        BYTE expectedList[] = { 0x01, 0x89, 0x67, 0x45, 0x23 };
        INT n = 0;
        for (BYTE const *i = sb.Ptr(), *i_end = i + sb.Size(); i != i_end; ++i, ++n)
        {
            ASSERT_EQ(expectedList[n], *i);    
        }        
    }


    TEST(Urasandesu_CppAnonym_SimpleBlobTest, PutTTest_RandomAccess_01)
    {
        using namespace Urasandesu::CppAnonym;
        
        SimpleBlob sb;
        sb.Put<BYTE>(0x01);
        sb.Put<DWORD>(0x23456789);

        BYTE expectedList[] = { 0x01, 0x89, 0x67, 0x45, 0x23 };
        ASSERT_EQ(expectedList[0], sb[0]);
        ASSERT_EQ(expectedList[2], sb[2]);
        ASSERT_EQ(expectedList[4], sb[4]);
    }


    TEST(Urasandesu_CppAnonym_SimpleBlobTest, PutTTest_PutsPODObjects_01)
    {
        using namespace Urasandesu::CppAnonym;
        
        MyPOD1 pod1 = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
        MyPOD2 podPrev;
        MyPOD2 podNext;
        MyPOD2 pod2 = { 0x090A0B0C, pod1, nullptr, &podPrev, &podNext };
        
        SimpleBlob sb;
        sb.Put<MyPOD2>(pod2);

        BYTE *pb = sb.Ptr();
        ASSERT_EQ(0x0C, *pb++);
        ASSERT_EQ(0x0B, *pb++);
        ASSERT_EQ(0x0A, *pb++);
        ASSERT_EQ(0x09, *pb++);
        ASSERT_EQ(0x01, *pb++);
        ASSERT_EQ(0x02, *pb++);
        ASSERT_EQ(0x03, *pb++);
        ASSERT_EQ(0x04, *pb++);
        ASSERT_EQ(0x05, *pb++);
        ASSERT_EQ(0x06, *pb++);
        ASSERT_EQ(0x07, *pb++);
        ASSERT_EQ(0x08, *pb++);
#ifdef _M_IX86
#else
        pb += 4;    // for next pointer member's alignment
#endif
        ASSERT_EQ(0x00, *pb++);
        ASSERT_EQ(0x00, *pb++);
        ASSERT_EQ(0x00, *pb++);
        ASSERT_EQ(0x00, *pb++);
#ifdef _M_IX86
#else
        ASSERT_EQ(0x00, *pb++);
        ASSERT_EQ(0x00, *pb++);
        ASSERT_EQ(0x00, *pb++);
        ASSERT_EQ(0x00, *pb++);
#endif
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podPrev) & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podPrev) >> 8 & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podPrev) >> 16 & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podPrev) >> 24 & 0xFF), *pb++);
#ifdef _M_IX86
#else
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podPrev) >> 32 & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podPrev) >> 40 & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podPrev) >> 48 & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podPrev) >> 56 & 0xFF), *pb++);
#endif
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podNext) & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podNext) >> 8 & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podNext) >> 16 & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podNext) >> 24 & 0xFF), *pb++);
#ifdef _M_IX86
#else
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podNext) >> 32 & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podNext) >> 40 & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podNext) >> 48 & 0xFF), *pb++);
        ASSERT_EQ(static_cast<BYTE>(reinterpret_cast<DWORD_PTR>(&podNext) >> 56 & 0xFF), *pb++);
#endif
    }


    TEST(Urasandesu_CppAnonym_SimpleBlobTest, PutTTest_HigherPerformanceThanTypicalWay_01)
    {
        using namespace std;
        using namespace Urasandesu::CppAnonym;
        using boost::timer::cpu_timer;
        
        INT assignCount = 0;
        {
            SimpleBlob sb;
            assignCount = static_cast<INT>(sb.Capacity() / sizeof(MyPOD2));
        }
        ASSERT_LT(20, assignCount);
        

#ifdef _DEBUG
        INT const RETRY_COUNT = 1000;
#else
        INT const RETRY_COUNT = 100000;
#endif
        auto t = cpu_timer();
        
        for (INT i = 0; i < RETRY_COUNT; ++i)
        {
            auto vec = vector<MyPOD2>();
            for (INT j = 0; j < assignCount; ++j)
            {
                vec.push_back(MyPOD2());
            }
        }
        
        auto typicalElapsed = t.elapsed();
        t = cpu_timer();
        
        for (INT i = 0; i < RETRY_COUNT; ++i)
        {
            SimpleBlob sb;
            for (INT j = 0; j < assignCount; ++j)
            {
                sb.Put<MyPOD2>(MyPOD2());
            }
        }
        
        auto sbElapsed = t.elapsed();
        
        cout << "Typical Way: " << typicalElapsed.wall << endl;
        cout << "Simple Blob: " << sbElapsed.wall << " (x " << typicalElapsed.wall / sbElapsed.wall << ")" << endl;
        ASSERT_LT(sbElapsed.wall, typicalElapsed.wall);
    }


    //TEST(RapidVectorTestSuite, IterationTest01LessThan512)
    //{
    //    using namespace std;
    //    using namespace Urasandesu::CppAnonym;
    //    
    //    RapidVector<BYTE> vec;
    //    for (INT i = 0; i < 512; ++i)
    //    {
    //        vec.push_back(static_cast<BYTE>(i & 0xFF));
    //    }
    //    ASSERT_EQ(512, vec.size());
    //    
    //    {
    //        RapidVector<BYTE>::iterator i = vec.begin();
    //        ASSERT_EQ(0x00, *i);
    //        ASSERT_EQ(0xFF, *(i += vec.size() - 1));
    //    }
    //}
}
