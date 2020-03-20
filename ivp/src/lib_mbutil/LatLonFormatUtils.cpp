/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Eng / CSAIL, MIT Cambridge MA     */
/*    FILE: LatLonFormatUtils.cpp                                */
/*    DATE: March 19th 2020                                      */
/*                                                               */
/* This file is part of IvP Helm Core Libs                       */
/*                                                               */
/* IvP Helm Core Libs is free software: you can redistribute it  */
/* and/or modify it under the terms of the Lesser GNU General    */
/* Public License as published by the Free Software Foundation,  */
/* either version 3 of the License, or (at your option) any      */
/* later version.                                                */
/*                                                               */
/* IvP Helm Core Libs is distributed in the hope that it will    */
/* be useful but WITHOUT ANY WARRANTY; without even the implied  */
/* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR       */
/* PURPOSE. See the Lesser GNU General Public License for more   */
/* details.                                                      */
/*                                                               */
/* You should have received a copy of the Lesser GNU General     */
/* Public License along with MOOS-IvP.  If not, see              */
/* <http://www.gnu.org/licenses/>.                               */
/*****************************************************************/

#include <iostream>
#include "LatLonFormatUtils.h"
#include "MBUtils.h"

using namespace std;

//--------------------------------------------------------
// Procedure: latDDtoDDMM()
//      Note: Convert 48.82530
//                    4849.518
//            49.518 minutes = 0.8253 degs * 60 minutes
//      Note: Negative latitudes are conveyed with positive
//            values. 23.82530 ==> 2349.518
//            It is assumed caller will handle appropriately
//            In the case of NMEA msgs, an N/S designator is used

string latDDtoDDMM(double gval)
{
  if((gval > 90) || (gval < -90))
    return("");
  if(gval < 0)
    gval = -gval;
  
  int degs = (int)(gval);

  gval = gval - (double)(degs);
  if(gval < 0)
    gval = -gval;

  double mins = gval * 60;

  string str = intToString(degs);
  if(str.length() == 1)
    str = "0" + str;

  if(mins < 10)
    str += "0";
  
  str += doubleToStringX(mins);
  
  return(str);
}


//--------------------------------------------------------
// Procedure: lonDDDtoDDMM()
//      Note: Convert 123.82530
//                    12349.518
//            49.518 minutes = 0.8253 degs * 60 minutes
//      Note: Negative Longitutes are conveyed with positive
//            values. -23.82530 ==> 02349.518
//            It is assumed caller will handle appropriately
//            In the case of NMEA msgs, an E/W designator is used

string lonDDDtoDDDMM(double gval)
{
  if((gval > 180) || (gval < -180))
    return("");
  if(gval < 0)
    gval = -gval;

  int degs = (int)(gval);

  gval = gval - (double)(degs);
  if(gval < 0)
    gval = -gval;

  double mins = gval * 60;

  string str = intToString(degs);
  if(str.length() == 1)
    str = "0" + str;
  if(str.length() == 2)
    str = "0" + str;

  if(mins < 10)
    str += "0";
  
  str += doubleToStringX(mins);

  return(str);
}

