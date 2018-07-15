/**
* Copyright (c) 2017 Nokia. All rights reserved.
*/
#pragma once

#include "gtest/gtest.h"

#include "../src/Calculator.hpp"

class CalculatorTest : public ::testing::Test
{
public:
    Calculation::Calculator calculator;
};
