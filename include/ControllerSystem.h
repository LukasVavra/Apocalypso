#pragma once

#include <Singleton.h>
#include <PODContainer.h>
#include <vector>
#include <memory>

class ControllerInterface
{
public:
    virtual void update(long unsigned id) = 0;
    virtual ~ControllerInterface() = default;
};

class ControllerSystem : public Singleton<ControllerSystem>
{
public:
    struct ControlPOD
    {
        long unsigned id;
        std::shared_ptr<ControllerInterface> controller;
    };

    void update();
    void add(long unsigned controlled_id, std::shared_ptr<ControllerInterface> controller);
    ControlPOD* get(long unsigned controlled_id);
    void remove(long unsigned controlled_id);
    template <class CONTROLLER, typename... Args>
    std::shared_ptr<ControllerInterface>& create_controller(Args&&... args);
    
private:
    PODContainer<ControlPOD, 128> cntr;
    std::vector<std::shared_ptr<ControllerInterface>> controllers;
};

template <class CONTROLLER, typename... Args>
inline std::shared_ptr<ControllerInterface>& ControllerSystem::create_controller(Args&&... args)
{
    controllers.emplace_back(std::make_shared<CONTROLLER>(std::forward<Args>(args)...));
    return controllers.back();
}