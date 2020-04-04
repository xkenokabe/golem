﻿// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "solenoid.h"

static void Delete(Component* self) { ((SolenoidInterface)(*self))->Delete(self); }

static int Id(Component self) { return ((SolenoidInterface)self)->Id(self); }

static const char* Tag(Component self) { return ((SolenoidInterface)self)->Tag(self); }

static const char* State(Component self) { return ((SolenoidInterface)self)->State(self); }

static bool IsOff(Component self) { return ((SolenoidInterface)self)->IsOff(self); }

static const SolenoidInterfaceStruct kTheInterface = {
    .Delete = Delete,
    .Id = Id,
    .Tag = Tag,
    .State = State,
    .IsOff = IsOff,
};

const SolenoidInterface solenoid = &kTheInterface;
