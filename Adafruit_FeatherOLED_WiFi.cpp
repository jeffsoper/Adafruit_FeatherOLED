/**************************************************************************/
/*!
    @file     Adafruit_FeatherOLED_WiFi.cpp
    @author   ktown

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2016, Adafruit Industries (adafruit.com)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/
#include "Adafruit_FeatherOLED_WiFi.h"

/******************************************************************************/
/*!
    @brief  Renders the RSSI icon
*/
/******************************************************************************/
void Adafruit_FeatherOLED_WiFi::renderRSSI( void )
{

  if (_rssiIcon)
  {
	//render antenna
    drawLine( 10,//x
              0,//yy
              14,//x_end
              0,//y_end
              WHITE);
    drawLine( 11,//x
              1,//yy
              13,//x_end
              1,//y_end
              WHITE);
    drawLine( 12,//x
              0,//yy
              12,//x_end
              6,//y_end
              WHITE);
    //need to adjust bars
    if (_rssi > -80) {
		drawLine( 2,//x
            6,//yy
            2,//x_end
            6,//y_end
            WHITE);
	}
	if (_rssi > -60) {
		drawLine( 4,//x
		    4,//yy
		    4,//x_end
		    6,//y_end
		    WHITE);
	}
	if (_rssi > -40) {
		drawLine( 6,//x
		    2,//yy
		    6,//x_end
		    6,//y_end
		    WHITE);

	}
	if (_rssi > -20) {
	    drawLine( 8,//x
            0,//yy
            8,//x_end
            6,//y_end
            WHITE);
	}
	setCursor(18,0);
  }

  if (_rssiVisible)
  {
	if (!_rssiIcon) {
    	setCursor(0,0);
	}
    print("RSSI:");
    if (_connected)
    {
      print(_rssi);
    }
    else
    {
      print("---");
    }
  }
}

/******************************************************************************/
/*!
    @brief  Renders the connection status icon
*/
/******************************************************************************/
void Adafruit_FeatherOLED_WiFi::renderConnected ( void )
{
  if (_connectedVisible)
  {
    setCursor(100,24);
    if (_connected)
    {
      println("CONN");
    }
    else
    {
      println("----");
    }
  }
}

/******************************************************************************/
/*!
    @brief  Renders the connection status icon
*/
/******************************************************************************/
void Adafruit_FeatherOLED_WiFi::renderIPAddress ( void )
{
  if (_ipAddressVisible)
  {
    if (_connected)
    {
      /*setCursor(0,24); printing in reverse order
      print((_ipAddress >> 24) & 0xFF, DEC);
      print(".");
      print((_ipAddress >> 16) & 0xFF, DEC);
      print(".");
      print((_ipAddress >> 8) & 0xFF, DEC);
      print(".");
      print(_ipAddress & 0xFF, DEC); */
      setCursor(0,24);
      print(_ipAddress & 0xFF, DEC);
      print(".");
      print((_ipAddress >> 8) & 0xFF, DEC);
      print(".");
      print((_ipAddress >> 16) & 0xFF, DEC);
      print(".");
      print((_ipAddress >> 24) & 0xFF, DEC);
    }
  }
}

/******************************************************************************/
/*!
    @brief  Updates the OLED display
*/
/******************************************************************************/
void Adafruit_FeatherOLED_WiFi::refreshIcons ( bool clearStatus)
{
  fillRect(0, 0, 128, 8, BLACK);
  if (clearStatus) { //status line is shared with the IP/connect
  	fillRect(0, 24, 128, 8, BLACK);
  	renderConnected();
	renderIPAddress();
  }
  renderBattery();
  renderRSSI();
  display();
}
