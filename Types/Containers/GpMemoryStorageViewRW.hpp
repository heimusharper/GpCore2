#pragma once

#include "../../Config/GpConfig.hpp"

#if defined(GP_USE_CONTAINERS)

#include "../Containers/GpContainersT.hpp"
#include "../Containers/GpRawPtrByte.hpp"
#include "../Units/Other/size_byte_t.hpp"
#include "../Classes/GpClassesDefines.hpp"

namespace GPlatform {

class GPCORE_API GpMemoryStorageViewRW
{
public:
    CLASS_REMOVE_CTRS_EXCEPT_DEFAULT(GpMemoryStorageViewRW);
    CLASS_DECLARE_DEFAULTS(GpMemoryStorageViewRW);

protected:
                                GpMemoryStorageViewRW   (void) noexcept = default;
public:
    virtual                     ~GpMemoryStorageViewRW  (void) noexcept = default;

    virtual GpRawPtrByteR       R                       (void) const = 0;
    virtual GpRawPtrByteRW      RW                      (void) = 0;
    virtual size_byte_t         Size                    (void) const noexcept = 0;
    virtual bool                IsEmpty                 (void) const noexcept = 0;
};

}//GPlatform

#endif//#if defined(GP_USE_CONTAINERS)
