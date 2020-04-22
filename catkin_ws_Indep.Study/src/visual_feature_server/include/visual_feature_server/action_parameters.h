#ifndef ACTION_PARAMETERS_H_
#define ACTION_PARAMETERS_H_
#include <iostream>

struct ActionParameters
{

  double upper_tilt;
  double pan;
  double lower_tilt;


  double x;
  double y;
  double z;

  ActionParameters();
  bool operator == (const ActionParameters &p2) const;
  bool operator < (const ActionParameters &p2) const;
  friend std::ostream& operator<< (std::ostream& os, const ActionParameters& act);

  template <typename Archive>
  void serialize(Archive& ar,const unsigned int version)
  {
    ar & upper_tilt;
    ar & pan;
    ar & lower_tilt;
    ar & x;
    ar & y;
    ar & z;
  }
};

#endif // ACTION_PARAMETERS_H_
