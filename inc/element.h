#pragma once

enum class Element
{
    neutral,
    fire,
    water,
    earth
};

bool operator==(Element left, Element right);
bool operator<(Element left, Element right);
bool operator>(Element left, Element right);
