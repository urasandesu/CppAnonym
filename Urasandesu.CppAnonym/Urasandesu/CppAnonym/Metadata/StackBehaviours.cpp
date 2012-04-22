﻿
#include "stdafx.h"

#ifndef URASANDESU_CPPANONYM_METADATA_STACKBEHAVIOURS_H
#include <Urasandesu/CppAnonym/Metadata/StackBehaviours.h>
#endif

#ifndef URASANDESU_CPPANONYM_METADATA_STACKBEHAVIOUR_H
#include <Urasandesu/CppAnonym/Metadata/StackBehaviour.h>
#endif

namespace Urasandesu { namespace CppAnonym { namespace Metadata {

    const StackBehaviour StackBehaviours::Pop0 = StackBehaviour(StackBehaviourTypes::SBT_POP0);
    const StackBehaviour StackBehaviours::Pop1 = StackBehaviour(StackBehaviourTypes::SBT_POP1);
    const StackBehaviour StackBehaviours::PopI = StackBehaviour(StackBehaviourTypes::SBT_POP_I);
    const StackBehaviour StackBehaviours::PopI8 = StackBehaviour(StackBehaviourTypes::SBT_POP_I8);
    const StackBehaviour StackBehaviours::PopR4 = StackBehaviour(StackBehaviourTypes::SBT_POP_R4);
    const StackBehaviour StackBehaviours::PopR8 = StackBehaviour(StackBehaviourTypes::SBT_POP_R8);
    const StackBehaviour StackBehaviours::PopRef = StackBehaviour(StackBehaviourTypes::SBT_POP_REF);
    const StackBehaviour StackBehaviours::Push0 = StackBehaviour(StackBehaviourTypes::SBT_PUSH0);
    const StackBehaviour StackBehaviours::Push1 = StackBehaviour(StackBehaviourTypes::SBT_PUSH1);
    const StackBehaviour StackBehaviours::PushI = StackBehaviour(StackBehaviourTypes::SBT_PUSH_I);
    const StackBehaviour StackBehaviours::PushI8 = StackBehaviour(StackBehaviourTypes::SBT_PUSH_I8);
    const StackBehaviour StackBehaviours::PushR4 = StackBehaviour(StackBehaviourTypes::SBT_PUSH_R4);
    const StackBehaviour StackBehaviours::PushR8 = StackBehaviour(StackBehaviourTypes::SBT_PUSH_R8);
    const StackBehaviour StackBehaviours::PushRef = StackBehaviour(StackBehaviourTypes::SBT_PUSH_REF);
    const StackBehaviour StackBehaviours::VarPop = StackBehaviour(StackBehaviourTypes::SBT_VAR_POP);
    const StackBehaviour StackBehaviours::VarPush = StackBehaviour(StackBehaviourTypes::SBT_VAR_PUSH);

}}}   // namespace Urasandesu { namespace CppAnonym { namespace Metadata {