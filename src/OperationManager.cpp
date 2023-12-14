#include "OperationManager.h"
#include <iostream>
#include <algorithm>

void OperationManager::add(OperationInterface *op)
{
    if(std::find(operation.begin(), operation.end(), op) == operation.end())
    {
        operation.push_back(op);
    }
}

bool OperationManager::run_op(long unsigned actor_id, long unsigned reactor_id, OperationId op_id)
{
    try
    {
        return operation.at(op_id)->run(actor_id, reactor_id);
    }
    catch(const std::out_of_range& e)
    {
        return false;
    }
}