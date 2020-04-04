﻿// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "sensor.h"

static void Delete(Component* self) { ((SensorInterface)(*self))->Delete(self); }

static int Id(Component self) { return ((SensorInterface)self)->Id(self); }

static const char* Tag(Component self) { return ((SensorInterface)self)->Tag(self); }

static Command SensorWatchCommand(Component self, const char* expected_state, Command notification_command) {
  return ((SensorInterface)self)->SensorWatchCommand(self, expected_state, notification_command);
}

static const char* State(Component self) { return ((SensorInterface)self)->State(self); }

static bool IsDefaultState(Component self) { return ((SensorInterface)self)->IsDefaultState(self); }

static const SensorInterfaceStruct kTheInterface = {
    .Delete = Delete,
    .Id = Id,
    .Tag = Tag,
    .SensorWatchCommand = SensorWatchCommand,
    .State = State,
    .IsDefaultState = IsDefaultState,
};

const SensorInterface sensor = &kTheInterface;
