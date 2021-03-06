﻿/* 
 * File: AssignationDistributorTest.cpp
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

#ifndef URASANDESU_CPPANONYM_UTILITIES_ASSIGNATIONDISTRIBUTOR_H
#include <Urasandesu/CppAnonym/Utilities/AssignationDistributor.h>
#endif

// Test.Urasandesu.CppAnonym.exe --gtest_filter=Urasandesu_CppAnonym_Utilities_AssignationDistributorTest.*
namespace {

    CPPANONYM_TEST(Urasandesu_CppAnonym_Utilities_AssignationDistributorTest, RawPointerTest_01)
    {
        using namespace Urasandesu::CppAnonym::Utilities;

        typedef GTEST_TEST_CLASS_NAME_(Urasandesu_CppAnonym_Utilities_AssignationDistributorTest, RawPointerTest_01) Tag;
        typedef SurvivalCounter<BasicCounter<Tag, 0> > Counter;
        ASSERT_EQ(0, Counter::Instance().Value());
        
        BYTE bufSrc[sizeof(Counter *)];
        ASSERT_EQ(0, Counter::Instance().Value());

        BYTE bufDst[sizeof(Counter *)];
        ASSERT_EQ(0, Counter::Instance().Value());

        AssignationDistributor<Counter *>::Assign(bufDst, bufSrc);
        ASSERT_EQ(0, Counter::Instance().Value());
    }





    CPPANONYM_TEST(Urasandesu_CppAnonym_Utilities_AssignationDistributorTest, RawPointerTest_02)
    {
        using namespace Urasandesu::CppAnonym::Utilities;

        typedef GTEST_TEST_CLASS_NAME_(Urasandesu_CppAnonym_Utilities_AssignationDistributorTest, RawPointerTest_01) Tag;
        typedef SurvivalCounter<BasicCounter<Tag, 0> > Counter;
        ASSERT_EQ(0, Counter::Instance().Value());
        
        BYTE bufSrc[sizeof(Counter *)];
        Counter *pSrc = new Counter();
        ::memcpy_s(bufSrc, sizeof(Counter *), &pSrc, sizeof(Counter *));
        ASSERT_EQ(1, Counter::Instance().Value());

        BYTE bufDst[sizeof(Counter *)];
        Counter *pDst = new Counter();
        ::memcpy_s(bufDst, sizeof(Counter *), &pDst, sizeof(Counter *));
        ASSERT_EQ(2, Counter::Instance().Value());

        AssignationDistributor<Counter *>::Assign(bufDst, bufSrc);
        ASSERT_EQ(2, Counter::Instance().Value());

        delete pSrc;
        ASSERT_EQ(1, Counter::Instance().Value());

        delete pDst;
        ASSERT_EQ(0, Counter::Instance().Value());
    }





    CPPANONYM_TEST(Urasandesu_CppAnonym_Utilities_AssignationDistributorTest, NotPodTest_01)
    {
        using namespace boost;
        using namespace Urasandesu::CppAnonym::Utilities;

        typedef GTEST_TEST_CLASS_NAME_(Urasandesu_CppAnonym_Utilities_AssignationDistributorTest, NotPodTest_01) Tag;
        typedef SurvivalCounter<BasicCounter<Tag, 0> > Counter;
        ASSERT_EQ(0, Counter::Instance().Value());
        
        BYTE bufSrc[sizeof(shared_ptr<Counter>)] = { 0 };
        ASSERT_EQ(0, Counter::Instance().Value());
        
        BYTE bufDst[sizeof(shared_ptr<Counter>)] = { 0 };
        ASSERT_EQ(0, Counter::Instance().Value());

        AssignationDistributor<shared_ptr<Counter> >::Assign(bufDst, bufSrc);
        ASSERT_EQ(0, Counter::Instance().Value());
    }





    CPPANONYM_TEST(Urasandesu_CppAnonym_Utilities_AssignationDistributorTest, NotPodTest_02)
    {
        using namespace boost;
        using namespace Urasandesu::CppAnonym::Utilities;

        typedef GTEST_TEST_CLASS_NAME_(Urasandesu_CppAnonym_Utilities_AssignationDistributorTest, NotPodTest_02) Tag;
        typedef SurvivalCounter<BasicCounter<Tag, 0> > Counter;
        ASSERT_EQ(0, Counter::Instance().Value());
        
        BYTE bufSrc[sizeof(shared_ptr<Counter>)];
        shared_ptr<Counter> pSrc(new Counter());
        ::memcpy_s(bufSrc, sizeof(shared_ptr<Counter>), &pSrc, sizeof(shared_ptr<Counter>));
        ASSERT_EQ(1, Counter::Instance().Value());
        
        BYTE bufDst[sizeof(shared_ptr<Counter>)];
        shared_ptr<Counter> pDst(new Counter());
        ::memcpy_s(bufDst, sizeof(shared_ptr<Counter>), &pDst, sizeof(shared_ptr<Counter>));
        ASSERT_EQ(2, Counter::Instance().Value());

        shared_ptr<Counter> &pSrc_ = *reinterpret_cast<shared_ptr<Counter> *>(bufSrc);
        shared_ptr<Counter> &pDst_ = *reinterpret_cast<shared_ptr<Counter> *>(bufDst);

        ASSERT_EQ(1, pSrc_.use_count());
        ASSERT_EQ(1, pDst_.use_count());
        ASSERT_NE(pSrc_, pDst_);

        AssignationDistributor<shared_ptr<Counter> >::Assign(bufDst, bufSrc);
        ASSERT_EQ(1, Counter::Instance().Value());
        
        ASSERT_EQ(2, pSrc_.use_count());
        ASSERT_EQ(2, pDst_.use_count());
        ASSERT_EQ(pSrc_, pDst_);
        
        pSrc_.~shared_ptr<Counter>();
        pDst_.~shared_ptr<Counter>();
        ::ZeroMemory(&pSrc, sizeof(shared_ptr<Counter>));  // suppress original auto destruction
        ::ZeroMemory(&pDst, sizeof(shared_ptr<Counter>));  // suppress original auto destruction
    }





    CPPANONYM_TEST(Urasandesu_CppAnonym_Utilities_AssignationDistributorTest, NotPodTest_03)
    {
        using namespace boost;
        using namespace Urasandesu::CppAnonym::Utilities;

        typedef GTEST_TEST_CLASS_NAME_(Urasandesu_CppAnonym_Utilities_AssignationDistributorTest, NotPodTest_02) Tag;
        typedef SurvivalCounter<BasicCounter<Tag, 0> > Counter;
        ASSERT_EQ(0, Counter::Instance().Value());
        
        shared_ptr<Counter> pSrc(new Counter());
        ASSERT_EQ(1, Counter::Instance().Value());
        
        shared_ptr<Counter> pDst(new Counter());
        ASSERT_EQ(2, Counter::Instance().Value());

        ASSERT_EQ(1, pSrc.use_count());
        ASSERT_EQ(1, pDst.use_count());
        ASSERT_NE(pSrc, pDst);

        AssignationDistributor<shared_ptr<Counter> >::Assign(&pSrc, &pDst);
        ASSERT_EQ(1, Counter::Instance().Value());

        ASSERT_EQ(2, pSrc.use_count());
        ASSERT_EQ(2, pDst.use_count());
        ASSERT_EQ(pSrc, pDst);
    }

}
