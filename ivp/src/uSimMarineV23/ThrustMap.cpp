/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: ThrustMap.cpp                                        */
/*    DATE: Dec 16th 2010                                        */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <iostream>
#include "ThrustMap.h"
#include "MBUtils.h"

using namespace std;

//----------------------------------------------------------------
// Constructor

ThrustMap::ThrustMap()
{
  m_min_thrust = -100;
  m_max_thrust =  100;
  m_reflect_negative = false;

  m_figlog.setLabel("ThrustMap");

  // For legacy reasons, we support the "thrust_factor" simple
  // form of a thrust map. This is overridden as soon as a 
  // positive pair is added to the map.
  m_thrust_factor = 0;
}


//----------------------------------------------------------------
// Procedure: addPair()

bool ThrustMap::addPair(double thrust, double speed)
{
  if((thrust < m_min_thrust) || (thrust > m_max_thrust)) {
    m_figlog.addWarning("Thrust Out of Range:" + doubleToString(thrust));
    return(false);
  }

  if(thrust > 0) {
    if(speed >= 0) {
      map<double, double> new_pos_mapping = m_pos_mapping;
      new_pos_mapping[thrust] = speed;
      if(isAscendingMap(new_pos_mapping))
	m_pos_mapping = new_pos_mapping;
      else {
	m_figlog.addError("Non-Ascending pair rejected: ");
	m_figlog.augError(doubleToStringX(thrust));
	m_figlog.augError(":" + doubleToStringX(speed));
	return(false);
      }
    }
    else {
      m_figlog.addError("Mapping negative speed to positive thrust: ");
      m_figlog.augError(doubleToStringX(thrust)+":");
      m_figlog.augError(doubleToStringX(speed));
      return(false);
    }
  }
  else if(thrust < 0) {
    if(speed <= 0) {
      map<double, double> new_neg_mapping = m_neg_mapping;
      new_neg_mapping[thrust] = speed;
      if(isAscendingMap(new_neg_mapping))
	m_neg_mapping = new_neg_mapping;
      else {
	m_figlog.addError("Non-Ascending pair rejected: ");
	m_figlog.augError(doubleToStringX(thrust));
	m_figlog.augError(":" + doubleToStringX(speed));
	return(false);
      }
    }
    else {
      m_figlog.addError("Mapping positive speed to negative thrust: ");
      m_figlog.augError(doubleToStringX(thrust)+":");
      m_figlog.augError(doubleToStringX(speed));
      return(false);
    }
  }
  else if((thrust == 0) && (speed != 0)) {
    m_figlog.addError("Mapping a non-zero speed to zero-thrust: ");
    m_figlog.augError(doubleToStringX(speed));
    return(false);
  }

  return(true);
}

//----------------------------------------------------------------
// Procedure: setThrustFactor
//      Note: When there is no mapping set otherwise for positive
//            thrust values, the thrust_factor will be used to 
//            calculate the speed = thrust/thrust_factor.

void ThrustMap::setThrustFactor(double value)
{
  if(value >= 0)
    m_thrust_factor = value;
}

//----------------------------------------------------------------
// Procedure: setMinMaxThrust()

void ThrustMap::setMinMaxThrust(double min_thrust, double max_thrust)
{
  if(min_thrust > max_thrust) {
    m_figlog.addWarning("Failed attempt to set Min/Max Thrust Range");
    return;
  }

  m_min_thrust = min_thrust;
  m_max_thrust = max_thrust;

  map<double, double>::iterator p;

  map<double, double> new_neg_mapping;
  p = m_neg_mapping.begin();
  while(p != m_neg_mapping.end()) {
    double thrust = p->first;
    double speed  = p->second;
    if((thrust >= m_min_thrust) && (thrust <= m_max_thrust))
      new_neg_mapping[thrust] = speed;
    p++;
  }
  m_neg_mapping = new_neg_mapping;

  map<double, double> new_pos_mapping;
  p = m_pos_mapping.begin();
  while(p != m_pos_mapping.end()) {
    double thrust = p->first;
    double speed  = p->second;
    if((thrust >= m_min_thrust) && (thrust <= m_max_thrust))
      new_pos_mapping[thrust] = speed;
    p++;
  }
  m_pos_mapping = new_pos_mapping;
}

//----------------------------------------------------------------
// Procedure: getSpeedValue()

double ThrustMap::getSpeedValue(double thrust) const
{
  if(thrust < 0)
    return(getSpeedValueNeg(thrust));
  else if(thrust > 0)
    return(getSpeedValuePos(thrust));
  else
    return(0);
}

//----------------------------------------------------------------
// Procedure: getThrustValue()

double ThrustMap::getThrustValue(double speed) const
{
  if(speed < 0)
    return(getThrustValueNeg(speed));
  else if(speed > 0)
    return(getThrustValuePos(speed));
  else
    return(0);
}

