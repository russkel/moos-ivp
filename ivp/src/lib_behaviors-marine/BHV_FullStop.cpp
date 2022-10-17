/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: BHV_FullStop.cpp                                     */
/*    DATE: Oct 16th 2022                                        */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <cmath>
#include <cstdlib>
#include "GeomUtils.h"
#include "VarDataPairUtils.h"
#include "BHV_FullStop.h"
#include "MBUtils.h"
#include "BuildUtils.h"
#include "ZAIC_PEAK.h"
#include "ZAIC_LEQ.h"
#include "MacroUtils.h"
#include "OF_Coupler.h"

using namespace std;

//-----------------------------------------------------------
// Constructor()

BHV_FullStop::BHV_FullStop(IvPDomain gdomain) : IvPBehavior(gdomain)
{
  this->setParam("descriptor", "zig");
  
  m_domain = subDomain(m_domain, "course,speed");

  // =======================================================
  // Init State vars
  resetState();
  
  // =======================================================
  // Init Config vars
  m_mark_duration  = 0;
  m_stop_thresh    = 0.1;
  m_stale_nav_thresh = 10;
  
  addInfoVars("NAV_X, NAV_Y, NAV_SPEED, NAV_HEADING");
}

//-----------------------------------------------------------
// Procedure: resetState()

void BHV_FullStop::resetState()
{
  m_odometer.reset();
  m_stem_hdg = 0;
  m_stem_utc = 0;
  m_max_dist_to_begin_pt = -1;
}

//-----------------------------------------------------------
// Procedure: onSetParamComplete()

void BHV_FullStop::onSetParamComplete() 
{
  m_begin_pt.set_label("fstop_" + m_us_name);

  // Visual Hint Defaults for the leg/turn paths
  m_hints.setMeasure("vertex_size", 10);
  m_hints.setColor("vertex_color", "pink");
  m_hints.setColor("label_color", "off");
}

//-----------------------------------------------------------
// Procedure: setParam()

bool BHV_FullStop::setParam(string param, string value) 
{
  if(IvPBehavior::setParam(param, value))
    return(true);
  
  bool handled = true;
  if(param == "stop_thresh")
    handled = setNonNegDoubleOnString(m_stop_thresh, value);
  else if(param == "mark_duration")
    handled = setNonNegDoubleOnString(m_mark_duration, value);
  else if(param == "visual_hints")  
    return(m_hints.setHints(value));
  else if(param == "mark_flag") 
    return(addVarDataPairOnString(m_mark_flags, value));
  else if(param == "unmark_flag") 
    return(addVarDataPairOnString(m_unmark_flags, value));
  
  else
    handled = false;

  return(handled);
}

//-----------------------------------------------------------
// Procedure: onRunState()

IvPFunction *BHV_FullStop::onRunState() 
{
  // Part 1: Update OS position, hdg, spd and odometer
  if(!updateOSPos() || !updateOSHdg() || !updateOSSpd())
    return(0);
  updateOdometer();
  
  // Part 2: Handle Mark Flags if any.  Note flags are posted
  // with no repeats allowed
  if((m_mark_flags.size() != 0) || (m_mark_flags.size() != 0)) {
    double curr_time = getBufferCurrTime();
    double elapsed = curr_time - m_stem_utc;
    if(elapsed >= m_mark_duration)
      postFlags(m_unmark_flags);
    else
      postFlags(m_mark_flags);
  }
  
  // Part 2: Check if FullStop has been achieved
  bool full_stop_done = checkForFullStop();
  if(full_stop_done) {
    setComplete();
    postBeginPoint(false);
    if(m_perpetual)
      resetState();
    return(0);
  }
  
  // Part 3: Create the IvP Function
  IvPFunction *ipf = buildOF();
  if(ipf) 
    ipf->setPWT(m_priority_wt);
  
  return(ipf);
}

//-----------------------------------------------------------
// Procedure: checkForFullStop()

bool BHV_FullStop::checkForFullStop() 
{
  // Criteria 1: reached threshold speed
  if(m_osv < m_stop_thresh)
    return(true);

  // Criteria 2: Have moved closer to begin pt
  double dist = hypot(m_osx - m_begin_pt.x(),
		      m_osy - m_begin_pt.y());
  
  if(m_max_dist_to_begin_pt == -1)
    m_max_dist_to_begin_pt = dist;

  if(dist < m_max_dist_to_begin_pt)
    return(true);

  return(false);
}


//-----------------------------------------------------------
// Procedure: buildOF()

IvPFunction *BHV_FullStop::buildOF() 
{
  IvPFunction *ipf = 0;  

  //===================================================
  // Part 1: Build the Speed ZAIC
  //===================================================
  IvPFunction *spd_ipf = 0;  

  ZAIC_LEQ spd_zaic(m_domain, "speed");
  spd_zaic.setSummit(0);
  spd_zaic.setSummitDelta(0);
  spd_zaic.setBaseWidth(0);
  spd_zaic.setMinMaxUtil(0,100);
  spd_ipf = spd_zaic.extractIvPFunction();
  if(!spd_ipf)
    postWMessage("Failure on the SPD ZAIC component");

  //===================================================
  // Part 2: Build the Heading ZAIC
  //===================================================
  ZAIC_PEAK crs_zaic(m_domain, "course");
  crs_zaic.setSummit(m_stem_hdg);
  crs_zaic.setBaseWidth(180);
  crs_zaic.setValueWrap(true);  
  IvPFunction *crs_ipf = crs_zaic.extractIvPFunction(false);  
  if(!crs_ipf) 
    postWMessage("Failure on the CRS ZAIC");

  OF_Coupler coupler;
  ipf = coupler.couple(crs_ipf, spd_ipf, 50, 50);
  if(!ipf)
    postWMessage("Failure on the CRS_SPD COUPLER");

  ipf->getPDMap()->normalize(0,100);
  ipf->setPWT(m_priority_wt);
  
  return(ipf);
}

