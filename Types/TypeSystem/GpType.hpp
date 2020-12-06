#pragma once

#include "../../Config/GpConfig.hpp"

#if defined(GP_USE_TYPE_SYSTEM)

#include "../Enums/GpEnums.hpp"
#include "../Strings/GpStringOps.hpp"

namespace GPlatform {

GP_ENUM(GPCORE_API, GpType,
    NOT_SET,
    U_INT_8,
    S_INT_8,
    U_INT_16,
    S_INT_16,
    U_INT_32,
    S_INT_32,
    U_INT_64,
    S_INT_64,
    DOUBLE,
    FLOAT,
    BOOLEAN,
    UUID,       
    STRING,
    BLOB,
    STRUCT,
    STRUCT_SP,
    ENUM,
    ENUM_FLAGS
);

}//GPlatform

#endif//GP_USE_TYPE_SYSTEM
