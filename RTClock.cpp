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

	RTClock::RTClock() {
		//rtc_init(RTCSEL_HSE);//HSE should be .
		//rtc_set_prescaler_load(0xf423); 
		//rtc_set_count(0);//initializing... just in case
		RTClock(RTCSEL_HSE, 0xf423);
	}

    RTClock::RTClock(rtc_clk_src src) {
	//uint16 prescal = 0x7fff; //just in case
	
	/*
	switch (src) {
	
		case RTCSEL_LSE : {
			//rtc_init(RTCSEL_LSE);//LSE should be 32768 Hz.
			//rtc_set_prescaler_load(0x7fff); //according to sheet clock/(prescaler + 1) = Hz
			prescal = 0x7fff;
			
			
			break;
			}
		case RTCSEL_LSI : {
			//rtc_init(RTCSEL_LSI);//LSI is around 40000 Hz (between 30000 and 60000).
			//rtc_set_prescaler_load(0x9C3F); //according to sheet clock/(prescaler + 1) = Hz 39999Hz = 0x9C3F
			prescal = 0x9C3F; 
			break;
			}
		case RTCSEL_HSE : {
			//rtc_init(RTCSEL_HSE);//HSE = 8/128MHz = 62500 Hz
			//rtc_set_prescaler_load(0xF423); //according to sheet clock/(prescaler + 1) = Hz 0xF423 = 62499
			prescal = 0xf423; 
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
	
	*/
	
	//rtc_set_count(0);//initializing... not needed. 
	
	RTClock(src, 0);
	
	}//end RTC

	RTClock::RTClock(rtc_clk_src src, uint16 prescaler ) {
		switch (src) {
	
		case RTCSEL_LSE : {
			rtc_init(RTCSEL_LSE);//LSE should be 32768 Hz.
			if (prescaler != 0) rtc_set_prescaler_load(prescaler); //according to sheet clock/(prescaler + 1) = Hz
			else rtc_set_prescaler_load(0x7fff);
			break;
			}
		case RTCSEL_LSI : {
			rtc_init(RTCSEL_LSI);//LSI is around 40000 Hz (between 30000 and 60000).
			if (prescaler != 0) rtc_set_prescaler_load(prescaler); //according to sheet clock/(prescaler + 1) = Hz 39999Hz = 0x9C3F
			else rtc_set_prescaler_load(0x9C3F);
			break;
			}
		case RTCSEL_HSE : {
			rtc_init(RTCSEL_HSE);//HSE = 8/128MHz = 62500 Hz
			if (prescaler != 0) rtc_set_prescaler_load(prescaler); //according to sheet clock/(prescaler + 1) = Hz 0xF423 = 62499
			else rtc_set_prescaler_load(0xF423);
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
	

	}

	RTClock::~RTClock() {
	//to implement
	}
	
	
	void RTClock::setTime (time_t time_stamp) {
		rtc_set_count(time_stamp);
	}
	
	void RTClock::setTime (struct tm* tm_ptr) {
		rtc_set_count(mktime (tm_ptr));
	}
	
	time_t RTClock::getTime() {
		return rtc_get_count();
	}
	
	struct tm*  RTClock::getTime(struct tm* tm_ptr) {
		time_t res = rtc_get_count();
		tm_ptr = localtime(&res); //why not gmtime? 
		
		
		return tm_ptr;
	}
	
	void RTClock::createAlarm(voidFuncPtr function, time_t alarm_time_t) {
		rtc_set_alarm(alarm_time_t); //must be int... for standardization sake. 
		rtc_attach_interrupt(RTC_ALARM_SPECIFIC_INTERRUPT, function);
	}
	
	void RTClock::attachSecondsInterrupt(voidFuncPtr function) {
		rtc_attach_interrupt(RTC_SECONDS_INTERRUPT, function);
	}
	void RTClock::detachSecondsInterrupt() {
		rtc_detach_interrupt(RTC_SECONDS_INTERRUPT);
	}

	
	void RTClock::createAlarm(voidFuncPtr function, tm* alarm_tm) {
		time_t alarm = mktime(alarm_tm);//convert to time_t
		createAlarm(function, alarm);	
	}
	
	
//change alarm time	
	void RTClock::setAlarmTime (tm * tm_ptr) {
		time_t time = mktime(tm_ptr);//convert to time_t
		rtc_set_alarm(time); //must be int... for standardization sake. 
	}
	

	
