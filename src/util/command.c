﻿// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "command.h"

#include "command_protected.h"

static void Delete(Command *self) { (*self)->impl->Delete(self); }

static void Do(Command self) { self->impl->Do(self); }

static const CommandAbstractMethodStruct kTheMethod = {
    .Delete = Delete,
    .Do = Do,
};

const CommandAbstractMethod command = &kTheMethod;
