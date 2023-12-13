#include "OperationManager.h"

void OperationManager::add(OperationInterface *op)
{
    operation.push_back(op);
}

bool OperationManager::run_op(long unsigned actor_id, long unsigned reactor_id, OperationId op_id)
{
    return operation.at(op_id)->run(actor_id, reactor_id);
}