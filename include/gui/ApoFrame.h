#pragma once

#include <ApoInterface.h>

class ApoFrame final : public ApoInterface
{
public:
    ApoFrame();
    virtual ~ApoFrame() = default;
    virtual void render() override;
    virtual void set_position(int& x, int& y) override;
    virtual void set_size(int& w, int& h) override;
private:
    int _x, _y, _w, _h;
};




















