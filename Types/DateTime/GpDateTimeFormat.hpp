#pragma once

#include "../../Config/GpConfig.hpp"

#if defined(GP_USE_DATE_TIME)

#include "../Enums/GpEnum.hpp"
#include "../Strings/GpStringOps.hpp"

namespace GPlatform {

GP_ENUM(GPCORE_API, GpDateTimeFormat,
    ISO_8601,       //2021-01-11T20:15:31+00:00
    RFC_2822,       //Mon, 11 Jan 2021 20:15:31 +0000
    STD_DATE_TIME   //2021-01-11 20:15:31
);

}//GPlatform

#endif//#if defined(GP_USE_DATE_TIME)
