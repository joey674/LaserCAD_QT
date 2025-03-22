#include "graphicsitemmanager.h"

SceneOperation SceneOperation::ins;

SceneOperation &SceneOperation::getIns()
{
    return ins;
}
