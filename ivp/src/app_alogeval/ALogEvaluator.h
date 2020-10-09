/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Eng / CSAIL, MIT Cambridge MA     */
/*    FILE: ALogEvaluator.h                                      */
/*    DATE: October 6th, 2020                                    */
/*                                                               */
/* This file is part of MOOS-IvP                                 */
/*                                                               */
/* MOOS-IvP is free software: you can redistribute it and/or     */
/* modify it under the terms of the GNU General Public License   */
/* as published by the Free Software Foundation, either version  */
/* 3 of the License, or (at your option) any later version.      */
/*                                                               */
/* MOOS-IvP is distributed in the hope that it will be useful,   */
/* but WITHOUT ANY WARRANTY; without even the implied warranty   */
/* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See  */
/* the GNU General Public License for more details.              */
/*                                                               */
/* You should have received a copy of the GNU General Public     */
/* License along with MOOS-IvP.  If not, see                     */
/* <http://www.gnu.org/licenses/>.                               */
/*****************************************************************/

#ifndef ALOG_EVALUATOR_HEADER
#define ALOG_EVALUATOR_HEADER

#include <vector>
#include <string>
#include "VCheckSet.h"
#include "LCheckSet.h"

class ALogEvaluator
{
 public:
  ALogEvaluator();
  ~ALogEvaluator() {}

  bool setALogFile(std::string);
  bool setTestFile(std::string);

  void setVerbose()                {m_verbose = true;}
  bool okALogFile() const          {return(m_alog_file != "");}
  bool okTestFile() const          {return(m_test_file != "");}

  void print() const;
  
  bool handle();

 protected: // Internal functions
  bool handleTestFile();
  bool handleALogFile();
  
 protected: // Config vars
  std::string m_alog_file;
  std::string m_test_file;
  bool        m_verbose;

 protected: // State vars
  LCheckSet   m_lcheck_set;
  std::string m_lcheck_status_prev;
  
  VCheckSet   m_vcheck_set;
  std::string m_vcheck_status_prev;
};

#endif
