﻿#pragma once
#ifndef URASANDESU_CPPANONYM_TRAITS_MAKEPOINTERHOLDERIMPLFWD_H
#define URASANDESU_CPPANONYM_TRAITS_MAKEPOINTERHOLDERIMPLFWD_H

namespace Urasandesu { namespace CppAnonym { namespace Traits {

    template<
        class T, 
        class TD, 
        class ImplD, 
        template<class, class, class> class PointerHolderImpl
    >
    struct MakePointerHolderImpl;

}}}   // namespace Urasandesu { namespace CppAnonym { namespace Traits {

#endif  // #ifndef URASANDESU_CPPANONYM_TRAITS_MAKEPOINTERHOLDERIMPLFWD_H