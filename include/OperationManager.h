#pragma once
#include <OperationInterface.h>
#include <Singleton.h>
#include <vector>
#include <cstdint>

using OperationId = uint16_t;

class OperationManager : public Singleton<OperationManager>
{
public:
    void add(OperationInterface* op);
    bool run_op(long unsigned actor_id, long unsigned reactor_id, OperationId op_id);
private:
    std::vector<OperationInterface*> operation;
};