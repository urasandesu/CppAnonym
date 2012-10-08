﻿#pragma once
#ifndef URASANDESU_CPPANONYM_METADATA_BASETYPENAMEMETADATAFWD_HPP
#define URASANDESU_CPPANONYM_METADATA_BASETYPENAMEMETADATAFWD_HPP

#ifndef URASANDESU_CPPANONYM_METADATA_APIHOLDERS_DEFAULTTYPENAMEMETADATAAPIHOLDERFWD_H
#include <Urasandesu/CppAnonym/Metadata/ApiHolders/DefaultTypeNameMetadataApiHolderFwd.h>
#endif

namespace Urasandesu { namespace CppAnonym { namespace Metadata {

    template<
        class TypeNameMetadataApiHolder = ApiHolders::DefaultTypeNameMetadataApiHolder
    >
    class BaseTypeNameMetadata;

    typedef BaseTypeNameMetadata<> TypeNameMetadata;

    
    
    
    
    //template<
    //    class TypeNameMetadataApiHolder = ApiHolders::DefaultTypeNameMetadataApiHolder
    //>    
    //class BaseTypeNameMetadataHash;

    //typedef BaseTypeNameMetadataHash<> TypeNameMetadataHash;

    //
    //
    //
    //
    //template<
    //    class TypeNameMetadataApiHolder = ApiHolders::DefaultTypeNameMetadataApiHolder
    //>    
    //class BaseTypeNameMetadataEqualTo;

    //typedef BaseTypeNameMetadataEqualTo<> TypeNameMetadataEqualTo;

}}}   // namespace Urasandesu { namespace CppAnonym { namespace Metadata {

#endif  // #ifndef URASANDESU_CPPANONYM_METADATA_BASETYPENAMEMETADATAFWD_HPP