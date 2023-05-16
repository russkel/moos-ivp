#--------------------------------------------------------
# The CMakeLists.txt for:                   lib_behaviors
# Author(s):                                Mike Benjamin
#--------------------------------------------------------

SET(SRC
  BehaviorReport.cpp
  IvPBehavior.cpp
  IvPContactBehavior.cpp
  LifeEventHistory.cpp
  LifeEvent.cpp
  ContactState.cpp
  ContactStateSet.cpp
)

SET(HEADERS
  BehaviorReport.h
  IvPBehavior.h
  IvPContactBehavior.h
  LifeEventHistory.h
  LifeEvent.h
  ContactStateSet.h
)

# Build Library
ADD_LIBRARY(behaviors ${SRC})

