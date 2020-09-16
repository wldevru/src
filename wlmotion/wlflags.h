#ifndef WLFLAGS_H
#define WLFLAGS_H

struct WLFlags
{
	WLFlags();
   ~WLFlags();

bool set(long,bool set=true);
bool get(long);
bool reset(long fl) {return set(fl,false);}

void tog(long);
void reset();

long m_Data;	
};


#endif // WLFLAGS_H
