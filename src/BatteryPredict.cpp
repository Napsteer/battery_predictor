#include "../inc/BatteryPredict.h"
#include "../inc/UNumber.h"
#include "../inc/Errors.h"
#include "../inc/Consts.h"

#include <iostream>

using namespace std;
using namespace bp;

bp::BatteryPredict::BatteryPredict()
   : _full_discharge_time(), _full_charge_time(), _critical_discharge_time(),
     _theoretical_time_from_full_charge() {}

unsigned bp::BatteryPredict::GetFullDischargeTime() const
{
   if (_full_discharge_time.nan)
      throw cant_calculate("Nie udało obliczyć się czasu całkowitego rozładowania");

   return _full_discharge_time.number;
}

unsigned bp::BatteryPredict::GetFullChargeTime() const
{
   if (_full_charge_time.nan)
      throw cant_calculate("Nie udało obliczyć się czasu całkowitego naładowania");

   return _full_charge_time.number;
}

unsigned bp::BatteryPredict::GetCriticalDischargeTime() const
{
   if (_critical_discharge_time.nan)
      throw cant_calculate("Nie udało obliczyć się czasu do krytycznego rozładowania");

   return _critical_discharge_time.number;
}

unsigned bp::BatteryPredict::GetTheoriticalTimeFromFullCharge() const
{
   if (_theoretical_time_from_full_charge.nan)
      throw cant_calculate("Nie udało obliczyć się teoretycznego czasu "
         "od pełnego naładowania");

   return _theoretical_time_from_full_charge.number;
}

bool bp::BatteryPredict::IsCharging() const
{
   return _charging;
}

void bp::BatteryPredict::_SetCharging(bool charging)
{
   _charging = charging;

   if (charging)
   {
      _full_charge_time.nan = false;
      _full_discharge_time.nan = true;
      _critical_discharge_time.nan = true;
      _theoretical_time_from_full_charge.nan = true;
   }
   else
   {
      _full_charge_time.nan = true;
      _full_discharge_time.nan = false;
      _critical_discharge_time.nan = false;
      _theoretical_time_from_full_charge.nan = false;
   }
}

void bp::BatteryPredict::_SetFullDischargeTime(unsigned full_discharge_time, bool nan)
{
   _full_discharge_time.number = full_discharge_time;
   _full_discharge_time.nan = nan;
}

void bp::BatteryPredict::_SetFullChargeTime(unsigned full_charge_time, bool nan)
{
   _full_charge_time.number = full_charge_time;
   _full_charge_time.nan = nan;
}

void bp::BatteryPredict::_SetCriticalDischargeTime(unsigned critical_discharge_time, bool nan)
{
   _critical_discharge_time.number = critical_discharge_time;
   _critical_discharge_time.nan = nan;
}

void bp::BatteryPredict::_SetTheoriticalTimeFromFullCharge(
   unsigned theoretical_time_from_full_charge, bool nan)
{
   _theoretical_time_from_full_charge.number = theoretical_time_from_full_charge;
   _theoretical_time_from_full_charge.nan = nan;
}

ostream& bp::operator<<(ostream& os, const BatteryPredict& bp)
{
   if (bp.IsCharging())
   {
      os << "Bateria ładuje się\n";
      os << "Do całkowitego naładowania pozostało " << 
         bp.GetFullChargeTime() << " minut";
   }
   else
   {
      os << "Bateria rozładowuje się\n";
      os << "Do krytycznego (" << CONSTS::BATTERY_CRITICAL_LEVEL << "%) "
         "rozładowania pozostało " << bp.GetCriticalDischargeTime() << " minut\n";
      os << "Do całkowitego rozładowania pozostało " << 
         bp.GetFullDischargeTime() << " minut\n";
      os << "Teoretyczny czas działania od pełnego naładowania " <<
         bp.GetTheoriticalTimeFromFullCharge() << " minut";
   }

   return os;
}
