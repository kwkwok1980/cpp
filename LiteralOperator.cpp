#include <iostream>

namespace binary
{
    using byte8 = unsigned char;
    using byte16 = unsigned short;
    using byte32 = unsigned int;

    namespace binary_literal
    {
        byte8 operator "" _b8(const char* p)
        {
            std::cout << p << std::endl;
            return 1;
        }

        byte16 operator "" _b16(const char* p)
        {
            std::cout << p << std::endl;
            return 1;
        }

        byte32 operator "" _b32(const char* p)
        {
            std::cout << p << std::endl;
            return 1;
        }
    }
}

namespace binary2
{
    using byte8 = unsigned char;
    using byte16 = unsigned short;
    using byte32 = unsigned int;

    namespace binary_literal_impl
    {
        template<typename T, char... bits>
        struct binary_struct;

        template<typename T, char... bits>
        struct binary_struct<T, '0', bits...>
        {
            static constexpr T value = binary_struct<T, bits...>::value;
        };

        template<typename T, char... bits>
        struct binary_struct<T, '1', bits...>
        {
            static constexpr T value = (static_cast<T>(1) << sizeof...(bits)) | binary_struct<T, bits...>::value;
        };

        template<typename T>
        struct binary_struct<T>
        {
            static constexpr T value = 0;
        };
    }

    namespace binary_literal
    {

        template<char... bits>
        constexpr byte8 operator "" _b8()
        {
            static_assert(sizeof...(bits) == 8, "size");
            return binary_literal_impl::binary_struct<byte8, bits...>::value;
        }

        template<char... bits>
        constexpr byte16 operator "" _b16()
        {
            static_assert(sizeof...(bits) == 16, "size");
            return binary_literal_impl::binary_struct<byte16, bits...>::value;
        }

        template<char... bits>
        constexpr byte32 operator "" _b32()
        {
            static_assert(sizeof...(bits) == 32, "size");
            return binary_literal_impl::binary_struct<byte32, bits...>::value;
        }
    }

}

namespace binary3
{
    using byte8 = unsigned char;
    using byte16 = unsigned short;
    using byte32 = unsigned int;

    namespace binary_literal_impl
    {
        template<typename T, char... bits>
        struct binary_struct;

        template<typename T, char bit, char... bits>
        struct binary_struct<T, bit, bits...>
        {
            static constexpr T eval_value()
            {
                if constexpr (sizeof...(bits) == 0)
                {
                    return static_cast<T>(bit - '0');
                }
                else
                {
                    if constexpr (bit == '0')
                    {
                        return binary_struct<T, bits...>::value;
                    }
                    else
                    {
                        return (static_cast<T>(1) << sizeof...(bits)) | binary_struct<T, bits...>::value;
                    }
                }
            }

            static constexpr T value = eval_value();
        };

    }

    namespace binary_literal
    {

        template<char... bits>
        constexpr byte8 operator "" _b8()
        {
            static_assert(sizeof...(bits) == 8, "size");
            return binary_literal_impl::binary_struct<byte8, bits...>::value;
        }

        template<char... bits>
        constexpr byte16 operator "" _b16()
        {
            static_assert(sizeof...(bits) == 16, "size");
            return binary_literal_impl::binary_struct<byte16, bits...>::value;
        }

        template<char... bits>
        constexpr byte32 operator "" _b32()
        {
            static_assert(sizeof...(bits) == 32, "size");
            return binary_literal_impl::binary_struct<byte32, bits...>::value;
        }
    }

}


using namespace binary3;
using namespace binary3::binary_literal;

int main()
{
    auto v1 = 00000101_b8;
    std::cout << static_cast<int>(v1) << std::endl;

    //auto v2 = 456_b8;
    //std::cout << static_cast<int>(v2) << std::endl;
    return 0;
}
