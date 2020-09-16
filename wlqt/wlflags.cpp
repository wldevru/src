#include "wlflags.h"

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

bool WLFlags::set(long set_flag,bool set_data)
{
if(set_data) m_Data|=set_flag; else	m_Data&=~set_flag;

return set_data;
}


void WLFlags::tog(long tog_flag)
{
m_Data^=tog_flag;
}


void WLFlags::reset()
{
m_Data=0;
}



