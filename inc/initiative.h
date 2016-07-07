#pragma once

struct Initiative
{
    int val;
    int accum;

    static const int limit = 100;

    Initiative(int _val = 0);
};
