#include "drawmanager.h"

DrawManager DrawManager::ins;

DrawManager &DrawManager::getIns()
{
    return ins;
}
