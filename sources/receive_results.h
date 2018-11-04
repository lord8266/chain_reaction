#ifndef receive_results_header
#define receive_results_header 1

#include "main.h"

class receive_results {
public:
  receive_results(box* to,box* from,player*);
  box* to =nullptr; // to where ball is coming
  box* from =nullptr;  // from where ball has come
  player* owner = nullptr;
};

#endif