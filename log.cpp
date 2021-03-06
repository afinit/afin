// Contains Log class

#include "log.hpp"
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

Log* Log::p_Inst = NULL;

Log::Log(){}

time_t Log::timer;

Log* Log::Inst(){
  if( !p_Inst ){
    p_Inst = new Log;
    // initialize timer
    time( &timer );
  }

  return p_Inst;
}

// initalize logfile
void Log::open_log( string logfile ){
  log_fs.open( logfile, fstream::out | fstream::trunc );

  // ensure logfile has opened properly
  if( log_fs.fail() ){
    fprintf( stderr, "Error: Could not open logfile '%s'. Check permissions for logfile location", logfile.c_str() );
    exit(1);
  }
}

// closes logfile
void Log::close_log(){
  log_fs << get_time() << "\tProcess terminated" << endl;
  log_fs.close();
}

// prints notes to file as the program progresses
void Log::log_it( string note ){
  if( log_output ){
    log_fs << get_time() << "\t" << note << endl;
  }
  if( screen_output ){
    cout << get_time() << "\t" << note << endl;
  }
}

// return a string of the current time in the program
string Log::get_time(){
  string curr_time = "";
  char buffer[100];

  int t_now = difftime( time(0), timer );   // get time now
  
  int t_hour = t_now / 3600;
  t_now = t_now % 3600;

  int t_min = t_now / 60;
  t_now = t_now % 60;

  // format time in xxx:xx:xx
  sprintf( buffer, "%d:%.2d:%.2d", t_hour, t_min, t_now);
  curr_time = buffer;

  return curr_time;
}
