#include "endianness.h"

inline static uint16_t u16_swap_bytes(uint16_t value)
{
	return (value & 0x00FFu) << 8 | (value & 0xFF00u) >> 8;
}

inline static uint32_t u32_swap_bytes(uint32_t value)
{
	return (uint32_t)u16_swap_bytes(value & 0x0000FFFFu) << 16 |
		(uint32_t)u16_swap_bytes((value & 0xFFFF0000u) >> 16);
}

inline static uint64_t u64_swap_bytes(uint64_t value)
{
	return (uint64_t)u32_swap_bytes(value & 0x00000000FFFFFFFFllu) << 32 |
		(uint64_t)u32_swap_bytes((value & 0xFFFFFFFF00000000llu) >> 32);
}

uint16_t be16_to_cpu(be16 value)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	return u16_swap_bytes(value);
#else
	return value;
#endif
}

uint32_t be32_to_cpu(be32 value)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	return u32_swap_bytes(value);
#else
	return value;
#endif
}

uint64_t be64_to_cpu(be64 value)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	return u64_swap_bytes(value);
#else
	return value;
#endif
}

be16 cpu_to_be16(uint16_t value)
{
	return be16_to_cpu(value);
}

be32 cpu_to_be32(uint32_t value)
{
	return be32_to_cpu(value);
}

be64 cpu_to_be64(uint64_t value)
{
	return be64_to_cpu(value);
}


uint16_t le16_to_cpu(le16 value)
{
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return u16_swap_bytes(value);
#else
	return value;
#endif
}

uint32_t le32_to_cpu(le32 value)
{
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return u32_swap_bytes(value);
#else
	return value;
#endif
}

uint64_t le64_to_cpu(le64 value)
{
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return u64_swap_bytes(value);
#else
	return value;
#endif
}

le16 cpu_to_le16(uint16_t value)
{
	return le16_to_cpu(value);
}

le32 cpu_to_le32(uint32_t value)
{
	return le32_to_cpu(value);
}

le64 cpu_to_le64(uint64_t value)
{
	return le64_to_cpu(value);
}
