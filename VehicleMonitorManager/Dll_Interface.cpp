#include "Dll_Interface.h"
#include "CustomVehicleMonitor.h"
#include <windows.h>

namespace TsmPluginFx {
namespace VehicleMonitor {

void* _stdcall CreateVehicleMonitor(LPWSTR aVehicleMonitorName, LPWSTR aUserVehicleDllName)
{
   CustomVehicleMonitor* result = new CustomVehicleMonitor(aVehicleMonitorName, aUserVehicleDllName);

   if (result->UserVehicleDllLoaded()) {
      return result;
   }
   else {
      delete result;
      return nullptr;
   }
}

bool _stdcall RegisterVehicleMonitor(void* aMonitor)
{
   if (aMonitor == nullptr) {
      return false;
   }

   return CustomVehicleMonitor::RegisterVehicleMonitor((CUserVehicleMonitor*)aMonitor);
}

bool _stdcall UnregisterVehicleMonitor(void* aMonitor)
{
   if (aMonitor == nullptr) {
      return false;
   }

   return CustomVehicleMonitor::UnregisterVehicleMonitor((CUserVehicleMonitor*)aMonitor);
}

void _stdcall DeleteVehicleMonitor(void* aMonitor)
{
   if (aMonitor == nullptr) {
      return;
   }

   delete (CUserVehicleMonitor*)aMonitor;
}

}
}