//-----------------------------------------------------------
// Procedure: onRunToIdleState()

void BHV_FullStop::onRunToIdleState()
{
  resetState();
  m_odometer.pause();
  postBeginPoint(false);
}

//-----------------------------------------------------------
// Procedure: onIdleToRunState()

void BHV_FullStop::onIdleToRunState()
{
  if(!updateOSPos() || !updateOSHdg())
    return;

  m_stem_utc = getBufferCurrTime();
  m_stem_hdg = m_osh;
  m_begin_pt.set_vertex(m_osx, m_osy);

  postBeginPoint(true);
  
  m_odometer.reset();  
  m_odometer.unpause();
}

//-----------------------------------------------------------
// Procedure: updateOSPos()
//   Returns: true if NAV_X/Y info is found and not stale
//            false otherwise

bool BHV_FullStop::updateOSPos(string fail_action) 
{
  bool   ok_osx = true;
  bool   ok_osy = true;
  double new_osx = getBufferDoubleVal("NAV_X", ok_osx);
  double new_osy = getBufferDoubleVal("NAV_Y", ok_osy);
  double age_osx = getBufferTimeVal("NAV_X");
  double age_osy = getBufferTimeVal("NAV_Y");

  bool all_ok = true;
  if(!ok_osy || !ok_osy)
    all_ok = false;

  if((age_osx > m_stale_nav_thresh) ||
     (age_osy > m_stale_nav_thresh))
    all_ok = false;
  
  if(!all_ok) {
    if(fail_action == "err")
      postEMessage("ownship NAV_X/Y not found or stale.");
    else if(fail_action == "warn")
      postWMessage("ownship NAV_X/Y not found or stale.");
    return(false);
  }

  m_osx = new_osx;
  m_osy = new_osy;
  return(true);
}

//-----------------------------------------------------------
// Procedure: updateOSHdg()
//   Returns: true if NAV_HEADING info is found and not stale
//            false otherwise

bool BHV_FullStop::updateOSHdg(string fail_action) 
{
  bool   ok_osh = true;
  double new_osh = getBufferDoubleVal("NAV_HEADING", ok_osh);
  double age_osh = getBufferTimeVal("NAV_HEADING");

  if(!ok_osh || (age_osh > m_stale_nav_thresh)) {
    if(fail_action == "err")
      postEMessage("ownship NAV_HEADING not found or stale.");
    else if(fail_action == "warn")
      postWMessage("ownship NAV_HEADING not found or stale.");
    return(false);
  }

  m_osh = new_osh;
  return(true);
}

//-----------------------------------------------------------
// Procedure: updateOSSpd()
//   Returns: true: if NAV_SPEED info is found and not stale
//            false: otherwise

bool BHV_FullStop::updateOSSpd(string fail_action) 
{
  bool   ok_osv  = true;
  double new_osv = getBufferDoubleVal("NAV_SPEED", ok_osv);
  double age_osv = getBufferTimeVal("NAV_SPEED");
  
  if(!ok_osv || (age_osv > m_stale_nav_thresh)) {
    if(fail_action == "err")
      postEMessage("ownship NAV_SPEED not found or stale.");
    else if(fail_action == "warn")
      postWMessage("ownship NAV_SPEED not found or stale.");
    return(false);
  }

  m_osv = new_osv;
  return(true);

}

//-----------------------------------------------------------
// Procedure: updateOdometer()

bool BHV_FullStop::updateOdometer()
{
  m_odometer.setX(m_osx);
  m_odometer.setY(m_osy);
   
  m_odometer.updateDistance();

  return(true);
}

//------------------------------------------------------------
// Procedure: postBeginPoint()
//   Purpose: Draw point where full-stop began

void BHV_FullStop::postBeginPoint(bool active)
{
  if(!active) {
    postMessage("VIEW_POINT", m_begin_pt.get_spec_inactive(), "bpt1");
    return;
  }

  applyHints(m_begin_pt, m_hints);

  string spec = m_begin_pt.get_spec();
  postMessage("VIEW_POINT", spec, "bpt1");
}

//-----------------------------------------------------------
// Procedure: expandMacros() 

string BHV_FullStop::expandMacros(string sdata)
{
  sdata = IvPBehavior::expandMacros(sdata);

  double odo_dist = m_odometer.getTotalDist();
  double mark_elapsed = 0;
  if(m_stem_utc > 0)
    mark_elapsed = getBufferCurrTime() - m_stem_utc;
  
  sdata = macroExpand(sdata, "STOP_DIST", odo_dist);
  sdata = macroExpand(sdata, "STOP_TIME", mark_elapsed);
  
  return(sdata);
}

