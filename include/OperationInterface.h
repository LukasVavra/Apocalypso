#pragma once

class OperationInterface {
public:
    virtual bool run(long unsigned actor_id, long unsigned reactor_id) = 0;
};