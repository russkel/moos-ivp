/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: PMGen.cpp                                            */
/*    DATE: Jan 1st, 2024                                        */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include "AngleUtils.h"
#include "PMGen.h"

using namespace std;

//----------------------------------------------------------------
// Procedure: setHdgHist()

void PMGen::setHdgHist(std::list<double> hdgs, std::list<double> utcs)
{
  m_recent_val_osh=hdgs;
  m_recent_utc_osh=utcs;  

  cout << "HeadingHistSet:" << m_recent_val_osh.size() << endl;
}


//----------------------------------------------------------------
// Procedure: getHdgAvg()

double PMGen::getHdgAvg(double time_window)
{
  list<double> hdgs = m_recent_val_osh;
  list<double> utcs = m_recent_utc_osh;

  if(hdgs.size() != utcs.size())
    return(-1);

  if(hdgs.size() == 0)
    return(-1);

  cout << "getHdgAvg(1):" << endl;

  double prev_hdg = hdgs.front();
  double most_recent_utc = utcs.front();
  hdgs.pop_front();
  utcs.pop_front();

  double total_delta_hdg = 0;
  unsigned int count = 0;

  cout << "getHdgAvg(a): prev_hdg" << prev_hdg << endl;
  cout << "getHdgAvg(b): newest_utc" << doubleToStringX(most_recent_utc) << endl;
  
  bool done = false;
  while(!done) {
    if(hdgs.size() == 0)
      break;

    double hdg = hdgs.front();
    double utc = utcs.front();
    cout << "getHdgAvg(c): hdg" << hdg << endl;
    cout << "getHdgAvg(d): utc" << doubleToStringX(utc) << endl;

    double elapsed = most_recent_utc - utc;
    if(elapsed > time_window)
      done = true;
    else {
      // Will return smaller of two deltas given possible ang wrap
      double delta_hdg = angleDiff(hdg, prev_hdg);
      // If port turn then delta is negative, otherwise stays positive
      if(portTurn(hdg, prev_hdg))
	delta_hdg = -delta_hdg;
      
      total_delta_hdg += delta_hdg;
      prev_hdg = hdg;
      count++;
    }
      
    hdgs.pop_front();
    utcs.pop_front();
  }

  cout << "getHdgAvg(2) count: " << count << endl;
  
  if(count == 0)
    return(0);

  double avg = total_delta_hdg / (double)(count);
  cout << "getHdgAvg(3) avg: " << count << endl;
  return(avg);
}
