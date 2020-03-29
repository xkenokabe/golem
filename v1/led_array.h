﻿// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_LED_ARRAY_H_
#define V1_LED_ARRAY_H_

#include <stdbool.h>

typedef struct LedArrayStruct* LedArray;
typedef struct {
  void (*Delete)(LedArray* self);
  int (*Id)(LedArray self);
  const char* (*Tag)(LedArray self);
  void (*TurnAllOff)(LedArray self);
  void (*TurnAllOn)(LedArray self);
  bool (*IsAllOff)(LedArray self);
  bool (*IsAllOn)(LedArray self);
  void (*TurnOff)(LedArray self, int led_id);
  void (*TurnOn)(LedArray self, int led_id);
  bool (*IsOff)(LedArray self, int led_id);
  bool (*IsOn)(LedArray self, int led_id);
} LedArrayInterfaceStruct;
typedef const LedArrayInterfaceStruct* LedArrayInterface;

extern const LedArrayInterface ledArray;

#endif  // V1_LED_ARRAY_H_
