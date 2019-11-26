#pragma once

#include <ctime>
#include <string>
#include <boost/numeric/ublas/vector.hpp>
#include <QString>
#include <QTextStream>
#include <QFile>
#include "ADNAuxiliary.hpp"
#include "ADNConfig.hpp"


namespace ublas = boost::numeric::ublas;

class ADNLogger
{
public:
  // singleton pattern
  ~ADNLogger();
  // deleted functions should be public for better error message handling
  ADNLogger(ADNLogger const& l) = delete;
  void operator=(ADNLogger const& l) = delete;

  static ADNLogger& GetLogger();
  
  void SetLogPath(std::string path);

  // logging functions

  // debug logging
  void ClearLog();
  void LogDebug(float value);
  void LogDebug(int value);
  void LogDebug(std::string value);
  void LogDebug(QString value);
  void LogDebug(ublas::vector<double> v);
  void LogDebug(std::string name, ublas::vector<double> v);
  void LogDebug(ublas::matrix<double> m);
  // time logs debug
  time_t LogDebugPassedSeconds(time_t time1, std::string text);
  clock_t LogDebugPassedMilliseconds(clock_t time1, std::string text);
  void LogDebugDateTime();

  // normal logging
  void Log(float value);
  void Log(int value);
  void Log(std::string value);
  void Log(QString value);
  void Log(ublas::vector<double> v);
  void Log(std::string name, ublas::vector<double> v);
  void Log(ublas::matrix<double> m);
  void Log(quintptr ptr);
  void Log(SBPosition3 pos);

  // time logs
  time_t LogPassedSeconds(time_t time1, std::string text);
  clock_t LogPassedMilliseconds(clock_t time1, std::string text);
  void LogDateTime();

  //void logPosition(std::string name, SBPosition3 pos);
  //void logVector(std::string name, SBPicometerPerSecond3 pos);
  //void logVector(std::string name, SBRadianPerSecond3 pos);
  //void logVector(std::string name, SBVector3 pos);

private:
  ADNLogger();

  std::string logPath_ = SAMSON::getUserDataPath() + "/adenita.log";
  QFile file_;
};

