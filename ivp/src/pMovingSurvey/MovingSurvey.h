/************************************************************/
/*    NAME: Michael Benjamin                                */
/*    ORGN: MIT                                             */
/*    FILE: MovingSurvey.h                                  */
/*    DATE: October 7th, 2019                               */
/************************************************************/

#ifndef MOVING_SURVEY_HEADER
#define MOVING_SURVEY_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <string>
#include "XYSegList.h"


class MovingSurvey : public AppCastingMOOSApp
{
 public:
  MovingSurvey();
  ~MovingSurvey();
  
 protected: // Standard MOOSApp functions to overload  
  bool OnNewMail(MOOSMSG_LIST &NewMail);
  bool Iterate();
  bool OnConnectToServer();
  bool OnStartUp();
  
 protected: // Standard AppCastingMOOSApp function to overload 
  bool buildReport();
  bool handleConfigSurvey(std::string);
  void updateSurveyLocation();
  void postUpdatedSurvey();
  
 protected:
  void registerVariables();

 private: // Configuration variables

  XYSegList m_survey;
  double    m_speed;
  double    m_heading;
  double    m_rpm;      // rotations per minute
  double    m_dps;      // degrees per second

  double    m_survey_x;
  double    m_survey_y;
  double    m_prev_time;

  std::string m_update_var;

  double    m_update_freq;
  
 private: // State variables

};

#endif 
