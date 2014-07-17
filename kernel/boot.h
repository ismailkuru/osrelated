#define SEG_TYPE_X 0x08
#define SEG_TYPE_W 0x02
#define SEG_TYPE_R 0x02

#define NULL_SEG         \
	.word 0, 0;      \
	.byte 0, 0, 0, 0

#define SEG(type, base, limit)                   \
	.word (((limit) >> 12) & 0xFFFF);        \
	.word ((base) & 0xFFFF);                 \
	.byte (((base) >> 16) & 0xFF);           \
	.byte (0x90 | (type));                   \
	.byte (0xC0 | (((limit) >> 28) & 0x0F)); \
	.byte (((base) >> 24) & 0xFF)
