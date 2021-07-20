/*****************************************************************/
/*    NAME: Michael R. Benjamin                                  */
/*    ORGN: Dept of Mechanical Eng / CSAIL, MIT Cambridge MA     */
/*    FILE: CollObDetect_Info.cpp                                */
/*    DATE: September 2nd, 2019                                  */
/*****************************************************************/

#include <cstdlib>
#include <iostream>
#include "CollObDetect_Info.h"
#include "ColorParse.h"
#include "ReleaseInfo.h"

using namespace std;

//----------------------------------------------------------------
// Procedure: showSynopsis

void showSynopsis()
{
  blk("SYNOPSIS:                                                       ");
  blk("------------------------------------                            ");
  blk("  The uFldCollObDetect application is used for                  ");
  blk("                                                                ");
  blk("                                                                ");
  blk("                                                                ");
  blk("                                                                ");
}

//----------------------------------------------------------------
// Procedure: showHelpAndExit

void showHelpAndExit()
{
  blk("                                                                ");
  blu("=============================================================== ");
  blu("Usage: uFldCollObDetect file.moos [OPTIONS]                     ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("Options:                                                        ");
  mag("  --alias","=<ProcessName>                                      ");
  blk("      Launch uFldCollObDetect with the given process name       ");
  blk("      rather than uFldCollObDetect.                             ");
  mag("  --example, -e                                                 ");
  blk("      Display example MOOS configuration block.                 ");
  mag("  --help, -h                                                    ");
  blk("      Display this help message.                                ");
  mag("  --interface, -i                                               ");
  blk("      Display MOOS publications and subscriptions.              ");
  mag("  --version,-v                                                  ");
  blk("      Display the release version of uFldCollObDetect.          ");
  blk("                                                                ");
  blk("Note: If argv[2] does not otherwise match a known option,       ");
  blk("      then it will be interpreted as a run alias. This is       ");
  blk("      to support pAntler launching conventions.                 ");
  blk("                                                                ");
  exit(0);
}

//----------------------------------------------------------------
// Procedure: showExampleConfigAndExit

void showExampleConfigAndExit()
{
  blu("=============================================================== ");
  blu("uFldCollObDetect Example MOOS Configuration                     ");
  blu("=============================================================== ");
  blk("                                                                ");
  blk("ProcessConfig = uFldCollObDetect                                ");
  blk("{                                                               ");
  blk("  AppTick   = 4                                                 ");
  blk("  CommsTick = 4                                                 ");
  blk("                                                                ");
  blk("  collision_dist   = 10                                         ");
  blk("  near_miss_dist   = 15                                         ");
  blk("  encounter_dist   = 20                                         ");
  blk("                                                                ");
  blk("  collision_flag   = OB_ENCOUNTER = $DIST                       ");
  blk("  near_miss_flag   = OB_NEAR_MISS = $DIST                       ");
  blk("  encounter_flag   = OB_COLLISION = $DIST                       ");
  blk("}                                                               ");
  blk("                                                                ");
  exit(0);
}


//----------------------------------------------------------------
// Procedure: showInterfaceAndExit

void showInterfaceAndExit()
{
  blk("                                                                ");
  blu("=============================================================== ");
  blu("uFldCollObDetect INTERFACE                                      ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("SUBSCRIPTIONS:                                                  ");
  blk("------------------------------------                            ");
  blk("  NODE_MESSAGE = src_node=alpha,dest_node=bravo,var_name=FOO,   ");
  blk("                 string_val=BAR                                 ");
  blk("  APPCAST_REQ  = node=all,app=uFldCollObDetect,duration=3.0     ");
  blk("                 key=pMarineViewer:alphaapp,thresh=run_warning  ");
  blk("                                                                ");
  blk("  KNOWN_OBSTACLE = pts={59,-101:64,-105:64,-112:59,-116:53},    ");
  blk("                   label=ob_3,duration=451.74                   ");
  blk("                                                                ");
  blk("  KNOWN_OBSTACLE_CLEAR = ob_3     (or \"all\")                  ");
  
  blk("  NODE_REPORT = NAME=alpha,TYPE=UUV,TIME=1252348077.59,         ");
  blk("                COLOR=red,X=51.71,Y=-35.50, LAT=43.824981,      ");
  blk("                LON=-70.329755,SPD=2.0,HDG=118.8,               ");
  blk("                YAW=118.8,DEPTH=4.6,LENGTH=3.8,                 ");
  blk("                MODE=MODE@ACTIVE:LOITERING                      ");
  blk("                                                                ");
  blk("PUBLICATIONS:                                                   ");
  blk("------------------------------------                            ");
  blk("  APPCAST                                                       ");
  blk("  <flags>                                                       ");
  blk("                                                                ");
  exit(0);
}

//----------------------------------------------------------------
// Procedure: showReleaseInfoAndExit

void showReleaseInfoAndExit()
{
  showReleaseInfo("uFldCollObDetect", "gpl");
  exit(0);
}

