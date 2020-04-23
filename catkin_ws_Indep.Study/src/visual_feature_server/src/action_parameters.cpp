#include <visual_feature_server/action_parameters.h>

ActionParameters::ActionParameters()
{
  upper_tilt = 0;
  pan = 0;
  lower_tilt = 0;
  x = 0;
  y = 0;
  z = 0;
}

bool ActionParameters::operator == (const ActionParameters &p2) const
{
   if(
     this->upper_tilt == p2.upper_tilt &&
     this->pan == p2.pan &&
     this->lower_tilt == p2.lower_tilt &&
     this->x == p2.x &&
     this->y == p2.y &&
     this->z == p2.z
    )
     return true;
   else
     return false;
}

bool ActionParameters::operator < (const ActionParameters &p2) const
{
  if(this->upper_tilt == p2.upper_tilt)
  {
    if(this->pan == p2.pan)
    {
      if(this->lower_tilt == p2.lower_tilt)
      {
        if(this->x == p2.x)
        {

          if(this->y == p2.y)
          {
            return this->z < p2.z;
          }
          else
          {
            return this->y < p2.y;
          }

        }
        else
        {
          return this->x < p2.x;
        }
      }
      else
      {
        return this->lower_tilt < p2.lower_tilt;
      }
    }
    else
    {
      return this->pan < p2.pan;
    }
  }
  else
  {
    return this->upper_tilt < p2.upper_tilt;
  }

}


std::ostream& operator<< (std::ostream& os, const ActionParameters& act)
{
  os << " (" << act.upper_tilt << "," << act.pan << ", " << act.lower_tilt << ")";
  return os;
}
