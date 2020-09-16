#include "WLFlags.h"

WLFlags::WLFlags()
{
reset();
}

WLFlags::~WLFlags()
{

}

bool WLFlags::get(long get_flag)
{
return ((m_Data&get_flag)==get_flag);
}

void WLFlags::tog(long flag)
{
m_Data^=flag;
}

bool WLFlags::set(long set_flag,bool set_data)
{
if(set_data) m_Data|=set_flag; else m_Data&=~set_flag;

return set_data;
}


void WLFlags::reset()
{
m_Data=0;
}



