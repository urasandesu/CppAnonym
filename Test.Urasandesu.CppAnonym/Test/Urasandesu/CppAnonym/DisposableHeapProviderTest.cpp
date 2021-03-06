﻿/* 
 * File: DisposableHeapProviderTest.cpp
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

#ifndef URASANDESU_CPPANONYM_SAFEENUM_H
#include <Urasandesu/CppAnonym/SafeEnum.h>
#endif

#ifndef URASANDESU_CPPANONYM_DISPOSINGINFO_H
#include <Urasandesu/CppAnonym/DisposingInfo.h>
#endif

#ifndef URASANDESU_CPPANONYM_DISPOSABLEHEAPPROVIDER_H
#include <Urasandesu/CppAnonym/DisposableHeapProvider.h>
#endif

#ifndef URASANDESU_CPPANONYM_COLLECTIONS_RAPIDVECTOR_HPP
#include <Urasandesu/CppAnonym/Collections/RapidVector.hpp>
#endif

#ifndef URASANDESU_CPPANONYM_SIMPLEHEAP_HPP
#include <Urasandesu/CppAnonym/SimpleHeap.hpp>
#endif

#ifndef URASANDESU_CPPANONYM_DEPENDENTOBJECTSPROVIDER_H
#include <Urasandesu/CppAnonym/DependentObjectsProvider.h>
#endif

#ifndef URASANDESU_CPPANONYM_STATICDEPENDENTOBJECTSSTORAGE_H
#include <Urasandesu/CppAnonym/StaticDependentObjectsStorage.h>
#endif

#ifndef URASANDESU_CPPANONYM_CPPANONYMNOTIMPLEMENTEDEXCEPTION_H
#include <Urasandesu/CppAnonym/CppAnonymNotImplementedException.h>
#endif

// Test.Urasandesu.CppAnonym.exe --gtest_filter=Urasandesu_CppAnonym_DisposableHeapProviderTest.*
namespace {

    namespace _731D234E {

        struct Piyo;
        struct PiyoPersistedHandler;

        struct PuyoPersistedHandler;

    }   // namespace _731D234E {

    namespace _731D234E {

        namespace mpl = boost::mpl;
        using namespace Urasandesu::CppAnonym;
        using std::pair;
        using std::vector;
        using Urasandesu::CppAnonym::Utilities::TempPtr;

        typedef StaticDependentObjectsStorage<Piyo> MyStorage;
        typedef MyStorage::host_type Host;

        struct OrderChecker
        {
            static OrderChecker &Instance()
            {
                static OrderChecker checker;
                return checker;
            }

            std::vector<size_t> m_ctorSeq;
            std::vector<size_t> m_dtorSeq;
            std::vector<size_t> m_disposingSeq;
        };

        struct PiyoFacade
        {
            typedef Piyo piyo_type;
            typedef PiyoPersistedHandler piyo_persisted_handler_type;
            typedef DisposingInfo<piyo_type, piyo_persisted_handler_type> piyo_disposing_info_type;

            
            typedef DisposableHeapProvider<
                piyo_disposing_info_type
            > base_heap_provider_type;
            
            
            typedef base_heap_provider_type::provider_of<piyo_disposing_info_type>::type piyo_provider_type;
        };

        struct PiyoPersistedHandler
        {
            typedef PiyoFacade facade;
            typedef facade::piyo_type piyo_type;
            typedef facade::piyo_persisted_handler_type piyo_persisted_handler_type;
            typedef facade::piyo_disposing_info_type piyo_disposing_info_type;
            typedef facade::piyo_provider_type piyo_provider_type;

            typedef TempPtr<piyo_type> sender_type;

            PiyoPersistedHandler();
            void operator()(sender_type *pSender, void *pArg);

            piyo_type *m_pPiyo;
        };

        struct Piyo : 
            PiyoFacade::base_heap_provider_type
        {
            typedef PiyoFacade facade;
            typedef facade::piyo_type piyo_type;
            typedef facade::piyo_persisted_handler_type piyo_persisted_handler_type;
            typedef facade::piyo_disposing_info_type piyo_disposing_info_type;
            typedef facade::piyo_provider_type piyo_provider_type;

            Piyo()
            { 
                OrderChecker::Instance().m_ctorSeq.push_back(reinterpret_cast<size_t>(this)); 
            }
            
            ~Piyo() 
            { 
                OrderChecker::Instance().m_dtorSeq.push_back(reinterpret_cast<size_t>(this)); 
                if (!m_piyos.empty())   // root
                {
                    auto &sPiyo = MyStorage::Object<piyo_type>();
                    auto &provider = sPiyo.ProviderOf<piyo_disposing_info_type>();
                    BOOST_FOREACH (auto const &pPiyo, m_piyos)
                        provider.DeleteObject(pPiyo);
                }
            }

            static piyo_type *CreateStaticPiyo()
            {
                auto pPiyo = NewStaticPiyo();
                pPiyo.Persist();
                return pPiyo.Get();
            }

            static TempPtr<piyo_type> NewStaticPiyo()
            {
                auto &sPiyo = MyStorage::Object<piyo_type>();
                auto &provider = sPiyo.ProviderOf<piyo_disposing_info_type>();
                auto pPiyo = provider.NewObject();
                auto handler = piyo_persisted_handler_type();
                provider.AddPersistedHandler(pPiyo, handler);
                return pPiyo;
            }
            
            piyo_type *CreatePiyo()
            {
                auto pPiyo = NewPiyo();
                pPiyo.Persist();
                return pPiyo.Get();
            }

            TempPtr<piyo_type> NewPiyo()
            {
                auto &sPiyo = MyStorage::Object<piyo_type>();
                auto &provider = sPiyo.ProviderOf<piyo_disposing_info_type>();
                auto pPiyo = provider.NewObject();
                auto handler = piyo_persisted_handler_type();
                provider.AddPersistedHandler(pPiyo, handler);
                return pPiyo;
            }

            void RegisterPiyo(TempPtr<piyo_type> &pPiyo)
            {
                auto &sPiyo = MyStorage::Object<piyo_type>();
                auto &provider = sPiyo.ProviderOf<piyo_disposing_info_type>();
                auto &piyo = *pPiyo;
                provider.RegisterObject(pPiyo);
                sPiyo.m_piyos.push_back(&piyo);
            }

            void DeletePiyo(TempPtr<piyo_type> &pPiyo)
            {
                using boost::range::find_if;

                auto &sPiyo = MyStorage::Object<piyo_type>();
                typedef decltype(sPiyo.m_piyos) Piyos;
                typedef Piyos::value_type Value;

                auto finder = [&](Value const &v) { return v == pPiyo.Get(); };
                auto result = find_if(sPiyo.m_piyos, finder);
                if (result != sPiyo.m_piyos.end())
                {
                    auto &provider = sPiyo.ProviderOf<piyo_disposing_info_type>();
                    provider.DeleteObject(*result);
                    sPiyo.m_piyos.erase(result);
                }
                else
                {
                    // nop, because the object will be deleted in .dtor.
                }
            }

            void Dispose()
            {
                OrderChecker::Instance().m_disposingSeq.push_back(reinterpret_cast<size_t>(this));
            }

            vector<piyo_type *> m_piyos;
        };

        PiyoPersistedHandler::PiyoPersistedHandler()
        { }
                
        void PiyoPersistedHandler::operator()(sender_type *pSender, void *pArg)
        {
            sender_type &pPiyo = *pSender;
            auto &sPiyo = MyStorage::Object<piyo_type>();
            sPiyo.RegisterPiyo(pPiyo);
        }






        struct PuyoFacade
        {
            typedef Piyo piyo_type;
            typedef PuyoPersistedHandler puyo_persisted_handler_type;
            typedef DisposingInfo<piyo_type, puyo_persisted_handler_type> nested_piyo_disposing_info_type;
            typedef PiyoPersistedHandler piyo_persisted_handler_type;
            typedef DisposingInfo<piyo_type, piyo_persisted_handler_type> piyo_disposing_info_type;

            
            typedef DisposableHeapProvider<
                nested_piyo_disposing_info_type,
                piyo_disposing_info_type
            > base_heap_provider_type;
            
            
            typedef base_heap_provider_type::provider_of<nested_piyo_disposing_info_type>::type nested_piyo_provider_type;
            typedef base_heap_provider_type::provider_of<piyo_disposing_info_type>::type piyo_provider_type;
        };

        struct PuyoPersistedHandler
        {
            typedef PuyoFacade facade;
            typedef facade::piyo_type piyo_type;
            typedef facade::puyo_persisted_handler_type puyo_persisted_handler_type;
            typedef facade::nested_piyo_disposing_info_type nested_piyo_disposing_info_type;
            typedef facade::piyo_persisted_handler_type piyo_persisted_handler_type;
            typedef facade::piyo_disposing_info_type piyo_disposing_info_type;
            typedef facade::base_heap_provider_type base_heap_provider_type;
            typedef facade::nested_piyo_provider_type nested_piyo_provider_type;
            typedef facade::piyo_provider_type piyo_provider_type;
        };

        struct Puyo : 
            PuyoFacade::base_heap_provider_type
        {
            typedef PuyoFacade facade;
            typedef facade::piyo_type piyo_type;
            typedef facade::puyo_persisted_handler_type puyo_persisted_handler_type;
            typedef facade::nested_piyo_disposing_info_type nested_piyo_disposing_info_type;
            typedef facade::piyo_persisted_handler_type piyo_persisted_handler_type;
            typedef facade::piyo_disposing_info_type piyo_disposing_info_type;
            typedef facade::base_heap_provider_type base_heap_provider_type;
            typedef facade::nested_piyo_provider_type nested_piyo_provider_type;
            typedef facade::piyo_provider_type piyo_provider_type;
        };

    }   // namespace _731D234E {

    CPPANONYM_TEST(Urasandesu_CppAnonym_DisposableHeapProviderTest, Test_01)
    {
        namespace mpl = boost::mpl;
        using namespace _731D234E;

        auto &sPiyo = MyStorage::Object<Piyo>();
        auto sPiyoId = reinterpret_cast<size_t>(&sPiyo);
        auto *pPiyoRoot = Piyo::CreateStaticPiyo();
        auto pPiyoRootId = reinterpret_cast<size_t>(pPiyoRoot);
        auto *pPiyo1 = pPiyoRoot->CreatePiyo();
        auto pPiyo1Id = reinterpret_cast<size_t>(pPiyo1);
        auto pPiyo2Id = size_t();
        {
            auto pPiyo2 = pPiyoRoot->NewPiyo();
            pPiyo2Id = reinterpret_cast<size_t>(pPiyo2.Get());
            pPiyo2.Persist();

            ASSERT_EQ(4, OrderChecker::Instance().m_ctorSeq.size());
            ASSERT_EQ(sPiyoId, OrderChecker::Instance().m_ctorSeq[0]);
            ASSERT_EQ(pPiyoRootId, OrderChecker::Instance().m_ctorSeq[1]);
            ASSERT_EQ(pPiyo1Id, OrderChecker::Instance().m_ctorSeq[2]);
            ASSERT_EQ(pPiyo2Id, OrderChecker::Instance().m_ctorSeq[3]);
            ASSERT_EQ(0, OrderChecker::Instance().m_dtorSeq.size());
            ASSERT_EQ(0, OrderChecker::Instance().m_disposingSeq.size());

            pPiyoRoot->DeletePiyo(pPiyo2);
        }

        ASSERT_EQ(4, OrderChecker::Instance().m_ctorSeq.size());
        ASSERT_EQ(sPiyoId, OrderChecker::Instance().m_ctorSeq[0]);
        ASSERT_EQ(pPiyoRootId, OrderChecker::Instance().m_ctorSeq[1]);
        ASSERT_EQ(pPiyo1Id, OrderChecker::Instance().m_ctorSeq[2]);
        ASSERT_EQ(pPiyo2Id, OrderChecker::Instance().m_ctorSeq[3]);
        ASSERT_EQ(1, OrderChecker::Instance().m_dtorSeq.size());
        ASSERT_EQ(1, OrderChecker::Instance().m_disposingSeq.size());

        StaticDependentObjectsStorageDetail::HostAccessor<Piyo>::Host().~Host();

        ASSERT_EQ(4, OrderChecker::Instance().m_dtorSeq.size());
        ASSERT_EQ(pPiyo2Id, OrderChecker::Instance().m_dtorSeq[0]);
        ASSERT_EQ(sPiyoId, OrderChecker::Instance().m_dtorSeq[1]);
        ASSERT_EQ(pPiyoRootId, OrderChecker::Instance().m_dtorSeq[2]);
        ASSERT_EQ(pPiyo1Id, OrderChecker::Instance().m_dtorSeq[3]);

        ASSERT_EQ(3, OrderChecker::Instance().m_disposingSeq.size());
        ASSERT_EQ(pPiyo2Id, OrderChecker::Instance().m_disposingSeq[0]);
        ASSERT_EQ(pPiyoRootId, OrderChecker::Instance().m_disposingSeq[1]);
        ASSERT_EQ(pPiyo1Id, OrderChecker::Instance().m_disposingSeq[2]);

        // Restore static area to work the debug heap correctly.
        new(&StaticDependentObjectsStorageDetail::HostAccessor<Piyo>::Host())Host();
    }

    CPPANONYM_TEST(Urasandesu_CppAnonym_DisposableHeapProviderTest, Test_02)
    {
        namespace mpl = boost::mpl;
        using mpl::not_;
        using namespace boost;
        using namespace _731D234E;
        
        BOOST_MPL_ASSERT((Piyo::is_provided_object<Piyo>));
        BOOST_MPL_ASSERT((not_<Piyo::is_provided_object<int> >));
        
        Piyo piyo;
        
        auto &provider = piyo.FirstProviderOf<Piyo>();
        TempPtr<Piyo> pPiyo = provider.NewObject();
        ASSERT_TRUE(pPiyo);
    }

    CPPANONYM_TEST(Urasandesu_CppAnonym_DisposableHeapProviderTest, Test_03)
    {
        namespace mpl = boost::mpl;
        using namespace boost;
        using namespace _731D234E;
        
        BOOST_MPL_ASSERT((is_same<Puyo::first_provider_of<Piyo>::type, PuyoFacade::nested_piyo_provider_type>));
        BOOST_MPL_ASSERT((is_same<Puyo::first_providing_persisted_handler<Piyo>::type, PuyoFacade::puyo_persisted_handler_type>));
    }

}