//----------------------------------------------------------------
// Procedure: isAscending()

bool ThrustMap::isAscending() const
{
  bool neg_ascending = isAscendingMap(m_neg_mapping);
  bool pos_ascending = isAscendingMap(m_pos_mapping);
  return(pos_ascending && neg_ascending);
}

//----------------------------------------------------------------
// Procedure: getThrustFactor()

double ThrustMap::getThrustFactor() const
{
  return(m_thrust_factor);
}

//----------------------------------------------------------------
// Procedure: isAscendingMap()

bool ThrustMap::isAscendingMap(map<double, double> gmap) const
{
  if(gmap.size() == 0)
    return(true);

  map<double, double>::const_iterator p;
  p = gmap.begin();
  double prev_range = p->second;
  p++;  
  while(p != gmap.end()) {
    double range  = p->second;
    if(range < prev_range) 
      return(false);
    prev_range = range;
    p++;
  }
  return(true);
}

//----------------------------------------------------------------
// Procedure: print()

void ThrustMap::print() const
{
  cout << "Thrust Map: ----------------------------------------" << endl;
  map<double, double>::const_iterator p;
  p = m_neg_mapping.begin();
  while(p != m_neg_mapping.end()) {
    double thrust = p->first;
    double speed  = p->second;
    cout << "thrust: " << thrust << "  speed: " << speed << endl;
    p++;
  }

  p = m_pos_mapping.begin();
  while(p != m_pos_mapping.end()) {
    double thrust = p->first;
    double speed  = p->second;
    cout << "thrust: " << thrust << "  speed: " << speed << endl;
    p++;
  }

  m_figlog.print();
}

//----------------------------------------------------------------
// Procedure: clear()

void ThrustMap::clear() 
{
  m_pos_mapping.clear();
  m_neg_mapping.clear();
  m_thrust_factor = 0;
  m_figlog.clear();
}

//----------------------------------------------------------------
// Procedure: usingThrustFactor()
//      Note: The thrust factor is used by default to calculated speed
//            for a given thrust, unless/until a thrus mapping is provided. 

bool ThrustMap::usingThrustFactor() const
{
  if(m_pos_mapping.size() == 0)
    return(true);
  else
    return(false);
}

//----------------------------------------------------------------
// Procedure: getMapPos()

string ThrustMap::getMapPos() const
{
  string posmap;

  map<double, double>::const_iterator p;
  for(p=m_pos_mapping.begin(); p!=m_pos_mapping.end(); p++) {
    double thrust = p->first;
    double speed  = p->second;
    if(posmap != "")
      posmap += ", ";
    posmap += doubleToStringX(thrust,4);
    posmap += ","+ doubleToStringX(speed, 4);
  }
  return(posmap);
}

//----------------------------------------------------------------
// Procedure: getMapNeg()

string ThrustMap::getMapNeg() const
{
  if(m_reflect_negative)
    return("Positive thrust-map reflected");
  
  string negmap;
  map<double, double>::const_iterator p;
  for(p=m_neg_mapping.begin(); p!=m_neg_mapping.end(); p++) {
    double thrust = p->first;
    double speed  = p->second;
    if(negmap != "")
      negmap += ", ";
    negmap += doubleToStringX(thrust,4);
    negmap += ":"+ doubleToStringX(speed, 4);
  }
  return(negmap);
}


//----------------------------------------------------------------
// Procedure: getSpeedValueNeg()

double ThrustMap::getSpeedValueNeg(double thrust) const
{
  if(m_neg_mapping.size() == 0) {
    if(m_reflect_negative) {
      double pos_thrust = -1 * thrust;
      double pos_speed  = getSpeedValuePos(pos_thrust);
      double ret_speed  = -1 * pos_speed;
      return(ret_speed);
    }
    else
      return(0);
  }
  
  map<double, double>::const_iterator p = m_neg_mapping.begin();
  
  double left_dom = m_min_thrust;
  double left_val = p->second;

  if(thrust <= m_min_thrust)
    return(left_val);

  double right_dom = 0;
  double right_val = 0;

  bool found = false;
  while((p != m_neg_mapping.end()) && !found) {
    double ithrust = p->first;
    double ispeed  = p->second;

    if(thrust <= ithrust) {
      right_dom = ithrust;
      right_val = ispeed;
      found = true;
    }
    else {
      left_dom = ithrust;
      left_val = ispeed;
    }    
    p++;
  }

  double run = (right_dom - left_dom);
  if(run <= 0)
    return(0);

  double rise  = (right_val - left_val);
  double slope = rise / run;

  double speed_val = ((thrust-left_dom) * slope) + left_val;

  return(speed_val);
}

//----------------------------------------------------------------
// Procedure: getSpeedValuePos()

