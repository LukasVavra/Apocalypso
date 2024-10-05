#pragma once

class ApoInterface
{
public:
    virtual void set_position(int& x, int& y) = 0;
    virtual void set_size(int& w, int& h) = 0;
    virtual void render() = 0;
    virtual ~ApoInterface() = default;
};