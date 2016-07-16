#pragma once

struct HP
{
    int curr;
    int max;

    HP(int _max = 0);

    void add(int val);  // curr = min(curr + val, max)
};
