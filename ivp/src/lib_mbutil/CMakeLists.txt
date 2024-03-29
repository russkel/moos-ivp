#--------------------------------------------------------
# The CMakeLists.txt for:                      lib_mbutil
# Author(s):                                Mike Benjamin
#--------------------------------------------------------

SET(SRC
  ColorParse.cpp
  ColorPack.cpp
  FColorMap.cpp
  HintHolder.cpp
  fileutil.cpp
  FileBuffer.cpp
  MBTimer.cpp
  MBUtils.cpp
  HashUtils.cpp
  MacroUtils.cpp
  TermUtils.cpp
  StringTree.cpp
  StringNode.cpp
  VarDataPair.cpp
  VarDataPairUtils.cpp
  AckMessage.cpp
  NodeMessage.cpp
  NodeMessageUtils.cpp
  Odometer.cpp
  Figlog.cpp
  TStamp.cpp
  ReleaseInfo.cpp
  stringutil.cpp
  MailFlagSet.cpp
  LatLonFormatUtils.cpp
  OpenURL.cpp
  BundleOut.cpp
  )

SET(HEADERS
  ColorPack.h
  ColorParse.h
  FColorMap.h
  HintHolder.h
  fileutil.h
  FileBuffer.h
  MBTimer.h
  MBUtils.h
  HashUtils.h
  MacroUtils.h
  StringNode.h
  StringTree.h
  TermUtils.h
  VarDataPair.h
  VarDataPairUtils.h
  NodeMessage.h
  NodeMessageUtils.h
  Odometer.h
  TStamp.h
  ReleaseInfo.h
  ScopeEntry.h
  stringutil.h
  MailFlagSet.h
  LatLonFormatUtils.h
  OpenURL.h
  BundleOut.h
)

# Build Library
ADD_LIBRARY(mbutil ${SRC})

