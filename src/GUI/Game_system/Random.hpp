#include <stdio.h>


class Random{
private:
    unsigned m_z, m_w;
public:
    Random(unsigned seed): m_z(seed),m_w(seed){}
    unsigned nextInt(){
        m_z = 36969 * (m_z & 65535) + (m_z >> 16);
        m_w = 18000 * (m_w & 65535) + (m_w >> 16);
        return ((m_z << 16) + m_w)%7;
    }
};
