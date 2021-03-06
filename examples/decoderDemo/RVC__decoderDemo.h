#include "actors-rts.h"
#include "natives.h"
#ifndef CAL_TOP_NETWORK_RVC__DECODERDEMO
#define CAL_TOP_NETWORK_RVC__DECODERDEMO
extern int32_t decoder__texture_V__SAMPLE_SZ;
extern int32_t decoder__motion_U__PIX_SZ;
extern int32_t decoder__motion_V__PIX_SZ;
extern int32_t decoder__parser__BTYPE_SZ;
extern int32_t decoder__FOURMV;
extern int32_t decoder__texture_Y__DCRecontruction__INTER;
extern int32_t decoder__texture_V__DCRecontruction__QUANT_MASK;
extern int32_t decoder__texture_V__DCRecontruction__BTYPE_SZ;
extern int32_t decoder__texture_Y__BTYPE_SZ;
extern int32_t decoder__texture_V__DCRecontruction__MAXW_IN_MB;
extern int32_t decoder__motion_V__ADDR_SZ;
extern int32_t decoder__texture_U__DCRecontruction__QUANT_SZ;
extern int32_t decoder__texture_V__idct2d__PIX_SZ;
extern int32_t decoder__texture_Y__SAMPLE_SZ;
extern int32_t decoder__FCODE_SHIFT;
extern int32_t decoder__motion_V__FLAG_SZ;
extern int32_t decoder__texture_V__DCRecontruction__SAMPLE_SZ;
extern int32_t decoder__texture_V__DCRecontruction__INTRA;
extern int32_t decoder__texture_Y__ACCODED;
extern int32_t decoder__texture_Y__idct2d__SIN_SZ;
extern int32_t decoder__motion_Y__PIX_SZ;
extern int32_t decoder__motion_Y__INTER;
extern int32_t decoder__motion_Y__MOTION;
extern int32_t decoder__texture_Y__DCRecontruction__MAXW_IN_MB;
extern int32_t decoder__ROUND_TYPE;
extern int32_t decoder__motion_V__NEWVOP;
extern int32_t decoder__parser__ACCODED;
extern int32_t decoder__motion_V__ROUND_TYPE;
extern int32_t decoder__texture_Y__QUANT_MASK;
extern int32_t decoder__motion_U__INTER;
static inline int32_t* Integers(int32_t start, int32_t stop);
extern int32_t decoder__texture_U__DCRecontruction__QUANT_MASK;
extern int32_t decoder__parser__SAMPLE_COUNT_SZ;
extern int32_t decoder__texture_U__SAMPLE_SZ;
extern int32_t decoder__FCODE_MASK;
extern int32_t decoder__BTYPE_SZ;
extern int32_t decoder__texture_V__ACCODED;
extern int32_t decoder__motion_Y__MB_COORD_SZ;
extern int32_t decoder__motion_U__INTRA;
extern int32_t decoder__texture_U__idct2d__PIX_SZ;
extern int32_t decoder__motion_Y__MAXH_IN_MB;
extern int32_t decoder__texture_V__idct2d__OUT_SZ;
extern int32_t decoder__texture_V__DCRecontruction__INTER;
extern int32_t decoder__texture_U__DCRecontruction__MB_COORD_SZ;
extern int32_t decoder__texture_V__QUANT_SZ;
extern int32_t decoder__texture_Y__idct2d__PIX_SZ;
extern int32_t decoder__motion_Y__ACCODED;
extern int32_t decoder__motion_U__MV_SZ;
extern int32_t decoder__texture_Y__INTER;
extern int32_t decoder__texture_U__DCRecontruction__INTER;
extern int32_t decoder__texture_Y__ACPRED;
extern int32_t decoder__texture_V__DCRecontruction__ACCODED;
extern int32_t decoder__texture_V__MB_COORD_SZ;
extern int32_t decoder__texture_Y__DCRecontruction__ACCODED;
extern int32_t decoder__texture_V__QUANT_MASK;
extern int32_t decoder__motion_U__MOTION;
extern int32_t decoder__parser__SAMPLE_SZ;
extern int32_t decoder__motion_V__MB_COORD_SZ;
extern int32_t decoder__motion_U__FLAG_SZ;
extern int32_t decoder__texture_Y__DCRecontruction__BTYPE_SZ;
extern int32_t decoder__motion_U__LAYOUT;
extern int32_t decoder__texture_U__DCRecontruction__MAXW_IN_MB;
extern int32_t decoder__texture_U__BTYPE_SZ;
extern int32_t decoder__motion_U__MAXW_IN_MB;
extern int32_t decoder__texture_Y__QUANT_SZ;
extern int32_t decoder__motion_V__BTYPE_SZ;
extern int32_t decoder__texture_U__QUANT_SZ;
extern int32_t decoder__texture_Y__DCRecontruction__DCVAL;
extern int32_t decoder__texture_V__INTER;
extern int32_t decoder__motion_Y__LAYOUT;
extern int32_t decoder__texture_V__idct2d__SIN_SZ;
extern int32_t decoder__motion_U__ROUND_TYPE;
extern int32_t decoder__texture_Y__DCRecontruction__INTRA;
extern int32_t decoder__texture_U__INTRA;
extern int32_t decoder__motion_Y__SEARCHWIN_IN_MB;
extern int32_t decoder__texture_V__DCRecontruction__DCVAL;
extern int32_t decoder__SAMPLE_SZ;
extern int32_t decoder__parser__MAXW_IN_MB;
static inline int32_t lshift(int32_t x, int32_t y);
extern int32_t decoder__motion_V__INTER;
extern int32_t decoder__INTER;
extern int32_t decoder__texture_U__QUANT_MASK;
extern int32_t decoder__texture_U__DCRecontruction__INTRA;
static inline int32_t bitnot(int32_t x);
extern int32_t decoder__texture_U__idct2d__SIN_SZ;
extern int32_t decoder__texture_U__DCRecontruction__ACCODED;
extern int32_t decoder__ACPRED;
extern int32_t decoder__texture_V__DCRecontruction__MB_COORD_SZ;
extern int32_t decoder__texture_Y__DCRecontruction__ACPRED;
extern int32_t decoder__MOTION;
extern int32_t decoder__parser__INTRA;
extern int32_t decoder__motion_V__BUF_SZ;
extern int32_t decoder__MB_COORD_SZ;
extern int32_t decoder__texture_V__DCRecontruction__ACPRED;
extern int32_t decoder__MV_SZ;
extern int32_t decoder__parser__FOURMV;
extern int32_t decoder__motion_Y__BUF_SZ;
extern int32_t decoder__MAXW_IN_MB;
extern int32_t decoder__texture_Y__DCRecontruction__NEWVOP;
extern int32_t decoder__INTRA;
extern int32_t decoder__NEWVOP;
extern int32_t decoder__texture_V__NEWVOP;
extern int32_t decoder__texture_Y__DCRecontruction__QUANT_SZ;
extern int32_t decoder__motion_U__NEWVOP;
extern int32_t decoder__texture_Y__INTRA;
extern int32_t decoder__texture_U__DCRecontruction__DCVAL;
extern int32_t decoder__motion_V__MAXW_IN_MB;
extern int32_t decoder__texture_U__ACCODED;
extern int32_t decoder__motion_U__BUF_SZ;
extern int32_t decoder__texture_V__DCRecontruction__NEWVOP;
extern int32_t decoder__texture_Y__NEWVOP;
extern int32_t decoder__motion_Y__MV_SZ;
extern int32_t decoder__texture_U__DCRecontruction__BTYPE_SZ;
extern int32_t decoder__texture_U__ACPRED;
extern int32_t decoder__texture_U__INTER;
extern int32_t decoder__MAXH_IN_MB;
static inline int32_t bitand(int32_t x, int32_t y);
extern int32_t decoder__motion_U__MB_COORD_SZ;
extern int32_t decoder__texture_U__MB_COORD_SZ;
extern int32_t decoder__motion_V__SEARCHWIN_IN_MB;
extern int32_t decoder__texture_Y__DCRecontruction__MB_COORD_SZ;
extern int32_t decoder__motion_U__MAXH_IN_MB;
extern int32_t decoder__parser__MV_SZ;
extern int32_t decoder__PIX_SZ;
extern int32_t decoder__motion_U__SEARCHWIN_IN_MB;
extern int32_t decoder__parser__ACPRED;
extern int32_t decoder__texture_U__idct2d__OUT_SZ;
extern int32_t decoder__motion_V__MOTION;
extern int32_t decoder__motion_V__ACCODED;
extern int32_t decoder__parser__NEWVOP;
extern int32_t decoder__motion_U__ACCODED;
extern int32_t decoder__motion_Y__INTRA;
extern int32_t decoder__motion_Y__FLAG_SZ;
static inline int32_t bitxor(int32_t x, int32_t y);
extern int32_t decoder__motion_V__INTRA;
static inline int32_t bitor(int32_t x, int32_t y);
extern int32_t decoder__ACCODED;
extern int32_t decoder__texture_Y__MB_COORD_SZ;
extern int32_t decoder__motion_V__MAXH_IN_MB;
extern int32_t decoder__texture_U__DCRecontruction__SAMPLE_SZ;
extern int32_t decoder__parser__MOTION;
extern int32_t decoder__QUANT_MASK;
extern int32_t decoder__texture_U__MAXW_IN_MB;
extern int32_t decoder__motion_Y__BTYPE_SZ;
extern int32_t decoder__texture_V__INTRA;
extern int32_t decoder__texture_Y__idct2d__OUT_SZ;
extern int32_t decoder__parser__FCODE_SHIFT;
extern int32_t decoder__motion_Y__ROUND_TYPE;
static inline int32_t urshift(int32_t x, int32_t y);
extern int32_t decoder__parser__INTER;
extern int32_t decoder__texture_U__NEWVOP;
extern int32_t decoder__SAMPLE_COUNT_SZ;
extern int32_t decoder__motion_Y__ADDR_SZ;
extern int32_t decoder__parser__MB_COORD_SZ;
extern int32_t decoder__texture_V__DCRecontruction__QUANT_SZ;
extern int32_t decoder__motion_U__BTYPE_SZ;
extern int32_t decoder__motion_V__LAYOUT;
extern int32_t decoder__parser__ROUND_TYPE;
extern int32_t decoder__texture_U__DCRecontruction__ACPRED;
extern int32_t decoder__texture_U__DCRecontruction__NEWVOP;
static inline int32_t rshift(int32_t x, int32_t y);
extern int32_t decoder__motion_V__MV_SZ;
extern int32_t decoder__texture_Y__DCRecontruction__SAMPLE_SZ;
extern int32_t decoder__motion_Y__MAXW_IN_MB;
extern int32_t decoder__QUANT_SZ;
extern int32_t decoder__texture_Y__DCRecontruction__QUANT_MASK;
extern int32_t decoder__texture_V__BTYPE_SZ;
extern int32_t decoder__texture_Y__MAXW_IN_MB;
extern int32_t decoder__ADDR_SZ;
extern int32_t decoder__parser__FCODE_MASK;
extern int32_t decoder__texture_V__MAXW_IN_MB;
extern int32_t decoder__motion_Y__NEWVOP;
extern int32_t decoder__parser__QUANT_MASK;
extern int32_t decoder__motion_U__ADDR_SZ;
extern int32_t decoder__texture_V__ACPRED;
#endif