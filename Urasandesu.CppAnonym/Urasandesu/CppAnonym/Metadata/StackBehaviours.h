﻿#pragma once
#ifndef URASANDESU_CPPANONYM_METADATA_STACKBEHAVIOURS_H
#define URASANDESU_CPPANONYM_METADATA_STACKBEHAVIOURS_H

namespace Urasandesu { namespace CppAnonym { namespace Metadata {

    class StackBehaviour;

    struct StackBehaviours
    {
        static const StackBehaviour Pop0;
        static const StackBehaviour Pop1;
        static const StackBehaviour PopI;
        static const StackBehaviour PopI8;
        static const StackBehaviour PopR4;
        static const StackBehaviour PopR8;
        static const StackBehaviour PopRef;
        static const StackBehaviour Push0;
        static const StackBehaviour Push1;
        static const StackBehaviour PushI;
        static const StackBehaviour PushI8;
        static const StackBehaviour PushR4;
        static const StackBehaviour PushR8;
        static const StackBehaviour PushRef;
        static const StackBehaviour VarPop;
        static const StackBehaviour VarPush;
    };

}}}   // namespace Urasandesu { namespace CppAnonym { namespace Metadata {

#endif  // #ifndef URASANDESU_CPPANONYM_METADATA_STACKBEHAVIOURS_H