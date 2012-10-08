﻿#pragma once
#ifndef URASANDESU_CPPANONYM_METADATA_METHODATTRIBUTES_HPP
#define URASANDESU_CPPANONYM_METADATA_METHODATTRIBUTES_HPP

#ifndef URASANDESU_CPPANONYM_SAFEENUM_HPP
#include <Urasandesu/CppAnonym/SafeEnum.hpp>
#endif

namespace Urasandesu { namespace CppAnonym { namespace Metadata {

    namespace Detail {

        struct MethodAttributesDef
        {
            enum type
            {
                MA_MEMBER_ACCESS_MASK = mdMemberAccessMask, 
                MA_PRIVATE_SCOPE = mdPrivateScope, 
                MA_PRIVATE = mdPrivate, 
                MA_FAMAND_ASSEM = mdFamANDAssem, 
                MA_ASSEM = mdAssem, 
                MA_FAMILY = mdFamily, 
                MA_FAMOR_ASSEM = mdFamORAssem, 
                MA_PUBLIC = mdPublic, 
                MA_STATIC = mdStatic, 
                MA_FINAL = mdFinal, 
                MA_VIRTUAL = mdVirtual, 
                MA_HIDE_BY_SIG = mdHideBySig, 
                MA_VTABLE_LAYOUT_MASK = mdVtableLayoutMask, 
                MA_REUSE_SLOT = mdReuseSlot, 
                MA_NEW_SLOT = mdNewSlot, 
                MA_CHECK_ACCESS_ON_OVERRIDE = mdCheckAccessOnOverride, 
                MA_ABSTRACT = mdAbstract, 
                MA_SPECIAL_NAME = mdSpecialName, 
                MA_PINVOKE_IMPL = mdPinvokeImpl, 
                MA_UNMANAGED_EXPORT = mdUnmanagedExport, 
                MA_RESERVED_MASK = mdReservedMask, 
                MA_RT_SPECIAL_NAME = mdRTSpecialName, 
                MA_HAS_SECURITY = mdHasSecurity, 
                MA_REQUIRE_SEC_OBJECT = mdRequireSecObject, 
                MA_UNREACHED
            };

            friend type operator |(type lhs, type rhs)
            {
                return static_cast<type>(+lhs | +rhs);
            }
        };

    }   // Detail

    typedef SafeEnum<Detail::MethodAttributesDef> MethodAttributes;

}}}   // namespace Urasandesu { namespace CppAnonym { namespace Metadata {

#endif  // #ifndef URASANDESU_CPPANONYM_METADATA_METHODATTRIBUTES_HPP