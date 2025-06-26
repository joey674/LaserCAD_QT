#ifndef MOTIONSTAGEDEVICE_H
#define MOTIONSTAGEDEVICE_H
#include <tuple>

class MotionStageDevice
{
public:
    virtual ~MotionStageDevice() = default;
    virtual bool connect() {};
    virtual bool disconnect() {};
    virtual bool setPos(double x,double y,double z){};
    virtual bool setSpeed(){};
    virtual bool resetPos(){};
    std::tuple<double, double, double> getPos(){
        return std::make_tuple(m_x, m_y, m_z);
    };

    double m_x=0;
    double m_y=0;
    double m_z=0;

    double m_maxZ = 0;
    double m_minZ = 0;
    double m_maxX = 0;
    double m_minX= 0;
    double m_maxY = 0;
    double m_minY = 0;
};

#endif // MOTIONSTAGEDEVICE_H
