#pragma once

#include "../../Config/GpConfig.hpp"

#if defined(GP_USE_TYPE_SYSTEM)

#include "GpTypeStructBase.hpp"

namespace GPlatform {

class GPCORE_API GpTypeUtils
{
    CLASS_REMOVE_CTRS(GpTypeUtils);

public:

    template<typename T> [[nodiscard]] static
    constexpr std::string_view STypeName (void) noexcept
    {
    #if defined(GP_COMPILER_GCC)
        constexpr std::string_view  pname       = __PRETTY_FUNCTION__;
        constexpr size_t            part_1_id   = pname.find_first_of('=');
        constexpr std::string_view  part_1      = pname.substr(part_1_id+2);
        constexpr size_t            part_2_id   = part_1.find_first_of(';');
        constexpr std::string_view  part_2      = part_1.substr(0, part_2_id);

        return part_2;
    #elif defined(GP_COMPILER_CLANG)
        constexpr std::string_view  pname       = __PRETTY_FUNCTION__;
        constexpr size_t            part_1_id   = pname.find_first_of('=');
        constexpr std::string_view  part_1      = pname.substr(part_1_id+2);
        constexpr size_t            part_2_id   = part_1.find_first_of(']');
        constexpr std::string_view  part_2      = part_1.substr(0, part_2_id);

        return part_2;
    #else
    #   error Unsupported compiller
    #endif
    }

    template<typename StructT, typename ValT> [[nodiscard]] static
    constexpr std::ptrdiff_t SOffsetOf(ValT StructT::*element)
    {
        return std::ptrdiff_t(&(static_cast<StructT*>(nullptr)->*element));
    }

    template<typename T> [[nodiscard]] static
    consteval GpType::EnumT SDetectType (void)
    {
             if constexpr (std::is_same_v<T, u_int_8>) return GpType::U_INT_8;
        else if constexpr (std::is_same_v<T, s_int_8>) return GpType::S_INT_8;
        else if constexpr (std::is_same_v<T, u_int_16>) return GpType::U_INT_16;
        else if constexpr (std::is_same_v<T, s_int_16>) return GpType::S_INT_16;
        else if constexpr (std::is_same_v<T, u_int_32>) return GpType::U_INT_32;
        else if constexpr (std::is_same_v<T, s_int_32>) return GpType::S_INT_32;
        else if constexpr (std::is_same_v<T, u_int_64>) return GpType::U_INT_64;
        else if constexpr (std::is_same_v<T, s_int_64>) return GpType::S_INT_64;
        else if constexpr (std::is_same_v<T, double>) return GpType::DOUBLE;
        else if constexpr (std::is_same_v<T, float>) return GpType::FLOAT;
        else if constexpr (std::is_same_v<T, bool>) return GpType::BOOLEAN;
        else if constexpr (std::is_same_v<T, GpUUID>) return GpType::UUID;
        else if constexpr (std::is_same_v<T, std::string>) return GpType::STRING;
        else if constexpr (std::is_same_v<T, GpBytesArray>) return GpType::BLOB;
        else if constexpr (std::is_base_of_v<GpTypeStructBase, T>) return GpType::STRUCT;
        else if constexpr (GpTypeStructBase::SP::SHasTag_GpSharedPtr<T>()) return GpType::STRUCT_SP;
        else if constexpr (GpUnitUtils::SHasTag_GpUnit<T>()) return SDetectType<typename T::value_type>();
        else if constexpr (GpEnum::SHasTag_GpEnum<T>()) return GpType::ENUM;
        else return GpType::NOT_SET;
    }

    template<typename T> [[nodiscard]] static
    consteval std::tuple<GpType::EnumT, GpType::EnumT, GpTypeContainer::EnumT>  SDetectTypeContainer (void)
    {
        constexpr GpType::EnumT t = SDetectType<T>();

        if constexpr (t != GpType::NOT_SET)
        {
            return {t, GpType::NOT_SET, GpTypeContainer::NO};
        } else
        {
            if constexpr (std::is_same_v<T, GpVector<typename T::value_type>>)
            {
                return {SDetectType<typename T::value_type>(), GpType::NOT_SET, GpTypeContainer::VECTOR};
            } else if constexpr (std::is_same_v<T, GpList<typename T::value_type>>)
            {
                return {SDetectType<typename T::value_type>(), GpType::NOT_SET, GpTypeContainer::LIST};
            } else if constexpr (std::is_same_v<T, GpSet<typename T::value_type>>)
            {
                return {SDetectType<typename T::value_type>(), GpType::NOT_SET, GpTypeContainer::SET};
            } else if constexpr (std::is_same_v<T, GpMap<typename T::key_type, typename T::mapped_type>>)
            {
                return {SDetectType<typename T::mapped_type>(),
                        SDetectType<typename T::key_type>(),
                        GpTypeContainer::MAP};
            } else
            {
                GpThrowCe<std::out_of_range>("Unknown type '"_sv + STypeName<T>() + "'");
            }
        }

        return {GpType::NOT_SET, GpType::NOT_SET, GpTypeContainer::NO};
    }

    template<typename T> [[nodiscard]] static
    GpUUID  SDetectStructTypeUID (void)
    {
        if constexpr (std::is_base_of_v<GpTypeStructBase, T>)
        {
            return T::STypeStructInfo().UID();
        } else if constexpr (GpTypeStructBase::SP::SHasTag_GpSharedPtr<T>())
        {
            return T::value_type::STypeStructUID();
        } else
        {
            return GpUUID();
        }
    }
};

}//namespace GPlatform

#endif//GP_USE_TYPE_SYSTEM
