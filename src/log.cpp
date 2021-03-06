/**
 * This file is part of Tales of Symphonia "Fix".
 *
 * Tales of Symphonia "Fix" is free software : you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by The Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Tales of Symphonia "Fix" is distributed in the hope that it will be
 * useful,
 *
 * But WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tales of Symphonia "Fix".
 *
 *   If not, see <http://www.gnu.org/licenses/>.
 *
**/
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include "log.h"

iSK_Logger* dll_log;

iSK_Logger*
TSF_CreateLog (const wchar_t* const wszName)
{
  extern HMODULE hInjectorDLL;

  typedef iSK_Logger* (__stdcall *SK_CreateLog_pfn)(const wchar_t* const wszName);
  static SK_CreateLog_pfn SK_CreateLog = nullptr;

  if (SK_CreateLog == nullptr) {
    SK_CreateLog =
      (SK_CreateLog_pfn)
        GetProcAddress (
          hInjectorDLL,
            "SK_CreateLog"
        );
  }

  iSK_Logger* pLog = SK_CreateLog (wszName);

  if (pLog != nullptr) {
    return pLog;
  } else {
    // ASSERT: WHAT THE HELL?!
    return nullptr;
  }
}