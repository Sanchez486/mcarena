#include "inc/element.h"

bool operator==(Element left, Element right)
{
    if( (int)left == (int)Element::neutral ||
        (int)right == (int)Element::neutral )
    {
        return true;
    }

    return (int)left == (int)right;
}


bool operator<(Element left, Element right)
{
    if( (int)left == (int)Element::fire && (int)right == (int)Element::water ||
        (int)left == (int)Element::water && (int)right == (int)Element::earth ||
        (int)left == (int)Element::earth && (int)right == (int)Element::fire )
    {
        return true;
    }

    return false;
}

bool operator>(Element left, Element right)
{
    return right < left;
}
