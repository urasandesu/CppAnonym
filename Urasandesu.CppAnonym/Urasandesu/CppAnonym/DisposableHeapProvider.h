﻿/* 
 * File: DisposableHeapProvider.h
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
#ifndef URASANDESU_CPPANONYM_DISPOSABLEHEAPPROVIDER_H
#define URASANDESU_CPPANONYM_DISPOSABLEHEAPPROVIDER_H

#ifndef URASANDESU_CPPANONYM_IDISPOSABLE_HPP
#include <Urasandesu/CppAnonym/IDisposable.hpp>
#endif

#ifndef URASANDESU_CPPANONYM_PERSISTABLEHEAPPROVIDER_H
#include <Urasandesu/CppAnonym/PersistableHeapProvider.h>
#endif

#ifndef URASANDESU_CPPANONYM_DISPOSABLEHEAPPROVIDERFWD_H
#include <Urasandesu/CppAnonym/DisposableHeapProviderFwd.h>
#endif

// TODO: rename to PersistableHeapProvider.hpp.

namespace Urasandesu { namespace CppAnonym {

    namespace DisposableHeapProviderDetail {

        using namespace Urasandesu::CppAnonym::Utilities;
        namespace mpl = boost::mpl;
        using boost::is_base_of;
        using boost::is_same;
        using boost::noncopyable;
        using mpl::_;
        using mpl::_1;
        using mpl::_2;
        using mpl::at_c;
        using mpl::begin;
        using mpl::deref;
        using mpl::deref;
        using mpl::end;
        using mpl::filter_view;
        using mpl::find;
        using mpl::find_if;
        using mpl::fold;
        using mpl::lambda;
        using mpl::next;
        using mpl::not_;
        using mpl::or_;
        using mpl::push_back;
        using mpl::reverse;
        using mpl::true_;
        using mpl::vector;
        using mpl::void_;

        template<class T, class HasDispose>
        struct DisposeCoreImpl
        {
            static void DisposeCore(T *p)
            {
                // Do nothing.
            }
        };

        template<class T>
        struct DisposeCoreImpl<T, true_> 
        { 
            static void DisposeCore(T *p)
            {
                p->Dispose();
            }
        };

        
        
        template<class I>
        struct DisposingInfoFacade
        {
            typedef typename deref<I>::type disposing_info_type;
            typedef PersistableHeapProvider<disposing_info_type> base_type;
            typedef typename base_type::object_type object_type;
            typedef typename base_type::persisted_handler_type persisted_handler_type;
        };

        template<class ReversedDisposingInfoTypes, class I, class IEnd>
        class ATL_NO_VTABLE DisposableHeapProviderImplImpl : 
            public DisposingInfoFacade<I>::base_type,
            public DisposableHeapProviderImplImpl<ReversedDisposingInfoTypes, typename next<I>::type, IEnd>
        {
        public:
            typedef DisposingInfoFacade<I> facade;
            typedef typename facade::base_type base_type;
            typedef typename facade::object_type object_type;
            typedef typename facade::persisted_handler_type persisted_handler_type;

            TempPtr<object_type> NewObject()
            {
                return base_type::NewObject();
            }
            
            void RegisterObject(TempPtr<object_type> &p)
            {
                base_type::RegisterObject(p);
            }

            SIZE_T AddPersistedHandler(TempPtr<object_type> &p, persisted_handler_type const &handler)
            {
                return base_type::AddPersistedHandler(p, handler);
            }

            void DeleteObject(object_type *p)
            {
                DisposeCore(p);
                base_type::DeleteObject(p);
            }

        private:
            static void Destruct(std::vector<object_type *> &objects)
            {
                for (auto ri = objects.rbegin(), ri_end = objects.rend(); ri != ri_end; ++ri)
                    DisposeCore(*ri);
            }
            
            static void DisposeCore(object_type *p)
            {
                typedef typename or_<
                    CPP_ANONYM_HAS_MEMBER_FUNCTION(DisposingInfoDispose, object_type), 
                    is_base_of<IDisposable, object_type> 
                >::type HasDispose;

                typedef DisposeCoreImpl<object_type, HasDispose> Impl;

                Impl::DisposeCore(p);
            }
        };

        template<class ReversedDisposingInfoTypes>
        class DisposableHeapProviderImplImpl<ReversedDisposingInfoTypes, 
                                              typename end<ReversedDisposingInfoTypes>::type, 
                                              typename end<ReversedDisposingInfoTypes>::type> : 
            noncopyable
        {
        };

        
        
        CPP_ANONYM_DECLARE_GET_MEMBER_TYPE(DisposingInfoObject, object_type);

        
        
        template<class DisposingInfo, class T>
        struct HasObjectT : 
            is_same<typename CPP_ANONYM_GET_MEMBER_TYPE(DisposingInfoObject, DisposingInfo)::type, T>
        {
        };

        
        
        template<class DisposingInfoTypes, LONG N>
        class ProvidingTypeAtImpl
        {
            typedef typename at_c<DisposingInfoTypes, N>::type disposing_info_type;
        public:
            typedef typename disposing_info_type::object_type type;
        };

        
        
        template<class DisposingInfoTypes, class T>
        class FirstProviderOfImpl
        {
            typedef typename find_if<DisposingInfoTypes, HasObjectT<_1, T> >::type i;
        public:
            typedef typename ProviderOfImpl<typename reverse<DisposingInfoTypes>::type, typename deref<i>::type>::type type;
        };

        
        
        template<class ReversedDisposingInfoTypes, class ProvidingType>
        class ProviderOfImpl
        {
            typedef typename find<ReversedDisposingInfoTypes, ProvidingType>::type i;
            typedef typename end<ReversedDisposingInfoTypes>::type i_end;
            BOOST_MPL_ASSERT((not_<is_same<i, i_end> >));
        public:
            typedef DisposableHeapProviderImplImpl<ReversedDisposingInfoTypes, i, i_end> type;
        };

        
        
        template<class ReversedDisposingInfoTypes, class T>
        class IsProvidedObjectImpl
        {
            typedef typename find_if<ReversedDisposingInfoTypes, HasObjectT<_1, T> >::type i;
            typedef typename end<ReversedDisposingInfoTypes>::type i_end;
        public:
            typedef typename not_<is_same<i, i_end> >::type type;
        };

        
        
        template<class DisposingInfoTypes, class T>
        class FirstProvidingPersistedHandlerImpl
        {
            typedef typename find_if<DisposingInfoTypes, HasObjectT<_1, T> >::type i;
            typedef typename deref<i>::type disposing_info_type;
        public:
            typedef typename disposing_info_type::persisted_handler_type type;
        };

        
        
        template<class DisposingInfoTypes>
        class ATL_NO_VTABLE DisposableHeapProviderImpl : 
            DisposableHeapProviderImplImpl<typename reverse<DisposingInfoTypes>::type, 
                                           typename begin<typename reverse<DisposingInfoTypes>::type>::type, 
                                           typename end<typename reverse<DisposingInfoTypes>::type>::type>
        {
        private:
            typedef DisposableHeapProviderImpl<DisposingInfoTypes> this_type;
            typedef DisposingInfoTypes disposing_info_types;

        public:
            template<LONG N>
            struct disposing_info_at : 
                at_c<disposing_info_types, N>
            {
            };

            template<LONG N>
            struct providing_type_at : 
                ProvidingTypeAtImpl<disposing_info_types, N>
            {
            };

            template<class T>
            struct first_provider_of : 
                FirstProviderOfImpl<disposing_info_types, T>
            {
            };

            template<class ProvidingType>
            struct provider_of : 
                ProviderOfImpl<typename reverse<disposing_info_types>::type, ProvidingType>
            {
            };

            template<class T>
            struct is_provided_object : 
                IsProvidedObjectImpl<typename reverse<disposing_info_types>::type, T>
            {
            };

            template<class T>
            struct first_providing_persisted_handler : 
                FirstProvidingPersistedHandlerImpl<disposing_info_types, T>
            {
            };

            template<class T>
            typename first_provider_of<T>::type & FirstProviderOf() const
            {
                this_type *pMutableThis = const_cast<this_type *>(this);
                return static_cast<typename first_provider_of<T>::type &>(*pMutableThis);
            }

            template<class ProvidingType>
            typename provider_of<ProvidingType>::type &ProviderOf() const
            {
                this_type *pMutableThis = const_cast<this_type *>(this);
                return static_cast<typename provider_of<ProvidingType>::type &>(*pMutableThis);
            }
        };

        
        
        template<class T0, CPPANONYM_DISPOSABLE_HEAP_PROVIDER_ENUM_SHIFTED_PARAMS(class T)>
        class DesignatedSequence
        {
            typedef vector<T0, CPPANONYM_DISPOSABLE_HEAP_PROVIDER_ENUM_SHIFTED_PARAMS(T)> types;
            typedef typename lambda<not_<is_same<_, void_> > >::type is_designated;
        public:
            typedef typename fold<filter_view<types, is_designated>, vector<>, push_back<_1, _2> >::type type;
        };

    }   // namespace DisposableHeapProviderDetail {

    template<class T0, CPPANONYM_DISPOSABLE_HEAP_PROVIDER_ENUM_SHIFTED_PARAMS(class T)>
    struct ATL_NO_VTABLE DisposableHeapProvider : 
        DisposableHeapProviderDetail::DisposableHeapProviderImpl<
            typename DisposableHeapProviderDetail::DesignatedSequence<T0, CPPANONYM_DISPOSABLE_HEAP_PROVIDER_ENUM_SHIFTED_PARAMS(T)>::type
        >
    {
        // The following typedef can't resolve if each element of the sequence is DisposableHeapProvider.
        //typedef typename DisposableHeapProviderDetail::DesignatedSequence<T0, CPPANONYM_DISPOSABLE_HEAP_PROVIDER_ENUM_SHIFTED_PARAMS(T)>::type disposing_info_types;
        template<class T = boost::mpl::void_>
        struct disposing_info : 
            DisposableHeapProviderDetail::DesignatedSequence<T0, CPPANONYM_DISPOSABLE_HEAP_PROVIDER_ENUM_SHIFTED_PARAMS(T)>
        {
        };
    };

}}   // namespace Urasandesu { namespace CppAnonym {

#endif  // #ifndef URASANDESU_CPPANONYM_DISPOSABLEHEAPPROVIDER_H
