﻿#pragma once
#ifndef URASANDESU_CPPANONYM_TRAITS_ISLIKEPOINTER_HPP
#define URASANDESU_CPPANONYM_TRAITS_ISLIKEPOINTER_HPP

#ifndef URASANDESU_CPPANONYM_TRAITS_HASMEMBERFUNCTION_H
#include <Urasandesu/CppAnonym/Traits/HasMemberFunction.h>
#endif

#ifndef URASANDESU_CPPANONYM_TRAITS_ISLIKEPOINTERFWD_HPP
#include <Urasandesu/CppAnonym/Traits/IsLikePointerFwd.hpp>
#endif

namespace Urasandesu { namespace CppAnonym { namespace Traits {

    namespace IsLikePointerDetail {

        using boost::mpl::and_;
        using boost::mpl::not_;
        using boost::mpl::or_;
        using namespace boost;

        template<class T>
        class IsLikePointerImpl : 
            public boost::is_pointer<T>
        {
        };

        template<class T, template<class> class CandidateSmartPtr>
        class IsLikePointerImpl<CandidateSmartPtr<T> >
        {
            CPP_ANONYM_DECLARE_HAS_MEMBER_FUNCTION(IndirectionOperator, operator*, T &, () const); 
            CPP_ANONYM_DECLARE_HAS_MEMBER_FUNCTION(MemberAccessOperator, operator->, T *, () const);
        public:
            typedef typename and_<
                CPP_ANONYM_HAS_MEMBER_FUNCTION(IndirectionOperator, CandidateSmartPtr<T>), 
                CPP_ANONYM_HAS_MEMBER_FUNCTION(MemberAccessOperator, CandidateSmartPtr<T>), 
                not_<
                    or_<
                        has_trivial_constructor<CandidateSmartPtr<T> >,
                        has_trivial_copy<CandidateSmartPtr<T> >, 
                        has_trivial_assign<CandidateSmartPtr<T> >, 
                        has_trivial_destructor<CandidateSmartPtr<T> >
                    >
                >
            >::type type;
        };

    }   // namespace IsLikePointerDetail {

    template<class T>
    struct IsLikePointer : 
        IsLikePointerDetail::IsLikePointerImpl<T>
    {
    };

    template<class T, template<class> class CandidateSmartPtr>
    struct IsLikePointer<CandidateSmartPtr<T> > : 
        IsLikePointerDetail::IsLikePointerImpl<CandidateSmartPtr<T> >
    {
    };

}}}   // namespace Urasandesu { namespace CppAnonym { namespace Traits {

#endif  // #ifndef URASANDESU_CPPANONYM_TRAITS_ISLIKEPOINTER_HPP