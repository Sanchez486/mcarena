#include "inc/hp.h"
#include <algorithm>

HP::HP(int _max) : curr(_max), max(_max)
{

}

void HP::add(int val)
{
    curr = std::min(curr + val, max);
}
