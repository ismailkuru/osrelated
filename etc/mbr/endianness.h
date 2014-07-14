#ifndef __ENDIANESS_H__
#define __ENDIANESS_H__

#include "types.h"

typedef	uint64_t	be64;
typedef	uint32_t	be32;
typedef	uint16_t	be16;

uint64_t be64_to_cpu(be64);
uint32_t be32_to_cpu(be32);
uint16_t be16_to_cpu(be16);

be64 cpu_to_be64(uint64_t);
be32 cpu_to_be32(uint32_t);
be16 cpu_to_be16(uint16_t);


typedef	uint64_t	le64;
typedef	uint32_t	le32;
typedef	uint16_t	le16;

uint64_t le64_to_cpu(le64);
uint32_t le32_to_cpu(le32);
uint16_t le16_to_cpu(le16);

le64 cpu_to_le64(uint64_t);
le32 cpu_to_le32(uint32_t);
le16 cpu_to_le16(uint16_t);

#endif /*__ENDIANESS_H__*/
