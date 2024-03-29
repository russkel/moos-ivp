/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: PIDEngine.h                                          */
/*    DATE: Jul 31st, 2005 Sunday in Montreal                    */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#ifndef MARINEX_PIDENGINE_HEADER
#define MARINEX_PIDENGINE_HEADER

#include <vector>
#include <list>
#include <string>
#include "ScalarPID.h"
#include "VarDataPair.h"

class PIDEngine {
public:
  PIDEngine();
  ~PIDEngine() {}

  void setSpeedFactor(double val) {m_speed_factor = val;}
  void updateTime(double val)     {m_curr_time = val;}
  void setStartTime(double val)   {m_start_time = val;}
  
  void setCurrHeading(double hdg);
  void setCurrSpeed(double spd);
  void setCurrDepth(double dep);
  void setCurrPitch(double pitch);

  void setDesHeading(double hdg);
  void setDesSpeed(double spd);
  void setDesDepth(double dep);

  void setDepthControl(bool v)        {m_depth_control=v;}
  bool hasDepthControl() const        {return(m_depth_control);}
  //  void setConfigParams(std::list<std::string> v) {m_config_params=v;}

  std::list<std::string>  setConfigParams(std::list<std::string>);

  bool hasControl()                   {return(!m_pid_override);}
  void setPIDOverride(bool v)         {m_pid_override=v;}
  void setPIDOverride(std::string);

  void setDesiredValues();
  bool checkForStaleness();
  
  bool handleYawSettings();
  bool handleSpeedSettings();
  bool handleDepthSettings();
  bool hasConfigSettingsForPID() const;
  
  void addPosting(std::string var, std::string val);
  void addPosting(std::string var, double val);
  std::vector<VarDataPair> getPostings() {return(m_postings);}
  void clearPostings() {m_postings.clear();}

  double getFrequency() const;
  
  double getDesiredRudder() const   {return(m_desired_rudder);}
  double getDesiredThrust() const   {return(m_desired_thrust);}
  double getDesiredElevator() const {return(m_desired_elevator);}

 protected:
  double setDesiredRudder();
  double setDesiredThrust();
  double setDesiredElevator();
  
 protected:
  ScalarPID m_heading_pid;
  ScalarPID m_speed_pid;
  ScalarPID m_z_to_pitch_pid;
  ScalarPID m_pitch_pid;

  std::list<std::string>   m_config_params;
  std::vector<std::string> m_config_errors;
  std::vector<std::string> m_config_info;
  
  double  m_speed_factor;
  double  m_curr_time;
  double  m_curr_thrust;
  double  m_start_time;
  unsigned int m_iterations;

  double  m_curr_heading;
  double  m_curr_speed;
  double  m_curr_depth;
  double  m_curr_pitch;
  double  m_curr_heading_tstamp;
  double  m_curr_speed_tstamp;
  double  m_curr_depth_tstamp;
  double  m_curr_pitch_tstamp;

  
  double  m_desired_hdg;
  double  m_desired_spd;
  double  m_desired_dep;
  double  m_desired_hdg_tstamp;
  double  m_desired_spd_tstamp;
  double  m_desired_dep_tstamp;

  double  m_desired_rudder;
  double  m_desired_thrust;
  double  m_desired_elevator;
  
  double  m_max_rudder;
  double  m_max_thrust;
  double  m_max_pitch;
  double  m_max_elevator;

  double  m_rudder_bias_duration;
  double  m_rudder_bias_limit;
  double  m_rudder_bias_side;
  double  m_rudder_bias_timestamp;

  bool    m_depth_control;
  bool    m_pid_override;
  
  std::vector<VarDataPair> m_postings;

  double  m_tardy_helm_thresh;
  double  m_tardy_nav_thresh;

  // Added April 2019 by mikerb
  // If debug settings on, ScalarPIDs will build debug output on
  // every iteration. Likely only want to do this if seeing max_sat.
  bool m_debug_hdg;
  bool m_debug_spd;
  bool m_debug_dep;

  bool m_simulation;
};
#endif




