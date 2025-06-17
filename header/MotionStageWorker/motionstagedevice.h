#ifndef MOTIONSTAGEDEVICE_H
#define MOTIONSTAGEDEVICE_H

class MotionStageDevice
{
public:
    virtual ~MotionStageDevice() = default;
    virtual bool connect() {};
    virtual bool disconnect() {};
    virtual bool setPos(double x,double y,double z){};
    virtual bool setSpeed(){};
};

#endif // MOTIONSTAGEDEVICE_H
