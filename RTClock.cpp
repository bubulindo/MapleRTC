/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**

 */

#include "RTClock.h"

	/*RTC::RTC() {
		rtc_init(RTCSEL_LSE);//LSE should be 32768 Hz.
		rtc_set_prescaler_load(0x7fff); 
		rtc_set_count(0);//initializing... just in case
	}*/
	
	//only needed in case we're not using the Maple.
	/*RTC::RTC(rtc_clk_src src, uint32 prescaler ) {
		rtc_init(src);//HSE = 8/128MHz = 62500 Hz
		rtc_set_prescaler_load((prescaler & 0xFFFFF)); //according to sheet clock/(prescaler + 1) = Hz 0xF423 = 62499
		rtc_set_count(0);//initializing... just in case				
	}*/

    RTClock::RTClock(rtc_clk_src src ) {
	
	switch (src) {
	
		case RTCSEL_LSE : {
			rtc_init(RTCSEL_LSE);//LSE should be 32768 Hz.
			rtc_set_prescaler_load(0x7fff); //according to sheet clock/(prescaler + 1) = Hz
			break;
			}
		case RTCSEL_LSI : {
			rtc_init(RTCSEL_LSI);//LSI is around 40000 Hz (between 30000 and 60000).
			rtc_set_prescaler_load(0x9C3F); //according to sheet clock/(prescaler + 1) = Hz 39999Hz = 0x9C3F
			break;
			}
		case RTCSEL_HSE : {
			rtc_init(RTCSEL_HSE);//HSE = 8/128MHz = 62500 Hz
			rtc_set_prescaler_load(0xF423); //according to sheet clock/(prescaler + 1) = Hz 0xF423 = 62499
			break;
			}
		case RTCSEL_DEFAULT: {
			//do nothing. Have a look at the clocks to see the diff between NONE and DEFAULT
			break;
			}
		case RTCSEL_NONE: {
			//do nothing. Have a look at the clocks to see the diff between NONE and DEFAULT
			break;
			}
		
		}//end switch
	
	rtc_set_count(0);//initializing... just in case
	
	}//end RTC
	
	
	
	
	RTClock::~RTClock() {
	//to implement
	}	
	
	
	void RTClock::setTime (uint32 time_stamp) {
		rtc_set_count(time_stamp);
	}

	
	uint32 RTClock::getTime() {
		return rtc_get_count();
	}
	
	void RTClock::createAlarm(voidFuncPtr function, uint32 alarm_time_t) {
		rtc_set_alarm(alarm_time_t); //must be int... for standardization sake. 
		rtc_attach_interrupt(RTC_ALARM_SPECIFIC_INTERRUPT, function);
	}
	
	void RTClock::attachSecondsInterrupt(voidFuncPtr function) {
		rtc_attach_interrupt(RTC_SECONDS_INTERRUPT, function);
	}
	void RTClock::detachSecondsInterrupt(voidFuncPtr function) {
		rtc_detach_interrupt(RTC_SECONDS_INTERRUPT);
	}


	
/*	void RTC::createAlarm(voidFuncPtr function, tm* alarm_tm) {
	
	time_t alarm = mktime(alarm_tm);//convert to time_t
	
	createAlarm(function, alarm);
		
	}*/
	
	/*	void RTC::setTime (tm * tm_ptr) {
	
	time_t time = mktime(tm_ptr);//convert to time_t
	rtc_set_count(time); 
	}*/
	
/*	tm* RTC::getTime() {
	time_t time = getCount(); 
	return localtime(&time); //return tm pointer
	}*/
	
	
