﻿// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "sleep_command.h"

#include <stdbool.h>
#include <stddef.h>

#include "bleu/v1/heap.h"
#include "command_protected.h"
#include "malkt/v1/uptime.h"

typedef enum {
  kNone = 0,
  kCancel,
  kDelete,
} PrivateRequest;

typedef struct {
  CommandStruct base;
  int sleep_time;
  uint64_t start_time;
  bool started;
  PrivateRequest request;
  ActiveObjectEngine engine;
  Command wakeup_command;
} SleepCommandStruct, *SleepCommand;

inline static SleepCommand Downcast(Command self) { return (SleepCommand)self; }

static void Delete(Command *self) {
  if (Downcast(*self)->started) {
    Downcast(*self)->request = kDelete;
    *self = NULL;
  } else {
    heap->Delete((void **)self);
  }
}

inline static bool HasRequest(SleepCommand self) { return self->request != kNone; }

static void ProcessRequest(SleepCommand self) {
  switch (self->request) {
    case kNone:
      break;
    case kCancel:
      self->started = false;
      self->request = kNone;
      break;
    case kDelete:
      heap->Delete((void **)&self);
      break;
  }
}

inline static bool ShouldWakeUp(SleepCommand self, uint64_t current_time) {
  return (current_time - self->start_time) >= self->sleep_time;
}

static void Do(Command self) {
  uint64_t current_time = uptime->Get();
  SleepCommand sc = Downcast(self);
  if (!sc->started) {
    sc->started = true;
    sc->start_time = current_time;
    activeObjectEngine->AddCommand(sc->engine, self);
  } else if (HasRequest(sc)) {
    ProcessRequest(sc);
  } else if (ShouldWakeUp(sc, current_time)) {
    activeObjectEngine->AddCommand(sc->engine, sc->wakeup_command);
  } else {
    activeObjectEngine->AddCommand(sc->engine, self);
  }
}

static void Cancel(Command self) { Downcast(self)->request = kCancel; }

static const CommandAbstractMethodStruct kConcreteMethod = {
    .Delete = Delete,
    .Do = Do,
    .Cancel = Cancel,
};

static Command New(int milliseconds, ActiveObjectEngine engine, Command wakeup_command) {
  Command self = (Command)heap->New(sizeof(SleepCommandStruct));
  self->impl = &kConcreteMethod;
  Downcast(self)->sleep_time = milliseconds;
  Downcast(self)->engine = engine;
  Downcast(self)->wakeup_command = wakeup_command;
  return self;
}

static int GetSleepTime(Command self) { return Downcast(self)->sleep_time; }

static void SetSleepTime(Command self, int milliseconds) { Downcast(self)->sleep_time = milliseconds; }

static const SleepCommandMethodStruct kTheMethod = {
    .New = New,
    .GetSleepTime = GetSleepTime,
    .SetSleepTime = SetSleepTime,
};

const SleepCommandMethod sleepCommand = &kTheMethod;