double ThrustMap::getSpeedValuePos(double thrust) const
{
  if(m_pos_mapping.size() == 0) {
    if(m_thrust_factor == 0)
      return(0);
    else
      return(thrust / m_thrust_factor);
  }
  
  map<double, double>::const_reverse_iterator p = m_pos_mapping.rbegin();
  
  double right_dom = m_max_thrust;
  double right_val = p->second;

  if(thrust >= m_max_thrust)
    return(right_val);

  double left_dom = 0;
  double left_val = 0;

  bool found = false;
  while((p != m_pos_mapping.rend()) && !found) {
    double ithrust = p->first;
    double ispeed  = p->second;

    if(thrust >= ithrust) {
      left_dom = ithrust;
      left_val = ispeed;
      found = true;
    }
    else {
      right_dom = ithrust;
      right_val = ispeed;
    }    
    p++;
  }

  double run = (right_dom - left_dom);
  if(run <= 0) 
    return(0);

  double rise  = (right_val - left_val);
  double slope = rise / run;

  double speed_val = ((thrust-left_dom) * slope) + left_val;

  return(speed_val);
}

//----------------------------------------------------------------
// Procedure: getThrustValuePos()

double ThrustMap::getThrustValuePos(double speed) const
{
  if(m_pos_mapping.size() == 0) {
    if(m_thrust_factor == 0)
      return(0);
    else
      return(speed * m_thrust_factor);
  }

  map<double, double>::const_reverse_iterator p = m_pos_mapping.rbegin();
  
  double right_dom = m_max_thrust;
  double right_val = p->second;

  if(speed >= right_val)
    return(m_max_thrust);

  double left_dom = 0;
  double left_val = 0;

  bool found = false;
  while((p != m_pos_mapping.rend()) && !found) {
    double ithrust = p->first;
    double ispeed  = p->second;

    if(speed > ispeed) {
      left_dom = ithrust;
      left_val = ispeed;
      found = true;
    }
    else {
      right_dom = ithrust;
      right_val = ispeed;
    }    
    p++;
  }

  double run = (right_dom - left_dom);
  if(run <= 0) 
    return(0);

  double rise  = (right_val - left_val);
  double slope = rise / run;
  double b     = left_val - slope * left_dom;

  double thrust_val;
  if(slope == 0)
    thrust_val = left_dom;
  else
    thrust_val = (speed - b) / slope;

  //cout << "left_val:" << left_val;
  //cout << "right_val:" << right_val;
  //cout << "Slope: " << slope << endl;
  return(thrust_val);
}

//----------------------------------------------------------------
// Procedure: getThrustValueNeg()

double ThrustMap::getThrustValueNeg(double speed) const
{
  if(m_neg_mapping.size() == 0) {
    if(m_reflect_negative)
      return(-1 * getThrustValuePos(-speed));
    else
      return(0);
  }
  
  map<double, double>::const_iterator p = m_neg_mapping.begin();
  
  double left_dom = m_min_thrust;
  double left_val = p->second;

  if(speed <= left_val)
    return(m_min_thrust);

  double right_dom = 0;
  double right_val = 0;

  bool found = false;
  while((p != m_neg_mapping.end()) && !found) {
    double ithrust = p->first;
    double ispeed  = p->second;

    if(speed <= ispeed) {
      right_dom = ithrust;
      right_val = ispeed;
      found = true;
    }
    else {
      left_dom = ithrust;
      left_val = ispeed;
    }    
    p++;
  }

  double run = (right_dom - left_dom);
  if(run <= 0)
    return(0);

  double rise  = (right_val - left_val);
  double slope = rise / run;
  double b = left_val - slope * left_dom;

  
  double thrust_val = 0;
  if(slope == 0)
    thrust_val = left_dom;
  else
    thrust_val = (speed - b) / slope;

  return(thrust_val);
}


//----------------------------------------------------------------
// Procedure: isConfigured()

bool ThrustMap::isConfigured() const
{
  if((m_pos_mapping.size() + m_neg_mapping.size()) == 0)
    return(false);

  return(true);
}


//----------------------------------------------------------------
// Procedure: stringToThrustMap()

ThrustMap stringToThrustMap(string str)
{
  ThrustMap thrust_map_null;
  ThrustMap thrust_map;

  vector<string> svector = parseString(str, ',');
  for(unsigned int i=0; i<svector.size(); i++) {
    string thrust = biteStringX(svector[i], ':');
    string speed  = svector[i];
    if(!isNumber(thrust) || !isNumber(speed))
      return(thrust_map_null);
    double dthrust = atof(thrust.c_str());
    double dspeed  = atof(speed.c_str());
    bool ok = thrust_map.addPair(dthrust, dspeed);
    if(!ok)
      return(thrust_map_null);
  }
  
  return(thrust_map);
}

