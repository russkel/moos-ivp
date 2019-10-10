/*****************************************************************/
/*    NAME: Michael R. Benjamin                                  */
/*    ORGN: Dept of Mechanical Eng / CSAIL, MIT Cambridge MA     */
/*    FILE: ObstacleSim.cpp                                      */
/*    DATE: October 19th, 2017                                   */
/*****************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "GeomUtils.h"
#include "ACTable.h"
#include "ObstacleSim.h"
#include "FileBuffer.h"
#include "ColorParse.h"
#include "XYFormatUtilsPoly.h"
#include "NodeRecordUtils.h"

using namespace std;

//---------------------------------------------------------
// Constructor

ObstacleSim::ObstacleSim()
{
  // Init Config variables
  m_min_range = 0;      
  m_min_poly_size = 0;
  m_max_poly_size = 0;

  m_poly_fill_color  = "white";
  m_poly_edge_color  = "gray50";
  m_poly_vert_color  = "gray50";
  m_poly_label_color = "invisible";

  m_poly_transparency = 0.15;
  m_poly_edge_size   = 1;
  m_poly_vert_size   = 1;

  m_post_points = false;
  m_rate_points = 5;

  // Init State variables
  m_viewables_queried = true;
  m_obstacles_queried = true;

  m_viewables_posted = 0;
  m_obstacles_posted = 0;
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool ObstacleSim::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    string sval  = msg.GetString(); 

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif
    
    if(key=="PMV_CONNECT")
      m_viewables_queried = true;
    else if(key=="VEHICLE_CONNECT")
      m_obstacles_queried = true;
    else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
      reportRunWarning("Unhandled Mail: " + key);
  }
	
  return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool ObstacleSim::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()

bool ObstacleSim::Iterate()
{
  AppCastingMOOSApp::Iterate();

  if(m_viewables_queried) {
    postViewableObstacles();
    m_viewables_queried = false;
  }

  if(m_post_points)
    postPoints();

  if(m_obstacles_queried) {
    postKnownObstacles();
    m_obstacles_queried = false;
  }

  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()

bool ObstacleSim::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  STRING_LIST::iterator p;
  for(p=sParams.begin(); p!=sParams.end(); p++) {
    string orig  = *p;
    string line  = *p;
    string param = tolower(biteStringX(line, '='));
    string value = line;

    bool handled = false;
    if(param == "obstacle_file") 
      handled = processObstacleFile(value);
    else if((param == "poly_vert_color") && isColor(value))
      handled = setColorOnString(m_poly_vert_color, value);
    else if((param == "poly_fill_color") && isColor(value))
      handled = setColorOnString(m_poly_fill_color, value);
    else if((param == "poly_edge_color") && isColor(value))
      handled = setColorOnString(m_poly_edge_color, value);
    else if((param == "poly_label_color") && isColor(value))
      handled = setColorOnString(m_poly_label_color, value);
    else if(param == "post_points")
      handled = setBooleanOnString(m_post_points, value);
    else if(param == "rate_points")
      handled = setNonNegDoubleOnString(m_rate_points, value);
    else if(param == "rate_pointsx")
      handled = setNonNegDoubleOnString(m_rate_points, value);

    if(!handled)
      reportUnhandledConfigWarning(orig);
  }
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void ObstacleSim::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("PMV_CONNECT", 0);
  Register("VEHICLE_CONNECT", 0);
}

//------------------------------------------------------------
// Procedure: processObstacleFile

bool ObstacleSim::processObstacleFile(string filename)
{
  vector<string> lines = fileBuffer(filename);
  unsigned int i, vsize = lines.size();
  if(vsize == 0) {
    reportConfigWarning("Error reading: " + filename);
    return(false);
  }

  for(i=0; i<vsize; i++) {
    string line = stripBlankEnds(lines[i]);
    if((line == "") || strBegins(line, "//"))
      continue;
    
    string left  = biteStringX(line, '=');
    string right = line;
    if(left == "region") {
      XYPolygon region = string2Poly(right);
      if(!region.is_convex()) {
	reportConfigWarning("Poorly specified region: " + right);
	return(false);
      }
      m_poly_region = region;
    }
    else if(left == "min_range") {
      if(isNumber(right)) 
	m_min_range = atof(right.c_str());
      else
	reportConfigWarning("Poorly specified min_range: " + right);
    }
    else if(left == "min_size") {
      if(isNumber(right)) 
	m_min_poly_size = atof(right.c_str());
      else
	reportConfigWarning("Poorly specified min_size: " + right);
    }
    else if(left == "max_size") {
      if(isNumber(right)) 
	m_max_poly_size = atof(right.c_str());
      else
	reportConfigWarning("Poorly specified min_size: " + right);
    }
    else if(left == "poly") {
      XYPolygon poly = string2Poly(right);
      if(!poly.is_convex()) {
	reportConfigWarning("Poorly specified obstacle: " + right);
	return(false);
      }
      poly.set_color("edge", m_poly_edge_color);
      poly.set_color("vertex", m_poly_vert_color);
      poly.set_color("fill", m_poly_fill_color);
      poly.set_color("label", m_poly_label_color);
      poly.set_vertex_size(m_poly_vert_size);
      poly.set_edge_size(m_poly_edge_size);
      poly.set_transparency(m_poly_transparency);
      m_obstacles.push_back(poly);
    }
  }
  return(true);
}

//------------------------------------------------------------
// Procedure: postViewableObstacles()

void ObstacleSim::postViewableObstacles()
{
  if(!m_post_points) {
    for(unsigned int i=0; i<m_obstacles.size(); i++) {
      string spec = m_obstacles[i].get_spec();
      Notify("VIEW_POLYGON", spec);
    }
  }

  if(m_poly_region.is_convex())
    Notify("VIEW_POLYGON", m_poly_region.get_spec());
  m_viewables_posted++;

}

//------------------------------------------------------------
// Procedure: postKnownObstacles()
//     Notes: o The KNOWN_OBSTACLE is intended for the benefit of
//              other shoreside apps, e.g., uFldCollObDetect so it
//              has access to ground truth. Thus KNOWN_OBSTACLE is
//              not intented to be shared out to the vehicles
//            o The GIVEN_OBSTACLE is intended for sharing to the
//              vehicles, only if this sim is not in "post_points"
//              mode. In post_points mode, this sim is sharing
//              simulated sensor data, not actual obstacle info

void ObstacleSim::postKnownObstacles()
{
  for(unsigned int i=0; i<m_obstacles.size(); i++) {
    string spec = m_obstacles[i].get_spec();
    // KNOWN_OBSTACLE is ground truth for other shoreside apps
    Notify("KNOWN_OBSTACLE", spec);
    // GIVEN_OBSTACLE is only posted and shared with vehicles
    // if this sim is not generated simulated post_points.
    if(!m_post_points)
      Notify("GIVEN_OBSTACLE", spec);
  }
  m_obstacles_posted++;
}

//------------------------------------------------------------
// Procedure: postPoints()
//      Note: Points are published as:
//            TRACKED_FEATURE = x=5,y=8,label=key,size=4,color=1

void ObstacleSim::postPoints()
{
  for(unsigned int i=0; i<m_obstacles.size(); i++) {
    for(unsigned int j=0; j<m_rate_points; j++) {
      double x, y;
      bool ok = randPointInPoly(m_obstacles[i], x, y);
      if(ok) {
	string key = m_obstacles[i].get_label();
	string msg = "x=" + doubleToStringX(x,2);
	msg += ",y=" + doubleToStringX(y,2);
	msg += ",label=" + key + ",color=1,size=2";
	Notify("TRACKED_FEATURE", msg);
	reportEvent("TRACKED_FEATURE="+msg);
      }
    }
  }
}

//------------------------------------------------------------
// Procedure: buildReport()

bool ObstacleSim::buildReport() 
{
  m_msgs << "============================================" << endl;
  m_msgs << "Configuration:                              " << endl;
  m_msgs << "  Obstacles: " << uintToString(m_obstacles.size()) << endl;
  m_msgs << "  MinRange:  " << doubleToStringX(m_min_range)     << endl;
  m_msgs << "  MinSize:   " << doubleToStringX(m_min_poly_size) << endl;
  m_msgs << "  MaxSize:   " << doubleToStringX(m_max_poly_size) << endl << endl;

  m_msgs << "  Post Points:   " << boolToString(m_post_points) << endl;
  m_msgs << "  Rate Points:   " << doubleToStringX(m_rate_points) << endl;

  m_msgs << "State:                                      " << endl;
  m_msgs << "  Viewables Posted: " << uintToString(m_viewables_posted) << endl;
  m_msgs << "  Obstacles Posted: " << uintToString(m_obstacles_posted) << endl;

  return(true);
}

