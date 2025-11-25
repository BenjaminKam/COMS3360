#pragma once

class vec2
{
public:
    double e[2];

    vec2() : e{0, 0} {}
    vec2(double e0, double e1) : e{e0, e1} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
};
