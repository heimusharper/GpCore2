#include "GpEnumFlags.hpp"
#include "../Strings/GpStringOps.hpp"

#if defined(GP_USE_ENUMS)

namespace GPlatform {

GpVector<std::string>   GpEnumFlags::ToStringArray (void) const
{
    GpVector<std::string_view>  v_sv = ToStringViewArray();
    GpVector<std::string>       res;
    res.reserve(v_sv.size());

    for (std::string_view s: v_sv)
    {
        res.emplace_back(std::string(s));
    }

    return res;
}

GpVector<std::string_view>  GpEnumFlags::ToStringViewArray (void) const
{
    GpVector<std::string_view> res;

    value_type value    = iValue;
    value_type id       = 0;

    while (value > 0)
    {
        if (value & 0b1)
        {
            res.emplace_back(ToStringFlag(id));
        }

        id++;
        value >>= 1;
    }

    return res;
}

void    GpEnumFlags::FromStringArray (const GpVector<std::string>& aArray)
{
    Clear();

    for (const std::string& s: aArray)
    {
        Set(s);
    }
}

void    GpEnumFlags::FromStringViewArray (const GpVector<std::string_view>& aArray)
{
    Clear();

    for (const std::string_view s: aArray)
    {
        Set(s);
    }
}

std::string GpEnumFlags::Echo (void) const
{
    GpVector<std::string_view> v = ToStringViewArray();
    return StrOps::SJoin<std::string_view>(v, ","_sv);
}

}//namespace GPlatform

#endif//#if defined(GP_USE_ENUMS)
