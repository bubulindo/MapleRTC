#include "utility/rtc_util.h"
#include "wirish.h"
#include <time.h>


#ifndef _RTCLOCK_H_
#define _RTCLOCK_H_

class RTClock {
 public:
 	//RTClock();
    RTClock(rtc_clk_src src ); 
	//RTC(rtc_clk_src src, uint32 prescaler );//only needed in case we're not using the Maple. 
	~RTClock(); 
	void setTime (uint32 time_stamp);
	//void setTime (struct tm * tstamp_ptr); 
	
	//struct tm* getTime(); 
	uint32 getTime();
	
	void createAlarm(voidFuncPtr function, uint32 alarm_time_t); 
	//void createAlarm(voidFuncPtr function, struct tm* alarm_tm);
	
	void attachSecondsInterrupt(voidFuncPtr function); 
	void detachSecondsInterrupt(voidFuncPtr function);
 //private:

} ;



#endif // _RTC_H_
                                                                                        