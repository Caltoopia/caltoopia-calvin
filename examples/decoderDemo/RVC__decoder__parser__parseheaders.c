#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_bits ART_INPUT(0)
#define  OUT0_BTYPE ART_OUTPUT(0)
#define  OUT1_MV ART_OUTPUT(1)
#define  OUT2_RUN ART_OUTPUT(2)
#define  OUT3_VALUE ART_OUTPUT(3)
#define  OUT4_LAST ART_OUTPUT(4)
#define  OUT5_WIDTH ART_OUTPUT(5)
#define  OUT6_HEIGHT ART_OUTPUT(6)
#define  OUT7_QP ART_OUTPUT(7)

//Actor constants
static const int32_t MAXW_IN_MB = 121;
static const int32_t MB_COORD_SZ = 8;
static const int32_t BTYPE_SZ = 12;
static const int32_t MV_SZ = 9;
static const int32_t NEWVOP = 2048;
static const int32_t INTRA = 1024;
static const int32_t INTER = 512;
static const int32_t QUANT_MASK = 31;
static const int32_t ROUND_TYPE = 32;
static const int32_t FCODE_MASK = 448;
static const int32_t FCODE_SHIFT = 6;
static const int32_t ACPRED = 1;
static const int32_t ACCODED = 2;
static const int32_t FOURMV = 4;
static const int32_t MOTION = 8;
static const int32_t SAMPLE_COUNT_SZ = 8;
static const int32_t SAMPLE_SZ = 13;
static const int32_t MV_START_INDEX = 616;
static const int32_t VISUAL_OBJECT_LAYER_PRIORITY_LENGTH = 3;
static const int32_t VOL_SHAPE_LENGTH = 2;
static const int32_t VOP_PREDICTION_LENGTH = 2;
static const int32_t ASPECT_RATIO_INFO_LENGTH = 4;
static const int32_t VOL_HEIGHT_LENGTH = 13;
static const int32_t VOL_WIDTH_LENGTH = 13;
static const int32_t B_VOP = 2;
static const int32_t I_VOP = 0;
static const int32_t VO_HEADER_LENGTH = 27;
static const int32_t P_VOP = 1;
static const int32_t VOP_FCODE_FOR_LENGTH = 3;
static const int32_t VOP_FCODE_FOR_MASK = 7;
static const int32_t TIME_INC_RES_LENGTH = 16;
static const int32_t LAST_HALF_VBV_OCC_LENGTH = 15;
static const int32_t VISUAL_OBJECT_LAYER_VERID_LENGTH = 4;
static const int32_t PAR_WIDTH_LENGTH = 8;
static const int32_t ASPECT_RATIO_INFO_IS_DETAILED = 15;
static const int32_t VO_NO_SHORT_HEADER = 8;
static const int32_t LEVEL_LENGTH = 12;
static const int32_t LEVEL_MASK = 4095;
static const int32_t intra_dc_threshold_table[8] = {32, 13, 15, 17, 19, 21, 23, 1};
static const int32_t MISC_BIT_LENGTH = 9;
static const int32_t MARKER_LENGTH = 1;
static const int32_t PAR_HEIGHT_LENGTH = 8;
static const int32_t ESCAPE_CODE = 7167;
static const int32_t CHROMA_FORMAT_LENGTH = 2;
static const int32_t VOP_START_CODE = 182;
static const int32_t LAST_HALF_VBV_BUF_SZ_LENGTH = 3;
static const int32_t DCBITS_UV_START_INDEX = 118;
static const int32_t INTRA_DC_VLC_THR_LENGTH = 3;
static const int32_t LAST_HALF_BIT_RATE_LENGTH = 15;
static const int32_t dquant_table[4] = {-1, -2, 1, 2};
static const int32_t FIRST_HALF_VBV_OCC_LENGTH = 11;
static const int32_t RUN_LENGTH = 6;
static const int32_t RUN_MASK = 63;
static const int32_t BITS_QUANT = 5;
static const int32_t BITS_QUANT_MASK = 31;
static const int32_t DCBITS_Y_START_INDEX = 92;
static const int32_t VOL_ID_LENGTH = 1;
static const int32_t COEFF_INTER_START_INDEX = 144;
static const int32_t FIRST_HALF_BIT_RATE_LENGTH = 15;
static const int32_t VO_ID_LENGTH = 5;
static const int32_t FIRST_HALF_VBV_BUF_SZ_LENGTH = 15;
static const int32_t CBP_SZ = 7;
static const int32_t MCBPC_PVOP_START_INDEX = 16;
static const int32_t VOL_START_CODE = 32;
static const int32_t VLD_TABLE_ADDR_BITS = 12;
static const int32_t LOW_DELAY_LENGTH = 1;
static const int32_t VIDEO_OBJECT_TYPE_INDICATION_LENGTH = 8;
static const int32_t MCBPC_IVOP_START_INDEX = 0;
static const int32_t COEFF_INTRA_START_INDEX = 380;
static const int32_t CBPY_START_INDEX = 58;
static const int32_t VLD_TABLE_DATA_BITS = 20;
static const int32_t vld_table[760] = {10, 12, 18, 58, 26, 76, 34, 16, 42, 50, 1, 80, 144, 208, 140, 204, 74, 0, 82, 226, 90, 218, 98, 202, 106, 178, 114, 162, 122, 146, 130, 138, 1, 1, 208, 144, 154, 140, 80, 196, 170, 204, 76, 200, 186, 194, 136, 72, 132, 68, 210, 12, 16, 192, 128, 64, 8, 4, 242, 338, 250, 314, 258, 298, 266, 290, 274, 282, 1, 1, 24, 36, 32, 16, 306, 0, 8, 4, 322, 330, 48, 40, 56, 20, 346, 60, 354, 362, 52, 12, 44, 28, 378, 466, 386, 458, 394, 16, 402, 20, 410, 24, 418, 28, 426, 32, 434, 36, 442, 40, 450, 44, 1, 48, 12, 0, 8, 4, 482, 570, 490, 8, 498, 12, 506, 16, 514, 20, 522, 24, 530, 28, 538, 32, 546, 36, 554, 40, 562, 44, 1, 48, 4, 0, 586, 1498, 594, 1426, 602, 1338, 610, 1194, 618, 1066, 626, 874, 634, 818, 642, 794, 650, 770, 658, 714, 666, 690, 674, 682, 1, 1, 1, 1, 698, 706, 1, 1, 1, 1, 722, 746, 730, 738, 1, 1, 1, 1, 754, 762, 1, 1, 1, 1, 778, 786, 16456, 16396, 44, 40, 802, 810, 18180, 18116, 18052, 17988, 826, 850, 834, 842, 584, 520, 456, 392, 858, 866, 328, 204, 140, 80, 882, 28668, 890, 946, 898, 922, 906, 914, 48, 84, 1476, 1540, 930, 938, 18244, 18308, 18372, 18436, 954, 1010, 962, 986, 970, 978, 88, 144, 268, 332, 994, 1002, 396, 648, 1604, 1668, 1018, 1042, 1026, 1034, 18500, 18564, 18628, 18692, 1050, 1058, 18756, 18820, 18884, 18948, 1074, 1138, 1082, 1114, 1090, 1106, 1098, 17924, 36, 32, 17860, 17796, 1122, 1130, 17732, 17668, 17604, 17540, 1146, 1170, 1154, 1162, 17476, 16392, 1412, 1348, 1178, 1186, 1284, 1220, 1156, 1092, 1202, 1282, 1210, 1258, 1218, 1242, 1226, 1234, 1028, 964, 264, 200, 1250, 17412, 28, 24, 1266, 1274, 17348, 17284, 17220, 17156, 1290, 1314, 1298, 1306, 17092, 17028, 16964, 900, 1322, 1330, 836, 136, 76, 20, 1346, 1402, 1354, 1378, 1362, 1370, 16900, 16836, 16772, 16708, 1386, 1394, 772, 708, 644, 16, 1410, 1418, 16644, 16580, 16516, 16452, 1434, 1482, 1442, 1466, 1450, 1458, 580, 516, 452, 388, 1474, 324, 72, 12, 1490, 16388, 260, 196, 4, 1506, 68, 1514, 132, 8, 1530, 2442, 1538, 2370, 1546, 2282, 1554, 2138, 1562, 2010, 1570, 1818, 1578, 1762, 1586, 1738, 1594, 1714, 1602, 1658, 1610, 1634, 1618, 1626, 1, 1, 1, 1, 1642, 1650, 1, 1, 1, 1, 1666, 1690, 1674, 1682, 1, 1, 1, 1, 1698, 1706, 1, 1, 1, 1, 1722, 1730, 262172, 262168, 88, 84, 1746, 1754, 264200, 263180, 262164, 13316, 1770, 1794, 1778, 1786, 5132, 8200, 4108, 3088, 1802, 1810, 2064, 1052, 80, 76, 1826, 28668, 1834, 1890, 1842, 1866, 1850, 1858, 92, 96, 1056, 9224, 1874, 1882, 265224, 266248, 277508, 278532, 1898, 1954, 1906, 1930, 1914, 1922, 100, 104, 108, 1060, 1938, 1946, 6156, 1064, 2068, 7180, 1962, 1986, 1970, 1978, 14340, 262176, 267272, 268296, 1994, 2002, 279556, 280580, 281604, 282628, 2018, 2082, 2026, 2058, 2034, 2050, 2042, 276484, 72, 68, 275460, 274436, 2066, 2074, 273412, 272388, 263176, 262160, 2090, 2114, 2098, 2106, 12292, 11268, 7176, 6152, 2122, 2130, 5128, 3084, 2060, 1048, 2146, 2226, 2154, 2202, 2162, 2186, 2170, 2178, 1044, 64, 4104, 60, 2194, 270340, 56, 52, 2210, 2218, 269316, 268292, 262156, 10244, 2234, 2258, 2242, 2250, 9220, 8196, 271364, 3080, 2266, 2274, 1040, 48, 44, 40, 2290, 2346, 2298, 2322, 2306, 2314, 266244, 265220, 6148, 267268, 2330, 2338, 7172, 2056, 1036, 36, 2354, 2362, 262152, 5124, 264196, 263172, 2378, 2426, 2386, 2410, 2394, 2402, 4100, 3076, 32, 28, 2418, 2052, 1032, 24, 2434, 262148, 20, 16, 4, 2450, 8, 2458, 1028, 12, 2474, 0, 2482, 3034, 2490, 3026, 2498, 3018, 2506, 2978, 2514, 2890, 2522, 2770, 2530, 2714, 2538, 2658, 2546, 2634, 2554, 2610, 2562, 2586, 2570, 2578, 1, 1, 1, 1, 2594, 2602, 1, 1, 1, 1, 2618, 2626, 128, -128, 124, -124, 2642, 2650, 120, -120, 116, -116, 2666, 2690, 2674, 2682, 112, -112, 108, -108, 2698, 2706, 104, -104, 100, -100, 2722, 2746, 2730, 2738, 96, -96, 92, -92, 2754, 2762, 88, -88, 84, -84, 2778, 2834, 2786, 2810, 2794, 2802, 80, -80, 76, -76, 2818, 2826, 72, -72, 68, -68, 2842, 2866, 2850, 2858, 64, -64, 60, -60, 2874, 2882, 56, -56, 52, -52, 2898, 2970, 2906, 2946, 2914, 2938, 2922, 2930, 48, -48, 44, -44, 40, -40, 2954, 2962, 36, -36, 32, -32, 28, -28, 2986, 3010, 2994, 3002, 24, -24, 20, -20, 16, -16, 12, -12, 8, -8, 4, -4};
static const int32_t MCBPC_LENGTH = 9;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  bool_t ac_coded;
  int32_t mylog;
  int32_t level_lookup_inter;
  int32_t run_lookup_inter;
  int32_t fcode;
  bool_t b_last;
  int32_t intra_dc_vlc_thr;
  bool_t prediction_is_IVOP;
  bool_t prediction_is_PVOP;
  bool_t fourmvflag;
  int32_t mvcomp;
  int32_t bits_to_read_count;
  int32_t bit_count;
  int32_t mby;
  int32_t vol_width;
  int32_t read_result_in_progress;
  int32_t msb_result;
  int32_t prev_quant;
  int32_t vop_quant;
  int32_t vol_height;
  int32_t level_lookup_intra;
  int32_t run_lookup_intra;
  bool_t btype_is_Q;
  int32_t mbx;
  bool_t btype_is_INTRA;
  int32_t dc_bits;
  int32_t cbpc;
  int32_t cbp;
  int32_t vld_index;
  bool_t acpredflag;
  bool_t prediction_is_BVOP;
  int32_t comp;
  int32_t vld_codeword;
} ActorInstance_RVC_decoder__parser__parseheaders;

//Actor functions
static inline int32_t RVC_decoder__parser__parseheadersmask_bits(ActorInstance_RVC_decoder__parser__parseheaders* thisActor, int32_t v, int32_t n){
  return bitand(v, (lshift(1, n) - 1));
}
static inline bool_t RVC_decoder__parser__parseheadersdone_reading_bits(ActorInstance_RVC_decoder__parser__parseheaders* thisActor){
  return (thisActor->bits_to_read_count < 0);
}
static inline int32_t RVC_decoder__parser__parseheadersread_result(ActorInstance_RVC_decoder__parser__parseheaders* thisActor){
  return thisActor->read_result_in_progress;
}
static inline int32_t RVC_decoder__parser__parseheadersintra_max_level(ActorInstance_RVC_decoder__parser__parseheaders* thisActor, bool_t last, int32_t run){
  return (((!(last))) ? ((((run == 0)) ? (27):((((run == 1)) ? (10):((((run == 2)) ? (5):((((run == 3)) ? (4):((((run < 8)) ? (3):((((run < 10)) ? (2):((((run < 15)) ? (1):(0))))))))))))))):((((run == 0)) ? (8):((((run == 1)) ? (3):((((run < 7)) ? (2):((((run < 21)) ? (1):(0))))))))));
}
static inline int32_t RVC_decoder__parser__parseheadersinter_max_level(ActorInstance_RVC_decoder__parser__parseheaders* thisActor, bool_t last, int32_t run){
  return (((!(last))) ? ((((run == 0)) ? (12):((((run == 1)) ? (6):((((run == 2)) ? (4):((((run < 7)) ? (3):((((run < 11)) ? (2):((((run < 27)) ? (1):(0))))))))))))):((((run == 0)) ? (3):((((run == 1)) ? (2):((((run < 41)) ? (1):(0))))))));
}
static inline int32_t RVC_decoder__parser__parseheadersintra_max_run(ActorInstance_RVC_decoder__parser__parseheaders* thisActor, bool_t last, int32_t level){
  return (((!(last))) ? ((((level == 1)) ? (14):((((level == 2)) ? (9):((((level == 3)) ? (7):((((level == 4)) ? (3):((((level == 5)) ? (2):((((level < 11)) ? (1):(0))))))))))))):((((level == 1)) ? (20):((((level == 2)) ? (6):((((level == 3)) ? (1):(0))))))));
}
static inline int32_t RVC_decoder__parser__parseheadersinter_max_run(ActorInstance_RVC_decoder__parser__parseheaders* thisActor, bool_t last, int32_t level){
  return (((!(last))) ? ((((level == 1)) ? (26):((((level == 2)) ? (10):((((level == 3)) ? (6):((((level == 4)) ? (2):(((((level == 5) || (level == 6))) ? (1):(0))))))))))):((((level == 1)) ? (40):((((level == 2)) ? (1):(0))))));
}
static inline bool_t RVC_decoder__parser__parseheadersvld_success(ActorInstance_RVC_decoder__parser__parseheaders* thisActor){
  return (bitand(thisActor->vld_codeword, 3) == 0);
}
static inline bool_t RVC_decoder__parser__parseheadersvld_failure(ActorInstance_RVC_decoder__parser__parseheaders* thisActor){
  return (bitand(thisActor->vld_codeword, 1) == 1);
}
static inline int32_t RVC_decoder__parser__parseheadersvld_result(ActorInstance_RVC_decoder__parser__parseheaders* thisActor){
  return rshift(thisActor->vld_codeword, 2);
}
void RVC_decoder__parser__parseheadersset_bits_to_read(ActorInstance_RVC_decoder__parser__parseheaders* thisActor, int32_t count) {
  thisActor->bits_to_read_count = (count - 1);
  thisActor->read_result_in_progress = 0;
}
void RVC_decoder__parser__parseheadersnext_mbxy(ActorInstance_RVC_decoder__parser__parseheaders* thisActor) {
  thisActor->mbx = (thisActor->mbx + 1);
  if ((thisActor->mbx == thisActor->vol_width)) {
    thisActor->mbx = 0;
    thisActor->mby = (thisActor->mby + 1);
  }
}
void RVC_decoder__parser__parseheadersstart_vld_engine(ActorInstance_RVC_decoder__parser__parseheaders* thisActor, int32_t index) {
  thisActor->vld_index = index;
  thisActor->vld_codeword = 2;
}
ART_ACTION_CONTEXT(1, 8)

ART_ACTION(action0, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action1__vol_object_layer_identification, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action2__vol_aspect__detailed, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action3__vol_control__detailed, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action4__vol_vbv__detailed, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action5__vol_shape, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action6__vol_time_inc_res, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action7__set_vol_width, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action8__set_vol_height, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action9__byte_align, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action10__vop_predict__supported, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action11__vop_timebase__one, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action12__vop_timebase__zero, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action13__vop_coding__uncoded, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action14__vop_coding__coded, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action15__send_new_vop_cmd, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action16__send_new_vop_width, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action17__send_new_vop_height, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action18__mb_done, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action19__get_mcbpc__ivop, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action20__get_mcbpc__pvop, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action21__mcbpc_pvop_uncoded, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action22__mcbpc_pvop_uncoded1, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action23__get_mbtype__noac, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action24__get_mbtype__ac, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action25__final_cbpy_inter, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action26__final_cbpy_intra, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action27__final_dquant, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action28__mb_dispatch_done, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action29__mb_dispatch_intra, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action30__mb_dispatch_inter_no_ac, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action31__mb_dispatch_inter_ac_coded, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action32__vld_start_intra__dc, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action33__vld_start_intra__nodc__ac_coded, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action34__vld_start_intra__nodc__no_ac_coded, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action35__vld_start_inter__ac_coded, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action36__vld_start_inter__not_ac_coded, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action37__get_dc_bits__none, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action38__get_dc_bits__some, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action39__dc_bits_shift, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action40__get_dc, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action41__block_done, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action42__dct_coeff, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action43__vld_code, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action44__vld_level, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action45__vld_run_or_direct, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action46__vld_run, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action47__vld_direct_read, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action48__vld_direct, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action49__do_level_lookup, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action50__vld_level_lookup, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action51__do_run_lookup, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action52__vld_run_lookup, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action53__mvcode_done, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action54__mvcode, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action55__mag_x, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action56__get_residual_x, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action57__mag_y, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action58__get_residual_y, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action59, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action60__do_vld_failure, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action61__generic_done, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action62__generic_done_with_bitread, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action63__test_zero_byte, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action64__test_vo_byte, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action65__test_vol_byte, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action66__test_vop_byte, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action67__test_one_byte, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION(action68__request_byte, ActorInstance_RVC_decoder__parser__parseheaders);
ART_ACTION_SCHEDULER(RVC_decoder__parser__parseheaders_action_scheduler);
static void ActorInstance_RVC_decoder__parser__parseheaders_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "bits", sizeof(bool_t), NULL},
};
static const PortDescription outputPortDescriptions[]={
  {0, "BTYPE", sizeof(int32_t), NULL},
  {0, "MV", sizeof(int32_t), NULL},
  {0, "RUN", sizeof(int32_t), NULL},
  {0, "VALUE", sizeof(int32_t), NULL},
  {0, "LAST", sizeof(bool_t), NULL},
  {0, "WIDTH", sizeof(int32_t), NULL},
  {0, "HEIGHT", sizeof(int32_t), NULL},
  {0, "QP", sizeof(int32_t), NULL},
};

static const int portRate_in_action0[] = {1};

static const int portRate_out_action0[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action1__vol_object_layer_identification[] = {1};

static const int portRate_out_action1__vol_object_layer_identification[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action2__vol_aspect__detailed[] = {0};

static const int portRate_out_action2__vol_aspect__detailed[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action3__vol_control__detailed[] = {1};

static const int portRate_out_action3__vol_control__detailed[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action4__vol_vbv__detailed[] = {1};

static const int portRate_out_action4__vol_vbv__detailed[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action5__vol_shape[] = {0};

static const int portRate_out_action5__vol_shape[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action6__vol_time_inc_res[] = {0};

static const int portRate_out_action6__vol_time_inc_res[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action7__set_vol_width[] = {0};

static const int portRate_out_action7__set_vol_width[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action8__set_vol_height[] = {0};

static const int portRate_out_action8__set_vol_height[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action9__byte_align[] = {0};

static const int portRate_out_action9__byte_align[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action10__vop_predict__supported[] = {0};

static const int portRate_out_action10__vop_predict__supported[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action11__vop_timebase__one[] = {1};

static const int portRate_out_action11__vop_timebase__one[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action12__vop_timebase__zero[] = {1};

static const int portRate_out_action12__vop_timebase__zero[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action13__vop_coding__uncoded[] = {1};

static const int portRate_out_action13__vop_coding__uncoded[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action14__vop_coding__coded[] = {1};

static const int portRate_out_action14__vop_coding__coded[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action15__send_new_vop_cmd[] = {0};

static const int portRate_out_action15__send_new_vop_cmd[] = {1, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action16__send_new_vop_width[] = {0};

static const int portRate_out_action16__send_new_vop_width[] = {1, 0, 0, 0, 0, 1, 0, 0};

static const int portRate_in_action17__send_new_vop_height[] = {0};

static const int portRate_out_action17__send_new_vop_height[] = {1, 0, 0, 0, 0, 0, 1, 0};

static const int portRate_in_action18__mb_done[] = {0};

static const int portRate_out_action18__mb_done[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action19__get_mcbpc__ivop[] = {0};

static const int portRate_out_action19__get_mcbpc__ivop[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action20__get_mcbpc__pvop[] = {1};

static const int portRate_out_action20__get_mcbpc__pvop[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action21__mcbpc_pvop_uncoded[] = {1};

static const int portRate_out_action21__mcbpc_pvop_uncoded[] = {1, 0, 0, 0, 0, 0, 0, 1};

static const int portRate_in_action22__mcbpc_pvop_uncoded1[] = {0};

static const int portRate_out_action22__mcbpc_pvop_uncoded1[] = {1, 0, 0, 0, 0, 0, 0, 1};

static const int portRate_in_action23__get_mbtype__noac[] = {0};

static const int portRate_out_action23__get_mbtype__noac[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action24__get_mbtype__ac[] = {1};

static const int portRate_out_action24__get_mbtype__ac[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action25__final_cbpy_inter[] = {0};

static const int portRate_out_action25__final_cbpy_inter[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action26__final_cbpy_intra[] = {0};

static const int portRate_out_action26__final_cbpy_intra[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action27__final_dquant[] = {0};

static const int portRate_out_action27__final_dquant[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action28__mb_dispatch_done[] = {0};

static const int portRate_out_action28__mb_dispatch_done[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action29__mb_dispatch_intra[] = {0};

static const int portRate_out_action29__mb_dispatch_intra[] = {1, 0, 0, 0, 0, 0, 0, 1};

static const int portRate_in_action30__mb_dispatch_inter_no_ac[] = {0};

static const int portRate_out_action30__mb_dispatch_inter_no_ac[] = {1, 0, 0, 0, 0, 0, 0, 1};

static const int portRate_in_action31__mb_dispatch_inter_ac_coded[] = {0};

static const int portRate_out_action31__mb_dispatch_inter_ac_coded[] = {1, 0, 0, 0, 0, 0, 0, 1};

static const int portRate_in_action32__vld_start_intra__dc[] = {0};

static const int portRate_out_action32__vld_start_intra__dc[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action33__vld_start_intra__nodc__ac_coded[] = {0};

static const int portRate_out_action33__vld_start_intra__nodc__ac_coded[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action34__vld_start_intra__nodc__no_ac_coded[] = {0};

static const int portRate_out_action34__vld_start_intra__nodc__no_ac_coded[] = {0, 0, 1, 1, 1, 0, 0, 0};

static const int portRate_in_action35__vld_start_inter__ac_coded[] = {0};

static const int portRate_out_action35__vld_start_inter__ac_coded[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action36__vld_start_inter__not_ac_coded[] = {0};

static const int portRate_out_action36__vld_start_inter__not_ac_coded[] = {0, 0, 1, 1, 1, 0, 0, 0};

static const int portRate_in_action37__get_dc_bits__none[] = {0};

static const int portRate_out_action37__get_dc_bits__none[] = {0, 0, 1, 1, 1, 0, 0, 0};

static const int portRate_in_action38__get_dc_bits__some[] = {0};

static const int portRate_out_action38__get_dc_bits__some[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action39__dc_bits_shift[] = {0};

static const int portRate_out_action39__dc_bits_shift[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action40__get_dc[] = {0};

static const int portRate_out_action40__get_dc[] = {0, 0, 1, 1, 1, 0, 0, 0};

static const int portRate_in_action41__block_done[] = {0};

static const int portRate_out_action41__block_done[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action42__dct_coeff[] = {0};

static const int portRate_out_action42__dct_coeff[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action43__vld_code[] = {1};

static const int portRate_out_action43__vld_code[] = {0, 0, 1, 1, 1, 0, 0, 0};

static const int portRate_in_action44__vld_level[] = {1};

static const int portRate_out_action44__vld_level[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action45__vld_run_or_direct[] = {1};

static const int portRate_out_action45__vld_run_or_direct[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action46__vld_run[] = {1};

static const int portRate_out_action46__vld_run[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action47__vld_direct_read[] = {1};

static const int portRate_out_action47__vld_direct_read[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action48__vld_direct[] = {0};

static const int portRate_out_action48__vld_direct[] = {0, 0, 1, 1, 1, 0, 0, 0};

static const int portRate_in_action49__do_level_lookup[] = {0};

static const int portRate_out_action49__do_level_lookup[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action50__vld_level_lookup[] = {1};

static const int portRate_out_action50__vld_level_lookup[] = {0, 0, 1, 1, 1, 0, 0, 0};

static const int portRate_in_action51__do_run_lookup[] = {0};

static const int portRate_out_action51__do_run_lookup[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action52__vld_run_lookup[] = {1};

static const int portRate_out_action52__vld_run_lookup[] = {0, 0, 1, 1, 1, 0, 0, 0};

static const int portRate_in_action53__mvcode_done[] = {0};

static const int portRate_out_action53__mvcode_done[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action54__mvcode[] = {0};

static const int portRate_out_action54__mvcode[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action55__mag_x[] = {0};

static const int portRate_out_action55__mag_x[] = {0, 1, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action56__get_residual_x[] = {0};

static const int portRate_out_action56__get_residual_x[] = {0, 1, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action57__mag_y[] = {0};

static const int portRate_out_action57__mag_y[] = {0, 1, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action58__get_residual_y[] = {0};

static const int portRate_out_action58__get_residual_y[] = {0, 1, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action59[] = {1};

static const int portRate_out_action59[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action60__do_vld_failure[] = {0};

static const int portRate_out_action60__do_vld_failure[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action61__generic_done[] = {0};

static const int portRate_out_action61__generic_done[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action62__generic_done_with_bitread[] = {1};

static const int portRate_out_action62__generic_done_with_bitread[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action63__test_zero_byte[] = {0};

static const int portRate_out_action63__test_zero_byte[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action64__test_vo_byte[] = {0};

static const int portRate_out_action64__test_vo_byte[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action65__test_vol_byte[] = {0};

static const int portRate_out_action65__test_vol_byte[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action66__test_vop_byte[] = {0};

static const int portRate_out_action66__test_vop_byte[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action67__test_one_byte[] = {0};

static const int portRate_out_action67__test_one_byte[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const int portRate_in_action68__request_byte[] = {0};

static const int portRate_out_action68__request_byte[] = {0, 0, 0, 0, 0, 0, 0, 0};

static const ActionDescription actionDescriptions[] = {
  {"action0", portRate_in_action0, portRate_out_action0},
  {"action1__vol_object_layer_identification", portRate_in_action1__vol_object_layer_identification, portRate_out_action1__vol_object_layer_identification},
  {"action2__vol_aspect__detailed", portRate_in_action2__vol_aspect__detailed, portRate_out_action2__vol_aspect__detailed},
  {"action3__vol_control__detailed", portRate_in_action3__vol_control__detailed, portRate_out_action3__vol_control__detailed},
  {"action4__vol_vbv__detailed", portRate_in_action4__vol_vbv__detailed, portRate_out_action4__vol_vbv__detailed},
  {"action5__vol_shape", portRate_in_action5__vol_shape, portRate_out_action5__vol_shape},
  {"action6__vol_time_inc_res", portRate_in_action6__vol_time_inc_res, portRate_out_action6__vol_time_inc_res},
  {"action7__set_vol_width", portRate_in_action7__set_vol_width, portRate_out_action7__set_vol_width},
  {"action8__set_vol_height", portRate_in_action8__set_vol_height, portRate_out_action8__set_vol_height},
  {"action9__byte_align", portRate_in_action9__byte_align, portRate_out_action9__byte_align},
  {"action10__vop_predict__supported", portRate_in_action10__vop_predict__supported, portRate_out_action10__vop_predict__supported},
  {"action11__vop_timebase__one", portRate_in_action11__vop_timebase__one, portRate_out_action11__vop_timebase__one},
  {"action12__vop_timebase__zero", portRate_in_action12__vop_timebase__zero, portRate_out_action12__vop_timebase__zero},
  {"action13__vop_coding__uncoded", portRate_in_action13__vop_coding__uncoded, portRate_out_action13__vop_coding__uncoded},
  {"action14__vop_coding__coded", portRate_in_action14__vop_coding__coded, portRate_out_action14__vop_coding__coded},
  {"action15__send_new_vop_cmd", portRate_in_action15__send_new_vop_cmd, portRate_out_action15__send_new_vop_cmd},
  {"action16__send_new_vop_width", portRate_in_action16__send_new_vop_width, portRate_out_action16__send_new_vop_width},
  {"action17__send_new_vop_height", portRate_in_action17__send_new_vop_height, portRate_out_action17__send_new_vop_height},
  {"action18__mb_done", portRate_in_action18__mb_done, portRate_out_action18__mb_done},
  {"action19__get_mcbpc__ivop", portRate_in_action19__get_mcbpc__ivop, portRate_out_action19__get_mcbpc__ivop},
  {"action20__get_mcbpc__pvop", portRate_in_action20__get_mcbpc__pvop, portRate_out_action20__get_mcbpc__pvop},
  {"action21__mcbpc_pvop_uncoded", portRate_in_action21__mcbpc_pvop_uncoded, portRate_out_action21__mcbpc_pvop_uncoded},
  {"action22__mcbpc_pvop_uncoded1", portRate_in_action22__mcbpc_pvop_uncoded1, portRate_out_action22__mcbpc_pvop_uncoded1},
  {"action23__get_mbtype__noac", portRate_in_action23__get_mbtype__noac, portRate_out_action23__get_mbtype__noac},
  {"action24__get_mbtype__ac", portRate_in_action24__get_mbtype__ac, portRate_out_action24__get_mbtype__ac},
  {"action25__final_cbpy_inter", portRate_in_action25__final_cbpy_inter, portRate_out_action25__final_cbpy_inter},
  {"action26__final_cbpy_intra", portRate_in_action26__final_cbpy_intra, portRate_out_action26__final_cbpy_intra},
  {"action27__final_dquant", portRate_in_action27__final_dquant, portRate_out_action27__final_dquant},
  {"action28__mb_dispatch_done", portRate_in_action28__mb_dispatch_done, portRate_out_action28__mb_dispatch_done},
  {"action29__mb_dispatch_intra", portRate_in_action29__mb_dispatch_intra, portRate_out_action29__mb_dispatch_intra},
  {"action30__mb_dispatch_inter_no_ac", portRate_in_action30__mb_dispatch_inter_no_ac, portRate_out_action30__mb_dispatch_inter_no_ac},
  {"action31__mb_dispatch_inter_ac_coded", portRate_in_action31__mb_dispatch_inter_ac_coded, portRate_out_action31__mb_dispatch_inter_ac_coded},
  {"action32__vld_start_intra__dc", portRate_in_action32__vld_start_intra__dc, portRate_out_action32__vld_start_intra__dc},
  {"action33__vld_start_intra__nodc__ac_coded", portRate_in_action33__vld_start_intra__nodc__ac_coded, portRate_out_action33__vld_start_intra__nodc__ac_coded},
  {"action34__vld_start_intra__nodc__no_ac_coded", portRate_in_action34__vld_start_intra__nodc__no_ac_coded, portRate_out_action34__vld_start_intra__nodc__no_ac_coded},
  {"action35__vld_start_inter__ac_coded", portRate_in_action35__vld_start_inter__ac_coded, portRate_out_action35__vld_start_inter__ac_coded},
  {"action36__vld_start_inter__not_ac_coded", portRate_in_action36__vld_start_inter__not_ac_coded, portRate_out_action36__vld_start_inter__not_ac_coded},
  {"action37__get_dc_bits__none", portRate_in_action37__get_dc_bits__none, portRate_out_action37__get_dc_bits__none},
  {"action38__get_dc_bits__some", portRate_in_action38__get_dc_bits__some, portRate_out_action38__get_dc_bits__some},
  {"action39__dc_bits_shift", portRate_in_action39__dc_bits_shift, portRate_out_action39__dc_bits_shift},
  {"action40__get_dc", portRate_in_action40__get_dc, portRate_out_action40__get_dc},
  {"action41__block_done", portRate_in_action41__block_done, portRate_out_action41__block_done},
  {"action42__dct_coeff", portRate_in_action42__dct_coeff, portRate_out_action42__dct_coeff},
  {"action43__vld_code", portRate_in_action43__vld_code, portRate_out_action43__vld_code},
  {"action44__vld_level", portRate_in_action44__vld_level, portRate_out_action44__vld_level},
  {"action45__vld_run_or_direct", portRate_in_action45__vld_run_or_direct, portRate_out_action45__vld_run_or_direct},
  {"action46__vld_run", portRate_in_action46__vld_run, portRate_out_action46__vld_run},
  {"action47__vld_direct_read", portRate_in_action47__vld_direct_read, portRate_out_action47__vld_direct_read},
  {"action48__vld_direct", portRate_in_action48__vld_direct, portRate_out_action48__vld_direct},
  {"action49__do_level_lookup", portRate_in_action49__do_level_lookup, portRate_out_action49__do_level_lookup},
  {"action50__vld_level_lookup", portRate_in_action50__vld_level_lookup, portRate_out_action50__vld_level_lookup},
  {"action51__do_run_lookup", portRate_in_action51__do_run_lookup, portRate_out_action51__do_run_lookup},
  {"action52__vld_run_lookup", portRate_in_action52__vld_run_lookup, portRate_out_action52__vld_run_lookup},
  {"action53__mvcode_done", portRate_in_action53__mvcode_done, portRate_out_action53__mvcode_done},
  {"action54__mvcode", portRate_in_action54__mvcode, portRate_out_action54__mvcode},
  {"action55__mag_x", portRate_in_action55__mag_x, portRate_out_action55__mag_x},
  {"action56__get_residual_x", portRate_in_action56__get_residual_x, portRate_out_action56__get_residual_x},
  {"action57__mag_y", portRate_in_action57__mag_y, portRate_out_action57__mag_y},
  {"action58__get_residual_y", portRate_in_action58__get_residual_y, portRate_out_action58__get_residual_y},
  {"action59", portRate_in_action59, portRate_out_action59},
  {"action60__do_vld_failure", portRate_in_action60__do_vld_failure, portRate_out_action60__do_vld_failure},
  {"action61__generic_done", portRate_in_action61__generic_done, portRate_out_action61__generic_done},
  {"action62__generic_done_with_bitread", portRate_in_action62__generic_done_with_bitread, portRate_out_action62__generic_done_with_bitread},
  {"action63__test_zero_byte", portRate_in_action63__test_zero_byte, portRate_out_action63__test_zero_byte},
  {"action64__test_vo_byte", portRate_in_action64__test_vo_byte, portRate_out_action64__test_vo_byte},
  {"action65__test_vol_byte", portRate_in_action65__test_vol_byte, portRate_out_action65__test_vol_byte},
  {"action66__test_vop_byte", portRate_in_action66__test_vop_byte, portRate_out_action66__test_vop_byte},
  {"action67__test_one_byte", portRate_in_action67__test_one_byte, portRate_out_action67__test_one_byte},
  {"action68__request_byte", portRate_in_action68__request_byte, portRate_out_action68__request_byte},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__parser__parseheaders",
  ActorInstance_RVC_decoder__parser__parseheaders,
  ActorInstance_RVC_decoder__parser__parseheaders_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  0, 0, // serialize/deserialize
  RVC_decoder__parser__parseheaders_action_scheduler,
  0, // no destructor
  1, inputPortDescriptions,
  8, outputPortDescriptions,
  69, actionDescriptions
);

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4085(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (!(RVC_decoder__parser__parseheadersdone_reading_bits(thisActor)));
    return ret;
  }
}

// 
ART_ACTION(action0, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t b;
  ART_ACTION_ENTER(action0, 0);
  b = pinRead_bool_t(IN0_bits);
  thisActor->read_result_in_progress = bitor(lshift(thisActor->read_result_in_progress, 1), ((b) ? (1):(0)));
  thisActor->bits_to_read_count = (thisActor->bits_to_read_count - 1);
  thisActor->bit_count = (thisActor->bit_count + 1);
  if ((thisActor->bits_to_read_count < 0)) {
    dprint2("Read %i bits 0x%x\n", thisActor->bit_count, thisActor->read_result_in_progress);
  
  } else {
    dprint2("In progress read %i bits 0x%x\n", thisActor->bit_count, thisActor->read_result_in_progress);
  }
  ART_ACTION_EXIT(action0, 0);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4118(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// vol_object_layer_identification
ART_ACTION(action1__vol_object_layer_identification, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t b;
  ART_ACTION_ENTER(action1__vol_object_layer_identification, 1);
  b = pinRead_bool_t(IN0_bits);
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, ((b) ? (((VISUAL_OBJECT_LAYER_VERID_LENGTH + VISUAL_OBJECT_LAYER_PRIORITY_LENGTH) + ASPECT_RATIO_INFO_LENGTH)):(ASPECT_RATIO_INFO_LENGTH)));
  thisActor->bit_count = (thisActor->bit_count + 1);
  ART_ACTION_EXIT(action1__vol_object_layer_identification, 1);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4132(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4135(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (RVC_decoder__parser__parseheadersmask_bits(thisActor, RVC_decoder__parser__parseheadersread_result(thisActor), ASPECT_RATIO_INFO_LENGTH) == 15);
    return ret;
  }
}

// vol_aspect.detailed
ART_ACTION(action2__vol_aspect__detailed, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action2__vol_aspect__detailed, 2);
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, 16);
  ART_ACTION_EXIT(action2__vol_aspect__detailed, 2);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4148(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4151(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  bool_t b;
  {
    bool_t ret;
    b = pinPeek_bool_t(IN0_bits, 0);
    ret = b;
    return ret;
  }
}

// vol_control.detailed
ART_ACTION(action3__vol_control__detailed, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t b;
  ART_ACTION_ENTER(action3__vol_control__detailed, 3);
  b = pinRead_bool_t(IN0_bits);
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, 3);
  thisActor->bit_count = (thisActor->bit_count + 1);
  ART_ACTION_EXIT(action3__vol_control__detailed, 3);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4162(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4165(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  bool_t b;
  {
    bool_t ret;
    b = pinPeek_bool_t(IN0_bits, 0);
    ret = b;
    return ret;
  }
}

// vol_vbv.detailed
ART_ACTION(action4__vol_vbv__detailed, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t b;
  ART_ACTION_ENTER(action4__vol_vbv__detailed, 4);
  b = pinRead_bool_t(IN0_bits);
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, 79);
  thisActor->bit_count = (thisActor->bit_count + 1);
  ART_ACTION_EXIT(action4__vol_vbv__detailed, 4);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4192(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// vol_shape
ART_ACTION(action5__vol_shape, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action5__vol_shape, 5);
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, 21);
  ART_ACTION_EXIT(action5__vol_shape, 5);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4204(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// vol_time_inc_res
ART_ACTION(action6__vol_time_inc_res, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t ones;
  int32_t time_inc_res;
  int32_t count;
  ART_ACTION_ENTER(action6__vol_time_inc_res, 6);
  ones = 0;
  time_inc_res = RVC_decoder__parser__parseheadersmask_bits(thisActor, rshift(RVC_decoder__parser__parseheadersread_result(thisActor), 2), TIME_INC_RES_LENGTH);
  count = 0;
  while (((count == 0) || (time_inc_res != 0))) {
    if ((bitand(time_inc_res, 1) == 1)) {
      ones = (ones + 1);
    }
    count = (count + 1);
    time_inc_res = rshift(time_inc_res, 1);
  }
  thisActor->mylog = (((ones > 1)) ? (count):((count - 1)));
  thisActor->mylog = (((thisActor->mylog < 1)) ? (1):(thisActor->mylog));
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, ((((((bitand(RVC_decoder__parser__parseheadersread_result(thisActor), 1) == 1)) ? (thisActor->mylog):(0)) + 1) + 13) + 1));
  ART_ACTION_EXIT(action6__vol_time_inc_res, 6);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4281(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// set_vol_width
ART_ACTION(action7__set_vol_width, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action7__set_vol_width, 7);
  thisActor->vol_width = RVC_decoder__parser__parseheadersmask_bits(thisActor, rshift(RVC_decoder__parser__parseheadersread_result(thisActor), (MARKER_LENGTH + 4)), (VOL_WIDTH_LENGTH - 4));
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, 14);
  ART_ACTION_EXIT(action7__set_vol_width, 7);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4299(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// set_vol_height
ART_ACTION(action8__set_vol_height, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action8__set_vol_height, 8);
  thisActor->vol_height = RVC_decoder__parser__parseheadersmask_bits(thisActor, rshift(RVC_decoder__parser__parseheadersread_result(thisActor), (MARKER_LENGTH + 4)), VOL_HEIGHT_LENGTH);
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, 9);
  ART_ACTION_EXIT(action8__set_vol_height, 8);
}


// byte_align
ART_ACTION(action9__byte_align, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action9__byte_align, 9);
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, (8 - bitand(thisActor->bit_count, 7)));
  ART_ACTION_EXIT(action9__byte_align, 9);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4319(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4322(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = ((RVC_decoder__parser__parseheadersmask_bits(thisActor, RVC_decoder__parser__parseheadersread_result(thisActor), VOP_PREDICTION_LENGTH) == 0) || (RVC_decoder__parser__parseheadersmask_bits(thisActor, RVC_decoder__parser__parseheadersread_result(thisActor), VOP_PREDICTION_LENGTH) == 1));
    return ret;
  }
}

// vop_predict.supported
ART_ACTION(action10__vop_predict__supported, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action10__vop_predict__supported, 10);
  thisActor->prediction_is_IVOP = (RVC_decoder__parser__parseheadersmask_bits(thisActor, RVC_decoder__parser__parseheadersread_result(thisActor), VOP_PREDICTION_LENGTH) == 0);
  thisActor->prediction_is_PVOP = (RVC_decoder__parser__parseheadersmask_bits(thisActor, RVC_decoder__parser__parseheadersread_result(thisActor), VOP_PREDICTION_LENGTH) == 1);
  thisActor->prediction_is_BVOP = (RVC_decoder__parser__parseheadersmask_bits(thisActor, RVC_decoder__parser__parseheadersread_result(thisActor), VOP_PREDICTION_LENGTH) == 2);
  ART_ACTION_EXIT(action10__vop_predict__supported, 10);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4361(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  bool_t b;
  {
    bool_t ret;
    b = pinPeek_bool_t(IN0_bits, 0);
    ret = b;
    return ret;
  }
}

// vop_timebase.one
ART_ACTION(action11__vop_timebase__one, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t b;
  ART_ACTION_ENTER(action11__vop_timebase__one, 11);
  b = pinRead_bool_t(IN0_bits);
  thisActor->bit_count = (thisActor->bit_count + 1);
  ART_ACTION_EXIT(action11__vop_timebase__one, 11);
}


// vop_timebase.zero
ART_ACTION(action12__vop_timebase__zero, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t b;
  ART_ACTION_ENTER(action12__vop_timebase__zero, 12);
  b = pinRead_bool_t(IN0_bits);
  thisActor->bit_count = (thisActor->bit_count + 1);
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, ((1 + thisActor->mylog) + 1));
  ART_ACTION_EXIT(action12__vop_timebase__zero, 12);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4379(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4382(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  bool_t b;
  {
    bool_t ret;
    b = pinPeek_bool_t(IN0_bits, 0);
    ret = (!(b));
    return ret;
  }
}

// vop_coding.uncoded
ART_ACTION(action13__vop_coding__uncoded, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t b;
  ART_ACTION_ENTER(action13__vop_coding__uncoded, 13);
  b = pinRead_bool_t(IN0_bits);
  thisActor->comp = 0;
  thisActor->bit_count = (thisActor->bit_count + 1);
  ART_ACTION_EXIT(action13__vop_coding__uncoded, 13);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4392(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// vop_coding.coded
ART_ACTION(action14__vop_coding__coded, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t b;
  ART_ACTION_ENTER(action14__vop_coding__coded, 14);
  b = pinRead_bool_t(IN0_bits);
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, (((!(thisActor->prediction_is_IVOP))) ? ((((1 + INTRA_DC_VLC_THR_LENGTH) + BITS_QUANT) + VOP_FCODE_FOR_LENGTH)):((INTRA_DC_VLC_THR_LENGTH + BITS_QUANT))));
  thisActor->bit_count = (thisActor->bit_count + 1);
  ART_ACTION_EXIT(action14__vop_coding__coded, 14);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4411(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// send_new_vop_cmd
ART_ACTION(action15__send_new_vop_cmd, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t cmd;
  bool_t round;
  ART_ACTION_ENTER(action15__send_new_vop_cmd, 15);
  cmd = bitor(NEWVOP, ((thisActor->prediction_is_IVOP) ? (INTRA):(INTER)));
  round = 0;
  if ((!(thisActor->prediction_is_IVOP))) {
    round = (bitand(rshift(RVC_decoder__parser__parseheadersread_result(thisActor), ((INTRA_DC_VLC_THR_LENGTH + BITS_QUANT) + VOP_FCODE_FOR_LENGTH)), 1) == 1);
    thisActor->intra_dc_vlc_thr = intra_dc_threshold_table[bitand(rshift(RVC_decoder__parser__parseheadersread_result(thisActor), (BITS_QUANT + VOP_FCODE_FOR_LENGTH)), 7)];
    thisActor->vop_quant = bitand(rshift(RVC_decoder__parser__parseheadersread_result(thisActor), VOP_FCODE_FOR_LENGTH), BITS_QUANT_MASK);
    thisActor->fcode = bitand(RVC_decoder__parser__parseheadersread_result(thisActor), VOP_FCODE_FOR_MASK);
  
  } else {
    thisActor->intra_dc_vlc_thr = intra_dc_threshold_table[bitand(rshift(RVC_decoder__parser__parseheadersread_result(thisActor), BITS_QUANT), 7)];
    thisActor->vop_quant = bitand(RVC_decoder__parser__parseheadersread_result(thisActor), BITS_QUANT_MASK);
    thisActor->fcode = 0;
  }
  thisActor->prev_quant = thisActor->vop_quant;
  cmd = bitor(cmd, ((round) ? (ROUND_TYPE):(0)));
  cmd = bitor(cmd, bitand(lshift(thisActor->fcode, FCODE_SHIFT), FCODE_MASK));
  pinWrite_int32_t(OUT0_BTYPE, cmd);
  ART_ACTION_EXIT(action15__send_new_vop_cmd, 15);
}


// send_new_vop_width
ART_ACTION(action16__send_new_vop_width, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action16__send_new_vop_width, 16);
  pinWrite_int32_t(OUT0_BTYPE, thisActor->vol_width);
  pinWrite_int32_t(OUT5_WIDTH, thisActor->vol_width);
  ART_ACTION_EXIT(action16__send_new_vop_width, 16);
}


// send_new_vop_height
ART_ACTION(action17__send_new_vop_height, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action17__send_new_vop_height, 17);
  pinWrite_int32_t(OUT0_BTYPE, thisActor->vol_height);
  pinWrite_int32_t(OUT6_HEIGHT, thisActor->vol_height);
  ART_ACTION_EXIT(action17__send_new_vop_height, 17);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4515(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->mby == thisActor->vol_height);
    return ret;
  }
}

// mb_done
ART_ACTION(action18__mb_done, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action18__mb_done, 18);
  ART_ACTION_EXIT(action18__mb_done, 18);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4519(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = thisActor->prediction_is_IVOP;
    return ret;
  }
}

// get_mcbpc.ivop
ART_ACTION(action19__get_mcbpc__ivop, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action19__get_mcbpc__ivop, 19);
  RVC_decoder__parser__parseheadersstart_vld_engine(thisActor, 0);
  ART_ACTION_EXIT(action19__get_mcbpc__ivop, 19);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4524(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (!(thisActor->prediction_is_IVOP));
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4527(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  bool_t b;
  {
    bool_t ret;
    b = pinPeek_bool_t(IN0_bits, 0);
    ret = (!(b));
    return ret;
  }
}

// get_mcbpc.pvop
ART_ACTION(action20__get_mcbpc__pvop, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t b;
  ART_ACTION_ENTER(action20__get_mcbpc__pvop, 20);
  b = pinRead_bool_t(IN0_bits);
  RVC_decoder__parser__parseheadersstart_vld_engine(thisActor, 16);
  thisActor->bit_count = (thisActor->bit_count + 1);
  ART_ACTION_EXIT(action20__get_mcbpc__pvop, 20);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4537(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (!(thisActor->prediction_is_IVOP));
    return ret;
  }
}

// mcbpc_pvop_uncoded
ART_ACTION(action21__mcbpc_pvop_uncoded, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t b;
  ART_ACTION_ENTER(action21__mcbpc_pvop_uncoded, 21);
  b = pinRead_bool_t(IN0_bits);
  RVC_decoder__parser__parseheadersnext_mbxy(thisActor);
  thisActor->bit_count = (thisActor->bit_count + 1);
  pinWrite_int32_t(OUT0_BTYPE, 512);
  pinWrite_int32_t(OUT7_QP, thisActor->vop_quant);
  ART_ACTION_EXIT(action21__mcbpc_pvop_uncoded, 21);
}


// mcbpc_pvop_uncoded1
ART_ACTION(action22__mcbpc_pvop_uncoded1, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action22__mcbpc_pvop_uncoded1, 22);
  pinWrite_int32_t(OUT0_BTYPE, 512);
  pinWrite_int32_t(OUT7_QP, thisActor->vop_quant);
  ART_ACTION_EXIT(action22__mcbpc_pvop_uncoded1, 22);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4559(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->vld_codeword, 3) == 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4562(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(RVC_decoder__parser__parseheadersvld_result(thisActor), 7) != 3);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4570(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(RVC_decoder__parser__parseheadersvld_result(thisActor), 7) != 4);
    return ret;
  }
}

// get_mbtype.noac
ART_ACTION(action23__get_mbtype__noac, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t mcbpc;
  int32_t type1;
  ART_ACTION_ENTER(action23__get_mbtype__noac, 23);
  mcbpc = rshift(thisActor->vld_codeword, 2);
  type1 = bitand(mcbpc, 7);
  thisActor->btype_is_INTRA = (type1 >= 3);
  thisActor->btype_is_Q = ((type1 == 4) || (type1 == 1));
  thisActor->fourmvflag = (type1 == 2);
  thisActor->cbpc = bitand(rshift(mcbpc, 4), 3);
  thisActor->acpredflag = 0;
  RVC_decoder__parser__parseheadersstart_vld_engine(thisActor, 58);
  ART_ACTION_EXIT(action23__get_mbtype__noac, 23);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4610(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->vld_codeword, 3) == 0);
    return ret;
  }
}

// get_mbtype.ac
ART_ACTION(action24__get_mbtype__ac, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t b;
  int32_t mcbpc;
  int32_t type1;
  ART_ACTION_ENTER(action24__get_mbtype__ac, 24);
  b = pinRead_bool_t(IN0_bits);
  mcbpc = rshift(thisActor->vld_codeword, 2);
  type1 = bitand(mcbpc, 7);
  thisActor->btype_is_INTRA = 1;
  thisActor->btype_is_Q = ((type1 == 4) || (type1 == 1));
  thisActor->cbpc = bitand(rshift(mcbpc, 4), 3);
  thisActor->acpredflag = b;
  thisActor->bit_count = (thisActor->bit_count + 1);
  RVC_decoder__parser__parseheadersstart_vld_engine(thisActor, 58);
  ART_ACTION_EXIT(action24__get_mbtype__ac, 24);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4641(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->vld_codeword, 3) == 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4644(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (!(thisActor->btype_is_INTRA));
    return ret;
  }
}

// final_cbpy_inter
ART_ACTION(action25__final_cbpy_inter, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t cbpy;
  ART_ACTION_ENTER(action25__final_cbpy_inter, 25);
  cbpy = (15 - rshift(thisActor->vld_codeword, 2));
  thisActor->comp = 0;
  thisActor->mvcomp = 0;
  thisActor->cbp = bitor(lshift(cbpy, 2), thisActor->cbpc);
  if (thisActor->btype_is_Q) {
    RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, 2);
  }
  ART_ACTION_EXIT(action25__final_cbpy_inter, 25);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4665(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->vld_codeword, 3) == 0);
    return ret;
  }
}

// final_cbpy_intra
ART_ACTION(action26__final_cbpy_intra, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t cbpy;
  ART_ACTION_ENTER(action26__final_cbpy_intra, 26);
  cbpy = rshift(thisActor->vld_codeword, 2);
  thisActor->comp = 0;
  thisActor->cbp = bitor(lshift(cbpy, 2), thisActor->cbpc);
  if (thisActor->btype_is_Q) {
    RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, 2);
  }
  ART_ACTION_EXIT(action26__final_cbpy_intra, 26);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4683(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// final_dquant
ART_ACTION(action27__final_dquant, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action27__final_dquant, 27);
  if (thisActor->btype_is_Q) {
    thisActor->prev_quant = thisActor->vop_quant;
    thisActor->vop_quant = (thisActor->vop_quant + dquant_table[RVC_decoder__parser__parseheadersread_result(thisActor)]);
    if ((thisActor->vop_quant > 31)) {
      thisActor->vop_quant = 31;
    }
    if ((thisActor->vop_quant < 1)) {
      thisActor->vop_quant = 1;
    }
  }
  ART_ACTION_EXIT(action27__final_dquant, 27);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4707(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->comp == 6);
    return ret;
  }
}

// mb_dispatch_done
ART_ACTION(action28__mb_dispatch_done, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action28__mb_dispatch_done, 28);
  RVC_decoder__parser__parseheadersnext_mbxy(thisActor);
  ART_ACTION_EXIT(action28__mb_dispatch_done, 28);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4711(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = thisActor->btype_is_INTRA;
    return ret;
  }
}

// mb_dispatch_intra
ART_ACTION(action29__mb_dispatch_intra, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t cmd;
  ART_ACTION_ENTER(action29__mb_dispatch_intra, 29);
  cmd = 1024;
  thisActor->ac_coded = (bitand(thisActor->cbp, lshift(1, (5 - thisActor->comp))) != 0);
  cmd = bitor(cmd, ((thisActor->ac_coded) ? (ACCODED):(0)));
  cmd = bitor(cmd, ((thisActor->acpredflag) ? (ACPRED):(0)));
  pinWrite_int32_t(OUT0_BTYPE, cmd);
  pinWrite_int32_t(OUT7_QP, thisActor->vop_quant);
  ART_ACTION_EXIT(action29__mb_dispatch_intra, 29);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4749(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->cbp, lshift(1, (5 - thisActor->comp))) == 0);
    return ret;
  }
}

// mb_dispatch_inter_no_ac
ART_ACTION(action30__mb_dispatch_inter_no_ac, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t U__21;
  ART_ACTION_ENTER(action30__mb_dispatch_inter_no_ac, 30);
  thisActor->ac_coded = 0;
  thisActor->comp = (thisActor->comp + 1);
  U__21 = bitor(INTER, bitor(MOTION, ((thisActor->fourmvflag) ? (FOURMV):(0))));
  pinWrite_int32_t(OUT0_BTYPE, U__21);
  pinWrite_int32_t(OUT7_QP, thisActor->vop_quant);
  ART_ACTION_EXIT(action30__mb_dispatch_inter_no_ac, 30);
}


// mb_dispatch_inter_ac_coded
ART_ACTION(action31__mb_dispatch_inter_ac_coded, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t U__22;
  ART_ACTION_ENTER(action31__mb_dispatch_inter_ac_coded, 31);
  thisActor->ac_coded = 1;
  U__22 = bitor(bitor(INTER, ACCODED), bitor(MOTION, ((thisActor->fourmvflag) ? (FOURMV):(0))));
  pinWrite_int32_t(OUT0_BTYPE, U__22);
  pinWrite_int32_t(OUT7_QP, thisActor->vop_quant);
  ART_ACTION_EXIT(action31__mb_dispatch_inter_ac_coded, 31);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4807(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = thisActor->btype_is_INTRA;
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4809(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->prev_quant < thisActor->intra_dc_vlc_thr);
    return ret;
  }
}

// vld_start_intra.dc
ART_ACTION(action32__vld_start_intra__dc, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action32__vld_start_intra__dc, 32);
  RVC_decoder__parser__parseheadersstart_vld_engine(thisActor, (((thisActor->comp < 4)) ? (DCBITS_Y_START_INDEX):(DCBITS_UV_START_INDEX)));
  thisActor->b_last = 0;
  ART_ACTION_EXIT(action32__vld_start_intra__dc, 32);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4820(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = thisActor->btype_is_INTRA;
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4822(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->prev_quant >= thisActor->intra_dc_vlc_thr);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4826(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = thisActor->ac_coded;
    return ret;
  }
}

// vld_start_intra.nodc.ac_coded
ART_ACTION(action33__vld_start_intra__nodc__ac_coded, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action33__vld_start_intra__nodc__ac_coded, 33);
  thisActor->b_last = 0;
  ART_ACTION_EXIT(action33__vld_start_intra__nodc__ac_coded, 33);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4829(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = thisActor->btype_is_INTRA;
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4831(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->prev_quant >= thisActor->intra_dc_vlc_thr);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4835(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (!(thisActor->ac_coded));
    return ret;
  }
}

// vld_start_intra.nodc.no_ac_coded
ART_ACTION(action34__vld_start_intra__nodc__no_ac_coded, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t U__23;
  int32_t U__24;
  bool_t U__25;
  ART_ACTION_ENTER(action34__vld_start_intra__nodc__no_ac_coded, 34);
  thisActor->b_last = 1;
  U__23 = 0;
  pinWrite_int32_t(OUT2_RUN, U__23);
  U__24 = 0;
  pinWrite_int32_t(OUT3_VALUE, U__24);
  U__25 = 1;
  pinWrite_bool_t(OUT4_LAST, U__25);
  ART_ACTION_EXIT(action34__vld_start_intra__nodc__no_ac_coded, 34);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4853(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = thisActor->ac_coded;
    return ret;
  }
}

// vld_start_inter.ac_coded
ART_ACTION(action35__vld_start_inter__ac_coded, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action35__vld_start_inter__ac_coded, 35);
  thisActor->b_last = 0;
  ART_ACTION_EXIT(action35__vld_start_inter__ac_coded, 35);
}


// vld_start_inter.not_ac_coded
ART_ACTION(action36__vld_start_inter__not_ac_coded, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t U__26;
  int32_t U__27;
  bool_t U__28;
  ART_ACTION_ENTER(action36__vld_start_inter__not_ac_coded, 36);
  thisActor->b_last = 1;
  U__26 = 0;
  pinWrite_int32_t(OUT2_RUN, U__26);
  U__27 = 0;
  pinWrite_int32_t(OUT3_VALUE, U__27);
  U__28 = 1;
  pinWrite_bool_t(OUT4_LAST, U__28);
  ART_ACTION_EXIT(action36__vld_start_inter__not_ac_coded, 36);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4871(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->vld_codeword, 3) == 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4874(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (rshift(thisActor->vld_codeword, 2) == 0);
    return ret;
  }
}

// get_dc_bits.none
ART_ACTION(action37__get_dc_bits__none, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t U__29;
  int32_t U__30;
  bool_t U__31;
  ART_ACTION_ENTER(action37__get_dc_bits__none, 37);
  thisActor->b_last = (!(thisActor->ac_coded));
  U__29 = 0;
  pinWrite_int32_t(OUT2_RUN, U__29);
  U__30 = 0;
  pinWrite_int32_t(OUT3_VALUE, U__30);
  U__31 = (!(thisActor->ac_coded));
  pinWrite_bool_t(OUT4_LAST, U__31);
  ART_ACTION_EXIT(action37__get_dc_bits__none, 37);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4896(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->vld_codeword, 3) == 0);
    return ret;
  }
}

// get_dc_bits.some
ART_ACTION(action38__get_dc_bits__some, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action38__get_dc_bits__some, 38);
  thisActor->dc_bits = rshift(thisActor->vld_codeword, 2);
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, thisActor->dc_bits);
  ART_ACTION_EXIT(action38__get_dc_bits__some, 38);
}


// dc_bits_shift
ART_ACTION(action39__dc_bits_shift, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t count;
  int32_t shift;
  ART_ACTION_ENTER(action39__dc_bits_shift, 39);
  count = thisActor->dc_bits;
  shift = 1;
  while ((count > 1)) {
    shift = lshift(shift, 1);
    count = (count - 1);
  }
  thisActor->msb_result = shift;
  ART_ACTION_EXIT(action39__dc_bits_shift, 39);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4920(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// get_dc
ART_ACTION(action40__get_dc, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t v;
  int32_t U__32;
  bool_t U__33;
  ART_ACTION_ENTER(action40__get_dc, 40);
  v = thisActor->read_result_in_progress;
  if ((bitand(v, thisActor->msb_result) == 0)) {
    v = ((v + 1) - lshift(thisActor->msb_result, 1));
  }
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, (((thisActor->dc_bits > 8)) ? (MARKER_LENGTH):(0)));
  thisActor->b_last = (!(thisActor->ac_coded));
  U__32 = 0;
  pinWrite_int32_t(OUT2_RUN, U__32);
  pinWrite_int32_t(OUT3_VALUE, v);
  U__33 = (!(thisActor->ac_coded));
  pinWrite_bool_t(OUT4_LAST, U__33);
  ART_ACTION_EXIT(action40__get_dc, 40);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4964(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4967(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = thisActor->b_last;
    return ret;
  }
}

// block_done
ART_ACTION(action41__block_done, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action41__block_done, 41);
  thisActor->comp = (thisActor->comp + 1);
  ART_ACTION_EXIT(action41__block_done, 41);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4972(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// dct_coeff
ART_ACTION(action42__dct_coeff, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action42__dct_coeff, 42);
  RVC_decoder__parser__parseheadersstart_vld_engine(thisActor, ((thisActor->btype_is_INTRA) ? (COEFF_INTRA_START_INDEX):(COEFF_INTER_START_INDEX)));
  ART_ACTION_EXIT(action42__dct_coeff, 42);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4981(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->vld_codeword, 3) == 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d4984(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (rshift(thisActor->vld_codeword, 2) != 7167);
    return ret;
  }
}

// vld_code
ART_ACTION(action43__vld_code, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t sign;
  bool_t last;
  int32_t run;
  int32_t level;
  int32_t val;
  int32_t U__34;
  ART_ACTION_ENTER(action43__vld_code, 43);
  sign = pinRead_bool_t(IN0_bits);
  val = rshift(thisActor->vld_codeword, 2);
  run = ((thisActor->btype_is_INTRA) ? (bitand(rshift(val, 8), 255)):(bitand(rshift(val, 4), 255)));
  last = ((thisActor->btype_is_INTRA) ? ((bitand(rshift(val, 16), 1) != 0)):((bitand(rshift(val, 12), 1) != 0)));
  level = ((thisActor->btype_is_INTRA) ? (bitand(val, 255)):(bitand(val, 15)));
  thisActor->b_last = last;
  thisActor->bit_count = (thisActor->bit_count + 1);
  U__34 = ((sign) ? ((-(level))):(level));
  pinWrite_int32_t(OUT3_VALUE, U__34);
  pinWrite_int32_t(OUT2_RUN, run);
  pinWrite_bool_t(OUT4_LAST, last);
  ART_ACTION_EXIT(action43__vld_code, 43);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5064(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->vld_codeword, 3) == 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5067(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  bool_t level_offset;
  {
    bool_t ret;
    level_offset = pinPeek_bool_t(IN0_bits, 0);
    ret = (!(level_offset));
    return ret;
  }
}

// vld_level
ART_ACTION(action44__vld_level, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t level_offset;
  ART_ACTION_ENTER(action44__vld_level, 44);
  level_offset = pinRead_bool_t(IN0_bits);
  thisActor->bit_count = (thisActor->bit_count + 1);
  RVC_decoder__parser__parseheadersstart_vld_engine(thisActor, ((thisActor->btype_is_INTRA) ? (COEFF_INTRA_START_INDEX):(COEFF_INTER_START_INDEX)));
  ART_ACTION_EXIT(action44__vld_level, 44);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5080(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->vld_codeword, 3) == 0);
    return ret;
  }
}

// vld_run_or_direct
ART_ACTION(action45__vld_run_or_direct, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t level_offset;
  ART_ACTION_ENTER(action45__vld_run_or_direct, 45);
  level_offset = pinRead_bool_t(IN0_bits);
  thisActor->bit_count = (thisActor->bit_count + 1);
  ART_ACTION_EXIT(action45__vld_run_or_direct, 45);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5088(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  bool_t run_offset;
  {
    bool_t ret;
    run_offset = pinPeek_bool_t(IN0_bits, 0);
    ret = (!(run_offset));
    return ret;
  }
}

// vld_run
ART_ACTION(action46__vld_run, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t run_offset;
  ART_ACTION_ENTER(action46__vld_run, 46);
  run_offset = pinRead_bool_t(IN0_bits);
  thisActor->bit_count = (thisActor->bit_count + 1);
  RVC_decoder__parser__parseheadersstart_vld_engine(thisActor, ((thisActor->btype_is_INTRA) ? (COEFF_INTRA_START_INDEX):(COEFF_INTER_START_INDEX)));
  ART_ACTION_EXIT(action46__vld_run, 46);
}


// vld_direct_read
ART_ACTION(action47__vld_direct_read, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t run_offset;
  ART_ACTION_ENTER(action47__vld_direct_read, 47);
  run_offset = pinRead_bool_t(IN0_bits);
  thisActor->bit_count = (thisActor->bit_count + 1);
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, 21);
  ART_ACTION_EXIT(action47__vld_direct_read, 47);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5113(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// vld_direct
ART_ACTION(action48__vld_direct, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t run;
  bool_t last;
  bool_t sign;
  int32_t level;
  int32_t U__35;
  ART_ACTION_ENTER(action48__vld_direct, 48);
  last = (bitand(rshift(RVC_decoder__parser__parseheadersread_result(thisActor), (((RUN_LENGTH + MARKER_LENGTH) + LEVEL_LENGTH) + MARKER_LENGTH)), 1) != 0);
  run = bitand(rshift(RVC_decoder__parser__parseheadersread_result(thisActor), ((MARKER_LENGTH + LEVEL_LENGTH) + MARKER_LENGTH)), RUN_MASK);
  level = bitand(rshift(RVC_decoder__parser__parseheadersread_result(thisActor), MARKER_LENGTH), LEVEL_MASK);
  if ((level >= 2048)) {
    sign = 1;
    level = (4096 - level);
  
  } else {
    sign = 0;
  }
  thisActor->b_last = last;
  U__35 = ((sign) ? ((-(level))):(level));
  pinWrite_int32_t(OUT3_VALUE, U__35);
  pinWrite_int32_t(OUT2_RUN, run);
  pinWrite_bool_t(OUT4_LAST, last);
  ART_ACTION_EXIT(action48__vld_direct, 48);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5183(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->vld_codeword, 3) == 0);
    return ret;
  }
}

// do_level_lookup
ART_ACTION(action49__do_level_lookup, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t val;
  ART_ACTION_ENTER(action49__do_level_lookup, 49);
  val = rshift(thisActor->vld_codeword, 2);
  thisActor->level_lookup_inter = RVC_decoder__parser__parseheadersinter_max_level(thisActor, (bitand(rshift(val, 12), 1) != 0), bitand(rshift(val, 4), 255));
  thisActor->level_lookup_intra = RVC_decoder__parser__parseheadersintra_max_level(thisActor, (bitand(rshift(val, 16), 1) != 0), bitand(rshift(val, 8), 255));
  ART_ACTION_EXIT(action49__do_level_lookup, 49);
}


// vld_level_lookup
ART_ACTION(action50__vld_level_lookup, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t sign;
  bool_t last;
  int32_t val;
  int32_t run;
  int32_t level;
  int32_t U__36;
  ART_ACTION_ENTER(action50__vld_level_lookup, 50);
  sign = pinRead_bool_t(IN0_bits);
  val = rshift(thisActor->vld_codeword, 2);
  run = ((thisActor->btype_is_INTRA) ? (bitand(rshift(val, 8), 255)):(bitand(rshift(val, 4), 255)));
  last = ((thisActor->btype_is_INTRA) ? ((bitand(rshift(val, 16), 1) != 0)):((bitand(rshift(val, 12), 1) != 0)));
  level = ((thisActor->btype_is_INTRA) ? ((bitand(val, 255) + thisActor->level_lookup_intra)):((bitand(val, 15) + thisActor->level_lookup_inter)));
  thisActor->b_last = last;
  thisActor->bit_count = (thisActor->bit_count + 1);
  U__36 = ((sign) ? ((-(level))):(level));
  pinWrite_int32_t(OUT3_VALUE, U__36);
  pinWrite_int32_t(OUT2_RUN, run);
  pinWrite_bool_t(OUT4_LAST, last);
  ART_ACTION_EXIT(action50__vld_level_lookup, 50);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5309(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->vld_codeword, 3) == 0);
    return ret;
  }
}

// do_run_lookup
ART_ACTION(action51__do_run_lookup, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t val;
  ART_ACTION_ENTER(action51__do_run_lookup, 51);
  val = rshift(thisActor->vld_codeword, 2);
  thisActor->run_lookup_inter = RVC_decoder__parser__parseheadersinter_max_run(thisActor, (bitand(rshift(val, 12), 1) != 0), bitand(val, 15));
  thisActor->run_lookup_intra = RVC_decoder__parser__parseheadersintra_max_run(thisActor, (bitand(rshift(val, 16), 1) != 0), bitand(val, 255));
  ART_ACTION_EXIT(action51__do_run_lookup, 51);
}


// vld_run_lookup
ART_ACTION(action52__vld_run_lookup, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t sign;
  int32_t level;
  bool_t last;
  int32_t val;
  int32_t run;
  int32_t U__37;
  ART_ACTION_ENTER(action52__vld_run_lookup, 52);
  sign = pinRead_bool_t(IN0_bits);
  val = rshift(thisActor->vld_codeword, 2);
  last = ((thisActor->btype_is_INTRA) ? ((bitand(rshift(val, 16), 1) != 0)):((bitand(rshift(val, 12), 1) != 0)));
  level = ((thisActor->btype_is_INTRA) ? (bitand(val, 255)):(bitand(val, 15)));
  run = (((thisActor->btype_is_INTRA) ? ((bitand(rshift(val, 8), 255) + thisActor->run_lookup_intra)):((bitand(rshift(val, 4), 255) + thisActor->run_lookup_inter))) + 1);
  thisActor->b_last = last;
  thisActor->bit_count = (thisActor->bit_count + 1);
  U__37 = ((sign) ? ((-(level))):(level));
  pinWrite_int32_t(OUT3_VALUE, U__37);
  pinWrite_int32_t(OUT2_RUN, run);
  pinWrite_bool_t(OUT4_LAST, last);
  ART_ACTION_EXIT(action52__vld_run_lookup, 52);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5431(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = ((thisActor->mvcomp == 4) || ((thisActor->mvcomp == 1) && (!(thisActor->fourmvflag))));
    return ret;
  }
}

// mvcode_done
ART_ACTION(action53__mvcode_done, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action53__mvcode_done, 53);
  ART_ACTION_EXIT(action53__mvcode_done, 53);
}


// mvcode
ART_ACTION(action54__mvcode, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action54__mvcode, 54);
  RVC_decoder__parser__parseheadersstart_vld_engine(thisActor, 616);
  ART_ACTION_EXIT(action54__mvcode, 54);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5443(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->vld_codeword, 3) == 0);
    return ret;
  }
}

// mag_x
ART_ACTION(action55__mag_x, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t mvval;
  ART_ACTION_ENTER(action55__mag_x, 55);
  mvval = rshift(thisActor->vld_codeword, 2);
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, ((((thisActor->fcode <= 1) || (mvval == 0))) ? (0):((thisActor->fcode - 1))));
  pinWrite_int32_t(OUT1_MV, mvval);
  ART_ACTION_EXIT(action55__mag_x, 55);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5465(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// get_residual_x
ART_ACTION(action56__get_residual_x, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t U__38;
  ART_ACTION_ENTER(action56__get_residual_x, 56);
  U__38 = thisActor->read_result_in_progress;
  pinWrite_int32_t(OUT1_MV, U__38);
  ART_ACTION_EXIT(action56__get_residual_x, 56);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5474(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->vld_codeword, 3) == 0);
    return ret;
  }
}

// mag_y
ART_ACTION(action57__mag_y, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t mvval;
  ART_ACTION_ENTER(action57__mag_y, 57);
  mvval = rshift(thisActor->vld_codeword, 2);
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, ((((thisActor->fcode <= 1) || (mvval == 0))) ? (0):((thisActor->fcode - 1))));
  pinWrite_int32_t(OUT1_MV, mvval);
  ART_ACTION_EXIT(action57__mag_y, 57);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5496(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// get_residual_y
ART_ACTION(action58__get_residual_y, ActorInstance_RVC_decoder__parser__parseheaders) {
  int32_t U__39;
  ART_ACTION_ENTER(action58__get_residual_y, 58);
  thisActor->mvcomp = (thisActor->mvcomp + 1);
  U__39 = thisActor->read_result_in_progress;
  pinWrite_int32_t(OUT1_MV, U__39);
  ART_ACTION_EXIT(action58__get_residual_y, 58);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5510(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->vld_codeword, 3) == 2);
    return ret;
  }
}

// 
ART_ACTION(action59, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t b;
  ART_ACTION_ENTER(action59, 59);
  b = pinRead_bool_t(IN0_bits);
  thisActor->vld_codeword = vld_table[(thisActor->vld_index + ((b) ? (1):(0)))];
  thisActor->vld_index = rshift(thisActor->vld_codeword, 2);
  thisActor->bit_count = (thisActor->bit_count + 1);
  ART_ACTION_EXIT(action59, 59);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5531(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(thisActor->vld_codeword, 1) == 1);
    return ret;
  }
}

// do_vld_failure
ART_ACTION(action60__do_vld_failure, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action60__do_vld_failure, 60);
  ART_ACTION_EXIT(action60__do_vld_failure, 60);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5534(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// generic_done
ART_ACTION(action61__generic_done, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action61__generic_done, 61);
  ART_ACTION_EXIT(action61__generic_done, 61);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5539(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// generic_done_with_bitread
ART_ACTION(action62__generic_done_with_bitread, ActorInstance_RVC_decoder__parser__parseheaders) {
  bool_t b;
  ART_ACTION_ENTER(action62__generic_done_with_bitread, 62);
  b = pinRead_bool_t(IN0_bits);
  thisActor->bit_count = (thisActor->bit_count + 1);
  ART_ACTION_EXIT(action62__generic_done_with_bitread, 62);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5545(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5548(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(RVC_decoder__parser__parseheadersread_result(thisActor), 255) == 0);
    return ret;
  }
}

// test_zero_byte
ART_ACTION(action63__test_zero_byte, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action63__test_zero_byte, 63);
  ART_ACTION_EXIT(action63__test_zero_byte, 63);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5556(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5559(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(RVC_decoder__parser__parseheadersread_result(thisActor), 254) == 0);
    return ret;
  }
}

// test_vo_byte
ART_ACTION(action64__test_vo_byte, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action64__test_vo_byte, 64);
  ART_ACTION_EXIT(action64__test_vo_byte, 64);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5567(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5570(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->read_result_in_progress == 32);
    return ret;
  }
}

// test_vol_byte
ART_ACTION(action65__test_vol_byte, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action65__test_vol_byte, 65);
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, 9);
  ART_ACTION_EXIT(action65__test_vol_byte, 65);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5578(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5581(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->read_result_in_progress == 182);
    return ret;
  }
}

// test_vop_byte
ART_ACTION(action66__test_vop_byte, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action66__test_vop_byte, 66);
  thisActor->mbx = 0;
  thisActor->mby = 0;
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, 2);
  ART_ACTION_EXIT(action66__test_vop_byte, 66);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5589(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5592(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (bitand(RVC_decoder__parser__parseheadersread_result(thisActor), 255) == 1);
    return ret;
  }
}

// test_one_byte
ART_ACTION(action67__test_one_byte, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action67__test_one_byte, 67);
  ART_ACTION_EXIT(action67__test_one_byte, 67);
}

bool_t RVC_decoder__parser__parseheaders__DOLLAR__d5600(art_action_context_t *context, ActorInstance_RVC_decoder__parser__parseheaders *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->bits_to_read_count < 0);
    return ret;
  }
}

// request_byte
ART_ACTION(action68__request_byte, ActorInstance_RVC_decoder__parser__parseheaders) {
  ART_ACTION_ENTER(action68__request_byte, 68);
  RVC_decoder__parser__parseheadersset_bits_to_read(thisActor, 8);
  ART_ACTION_EXIT(action68__request_byte, 68);
}

#define ActorInstance_RVC_decoder__parser__parseheaders__vol_object_ID 0
#define ActorInstance_RVC_decoder__parser__parseheaders__vol_aspect_ID 1
#define ActorInstance_RVC_decoder__parser__parseheaders__vol_control_ID 2
#define ActorInstance_RVC_decoder__parser__parseheaders__vol_vbv_ID 3
#define ActorInstance_RVC_decoder__parser__parseheaders__vol_shape_ID 4
#define ActorInstance_RVC_decoder__parser__parseheaders__vol_time_inc_res_ID 5
#define ActorInstance_RVC_decoder__parser__parseheaders__vol_width_ID 6
#define ActorInstance_RVC_decoder__parser__parseheaders__vol_height_ID 7
#define ActorInstance_RVC_decoder__parser__parseheaders__vol_misc_ID 8
#define ActorInstance_RVC_decoder__parser__parseheaders__stuck_ID 9
#define ActorInstance_RVC_decoder__parser__parseheaders__vop_predict_ID 10
#define ActorInstance_RVC_decoder__parser__parseheaders__vop_timebase_ID 11
#define ActorInstance_RVC_decoder__parser__parseheaders__vop_coding_ID 12
#define ActorInstance_RVC_decoder__parser__parseheaders__send_new_vop_info_ID 13
#define ActorInstance_RVC_decoder__parser__parseheaders__send_new_vop_width_ID 14
#define ActorInstance_RVC_decoder__parser__parseheaders__send_new_vop_height_ID 15
#define ActorInstance_RVC_decoder__parser__parseheaders__mb_ID 16
#define ActorInstance_RVC_decoder__parser__parseheaders__pvop_uncoded1_ID 17
#define ActorInstance_RVC_decoder__parser__parseheaders__pvop_uncoded2_ID 18
#define ActorInstance_RVC_decoder__parser__parseheaders__pvop_uncoded3_ID 19
#define ActorInstance_RVC_decoder__parser__parseheaders__pvop_uncoded4_ID 20
#define ActorInstance_RVC_decoder__parser__parseheaders__pvop_uncoded5_ID 21
#define ActorInstance_RVC_decoder__parser__parseheaders__get_mbtype_ID 22
#define ActorInstance_RVC_decoder__parser__parseheaders__final_cbpy_ID 23
#define ActorInstance_RVC_decoder__parser__parseheaders__dquant_intra_ID 24
#define ActorInstance_RVC_decoder__parser__parseheaders__block_ID 25
#define ActorInstance_RVC_decoder__parser__parseheaders__dquant_inter_ID 26
#define ActorInstance_RVC_decoder__parser__parseheaders__mv_ID 27
#define ActorInstance_RVC_decoder__parser__parseheaders__texture_ID 28
#define ActorInstance_RVC_decoder__parser__parseheaders__get_dc_bits_ID 29
#define ActorInstance_RVC_decoder__parser__parseheaders__texac_ID 30
#define ActorInstance_RVC_decoder__parser__parseheaders__get_dc_ID 31
#define ActorInstance_RVC_decoder__parser__parseheaders__get_dc_a_ID 32
#define ActorInstance_RVC_decoder__parser__parseheaders__vld1_ID 33
#define ActorInstance_RVC_decoder__parser__parseheaders__vld4_ID 34
#define ActorInstance_RVC_decoder__parser__parseheaders__vld7_ID 35
#define ActorInstance_RVC_decoder__parser__parseheaders__vld6_ID 36
#define ActorInstance_RVC_decoder__parser__parseheaders__vld_direct_ID 37
#define ActorInstance_RVC_decoder__parser__parseheaders__vld4a_ID 38
#define ActorInstance_RVC_decoder__parser__parseheaders__vld6a_ID 39
#define ActorInstance_RVC_decoder__parser__parseheaders__mag_x_ID 40
#define ActorInstance_RVC_decoder__parser__parseheaders__get_residual_x_ID 41
#define ActorInstance_RVC_decoder__parser__parseheaders__mv_y_ID 42
#define ActorInstance_RVC_decoder__parser__parseheaders__mag_y_ID 43
#define ActorInstance_RVC_decoder__parser__parseheaders__get_residual_y_ID 44
#define ActorInstance_RVC_decoder__parser__parseheaders__stuck_1a_ID 45
#define ActorInstance_RVC_decoder__parser__parseheaders__stuck_1b_ID 46
#define ActorInstance_RVC_decoder__parser__parseheaders__stuck_2a_ID 47
#define ActorInstance_RVC_decoder__parser__parseheaders__stuck_2b_ID 48
#define ActorInstance_RVC_decoder__parser__parseheaders__stuck_3a_ID 49
#define ActorInstance_RVC_decoder__parser__parseheaders__stuck_3b_ID 50
#define ActorInstance_RVC_decoder__parser__parseheaders__stuck_4a_ID 51
#define ActorInstance_RVC_decoder__parser__parseheaders__stuck_4b_ID 52
static void ActorInstance_RVC_decoder__parser__parseheaders_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__parser__parseheaders *thisActor=(ActorInstance_RVC_decoder__parser__parseheaders*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_1a_ID;//Initial state
  {
    thisActor->bits_to_read_count = -1;
    thisActor->bit_count = 0;
    thisActor->vld_codeword = 1;
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__parser__parseheaders_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__parser__parseheaders *thisActor=(ActorInstance_RVC_decoder__parser__parseheaders*) pBase;
  ART_ACTION_SCHEDULER_ENTER(1, 8)
  while(1) {
    if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
      if (RVC_decoder__parser__parseheaders__DOLLAR__d4085(context, thisActor)) {
        ART_FIRE_ACTION(action0);
        continue;
      }
    }
    if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
      if (RVC_decoder__parser__parseheaders__DOLLAR__d5510(context, thisActor)) {
        ART_FIRE_ACTION(action59);
        continue;
      }
    }
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__parser__parseheaders__vol_object_ID:
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if (RVC_decoder__parser__parseheaders__DOLLAR__d4118(context, thisActor)) {
            ART_FIRE_ACTION(action1__vol_object_layer_identification);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vol_aspect_ID;
            continue;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vol_aspect_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4132(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4135(context, thisActor)) {
          ART_FIRE_ACTION(action2__vol_aspect__detailed);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vol_control_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5534(context, thisActor)) {
          ART_FIRE_ACTION(action61__generic_done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vol_control_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vol_control_ID:
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if (RVC_decoder__parser__parseheaders__DOLLAR__d4148(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4151(context, thisActor)) {
            ART_FIRE_ACTION(action3__vol_control__detailed);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vol_vbv_ID;
            continue;
          }
        }
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if (RVC_decoder__parser__parseheaders__DOLLAR__d5539(context, thisActor)) {
            ART_FIRE_ACTION(action62__generic_done_with_bitread);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vol_shape_ID;
            continue;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vol_vbv_ID:
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if (RVC_decoder__parser__parseheaders__DOLLAR__d4162(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4165(context, thisActor)) {
            ART_FIRE_ACTION(action4__vol_vbv__detailed);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vol_shape_ID;
            continue;
          }
        }
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if (RVC_decoder__parser__parseheaders__DOLLAR__d5539(context, thisActor)) {
            ART_FIRE_ACTION(action62__generic_done_with_bitread);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vol_shape_ID;
            continue;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vol_shape_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4192(context, thisActor)) {
          ART_FIRE_ACTION(action5__vol_shape);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vol_time_inc_res_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vol_time_inc_res_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4204(context, thisActor)) {
          ART_FIRE_ACTION(action6__vol_time_inc_res);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vol_width_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vol_width_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4281(context, thisActor)) {
          ART_FIRE_ACTION(action7__set_vol_width);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vol_height_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vol_height_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4299(context, thisActor)) {
          ART_FIRE_ACTION(action8__set_vol_height);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vol_misc_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vol_misc_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5534(context, thisActor)) {
          ART_FIRE_ACTION(action61__generic_done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__stuck_ID:
        ART_FIRE_ACTION(action9__byte_align);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_1a_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vop_predict_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4319(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4322(context, thisActor)) {
          ART_FIRE_ACTION(action10__vop_predict__supported);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vop_timebase_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5534(context, thisActor)) {
          ART_FIRE_ACTION(action61__generic_done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vop_timebase_ID:
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if (RVC_decoder__parser__parseheaders__DOLLAR__d4361(context, thisActor)) {
            ART_FIRE_ACTION(action11__vop_timebase__one);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vop_timebase_ID;
            continue;
          }
        }
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          ART_FIRE_ACTION(action12__vop_timebase__zero);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vop_coding_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vop_coding_ID:
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if (RVC_decoder__parser__parseheaders__DOLLAR__d4379(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4382(context, thisActor)) {
            ART_FIRE_ACTION(action13__vop_coding__uncoded);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_ID;
            continue;
          }
        }
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if (RVC_decoder__parser__parseheaders__DOLLAR__d4392(context, thisActor)) {
            ART_FIRE_ACTION(action14__vop_coding__coded);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__send_new_vop_info_ID;
            continue;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__send_new_vop_info_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4411(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT0_BTYPE) >= 1)) {
            ART_FIRE_ACTION(action15__send_new_vop_cmd);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__send_new_vop_width_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__send_new_vop_width_ID:
        if ((pinAvailOut_int32_t(OUT0_BTYPE) >= 1) && (pinAvailOut_int32_t(OUT5_WIDTH) >= 1)) {
          ART_FIRE_ACTION(action16__send_new_vop_width);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__send_new_vop_height_ID;
          continue;
        
        } else {
          result = exitcode_block_Any;
          goto out;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__send_new_vop_height_ID:
        if ((pinAvailOut_int32_t(OUT0_BTYPE) >= 1) && (pinAvailOut_int32_t(OUT6_HEIGHT) >= 1)) {
          ART_FIRE_ACTION(action17__send_new_vop_height);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__mb_ID;
          continue;
        
        } else {
          result = exitcode_block_Any;
          goto out;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__mb_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4515(context, thisActor)) {
          ART_FIRE_ACTION(action18__mb_done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_ID;
          continue;
        }
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if (RVC_decoder__parser__parseheaders__DOLLAR__d4524(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4527(context, thisActor)) {
            ART_FIRE_ACTION(action20__get_mcbpc__pvop);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__get_mbtype_ID;
            continue;
          }
        }
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if (RVC_decoder__parser__parseheaders__DOLLAR__d4537(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT0_BTYPE) >= 1) && (pinAvailOut_int32_t(OUT7_QP) >= 1)) {
              ART_FIRE_ACTION(action21__mcbpc_pvop_uncoded);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__pvop_uncoded1_ID;
              continue;
            
            } else {
              result = exitcode_block_Any;
              goto out;
            }
          }
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4519(context, thisActor)) {
          ART_FIRE_ACTION(action19__get_mcbpc__ivop);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__get_mbtype_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__pvop_uncoded1_ID:
        if ((pinAvailOut_int32_t(OUT0_BTYPE) >= 1) && (pinAvailOut_int32_t(OUT7_QP) >= 1)) {
          ART_FIRE_ACTION(action22__mcbpc_pvop_uncoded1);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__pvop_uncoded2_ID;
          continue;
        
        } else {
          result = exitcode_block_Any;
          goto out;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__pvop_uncoded2_ID:
        if ((pinAvailOut_int32_t(OUT0_BTYPE) >= 1) && (pinAvailOut_int32_t(OUT7_QP) >= 1)) {
          ART_FIRE_ACTION(action22__mcbpc_pvop_uncoded1);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__pvop_uncoded3_ID;
          continue;
        
        } else {
          result = exitcode_block_Any;
          goto out;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__pvop_uncoded3_ID:
        if ((pinAvailOut_int32_t(OUT0_BTYPE) >= 1) && (pinAvailOut_int32_t(OUT7_QP) >= 1)) {
          ART_FIRE_ACTION(action22__mcbpc_pvop_uncoded1);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__pvop_uncoded4_ID;
          continue;
        
        } else {
          result = exitcode_block_Any;
          goto out;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__pvop_uncoded4_ID:
        if ((pinAvailOut_int32_t(OUT0_BTYPE) >= 1) && (pinAvailOut_int32_t(OUT7_QP) >= 1)) {
          ART_FIRE_ACTION(action22__mcbpc_pvop_uncoded1);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__pvop_uncoded5_ID;
          continue;
        
        } else {
          result = exitcode_block_Any;
          goto out;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__pvop_uncoded5_ID:
        if ((pinAvailOut_int32_t(OUT0_BTYPE) >= 1) && (pinAvailOut_int32_t(OUT7_QP) >= 1)) {
          ART_FIRE_ACTION(action22__mcbpc_pvop_uncoded1);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__mb_ID;
          continue;
        
        } else {
          result = exitcode_block_Any;
          goto out;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__get_mbtype_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5531(context, thisActor)) {
          ART_FIRE_ACTION(action60__do_vld_failure);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4559(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4562(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4570(context, thisActor)) {
          ART_FIRE_ACTION(action23__get_mbtype__noac);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__final_cbpy_ID;
          continue;
        }
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if (RVC_decoder__parser__parseheaders__DOLLAR__d4610(context, thisActor)) {
            ART_FIRE_ACTION(action24__get_mbtype__ac);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__final_cbpy_ID;
            continue;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__final_cbpy_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4641(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4644(context, thisActor)) {
          ART_FIRE_ACTION(action25__final_cbpy_inter);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__dquant_inter_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4665(context, thisActor)) {
          ART_FIRE_ACTION(action26__final_cbpy_intra);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__dquant_intra_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5531(context, thisActor)) {
          ART_FIRE_ACTION(action60__do_vld_failure);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__dquant_intra_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4683(context, thisActor)) {
          ART_FIRE_ACTION(action27__final_dquant);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__block_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__block_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4707(context, thisActor)) {
          ART_FIRE_ACTION(action28__mb_dispatch_done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__mb_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4711(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT0_BTYPE) >= 1) && (pinAvailOut_int32_t(OUT7_QP) >= 1)) {
            ART_FIRE_ACTION(action29__mb_dispatch_intra);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__texture_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4749(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT0_BTYPE) >= 1) && (pinAvailOut_int32_t(OUT7_QP) >= 1)) {
            ART_FIRE_ACTION(action30__mb_dispatch_inter_no_ac);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__block_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        if ((pinAvailOut_int32_t(OUT0_BTYPE) >= 1) && (pinAvailOut_int32_t(OUT7_QP) >= 1)) {
          ART_FIRE_ACTION(action31__mb_dispatch_inter_ac_coded);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__texture_ID;
          continue;
        
        } else {
          result = exitcode_block_Any;
          goto out;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__dquant_inter_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4683(context, thisActor)) {
          ART_FIRE_ACTION(action27__final_dquant);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__mv_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__mv_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5431(context, thisActor)) {
          ART_FIRE_ACTION(action53__mvcode_done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__block_ID;
          continue;
        }
        ART_FIRE_ACTION(action54__mvcode);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__mag_x_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__texture_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4807(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4809(context, thisActor)) {
          ART_FIRE_ACTION(action32__vld_start_intra__dc);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__get_dc_bits_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4829(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4831(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4835(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT2_RUN) >= 1) && (pinAvailOut_int32_t(OUT3_VALUE) >= 1) && (pinAvailOut_bool_t(OUT4_LAST) >= 1)) {
            ART_FIRE_ACTION(action34__vld_start_intra__nodc__no_ac_coded);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__texac_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4820(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4822(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4826(context, thisActor)) {
          ART_FIRE_ACTION(action33__vld_start_intra__nodc__ac_coded);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__texac_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4853(context, thisActor)) {
          ART_FIRE_ACTION(action35__vld_start_inter__ac_coded);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__texac_ID;
          continue;
        }
        if ((pinAvailOut_int32_t(OUT2_RUN) >= 1) && (pinAvailOut_int32_t(OUT3_VALUE) >= 1) && (pinAvailOut_bool_t(OUT4_LAST) >= 1)) {
          ART_FIRE_ACTION(action36__vld_start_inter__not_ac_coded);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__texac_ID;
          continue;
        
        } else {
          result = exitcode_block_Any;
          goto out;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__get_dc_bits_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5531(context, thisActor)) {
          ART_FIRE_ACTION(action60__do_vld_failure);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4871(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4874(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT2_RUN) >= 1) && (pinAvailOut_int32_t(OUT3_VALUE) >= 1) && (pinAvailOut_bool_t(OUT4_LAST) >= 1)) {
            ART_FIRE_ACTION(action37__get_dc_bits__none);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__texac_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4896(context, thisActor)) {
          ART_FIRE_ACTION(action38__get_dc_bits__some);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__get_dc_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__texac_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4964(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4967(context, thisActor)) {
          ART_FIRE_ACTION(action41__block_done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__block_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4972(context, thisActor)) {
          ART_FIRE_ACTION(action42__dct_coeff);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vld1_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__get_dc_ID:
        ART_FIRE_ACTION(action39__dc_bits_shift);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__get_dc_a_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__get_dc_a_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d4920(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT2_RUN) >= 1) && (pinAvailOut_int32_t(OUT3_VALUE) >= 1) && (pinAvailOut_bool_t(OUT4_LAST) >= 1)) {
            ART_FIRE_ACTION(action40__get_dc);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__texac_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vld1_ID:
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if (RVC_decoder__parser__parseheaders__DOLLAR__d4981(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d4984(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT3_VALUE) >= 1) && (pinAvailOut_int32_t(OUT2_RUN) >= 1) && (pinAvailOut_bool_t(OUT4_LAST) >= 1)) {
              ART_FIRE_ACTION(action43__vld_code);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__texac_ID;
              continue;
            
            } else {
              result = exitcode_block_Any;
              goto out;
            }
          }
        }
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if (RVC_decoder__parser__parseheaders__DOLLAR__d5064(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d5067(context, thisActor)) {
            ART_FIRE_ACTION(action44__vld_level);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vld4_ID;
            continue;
          }
        }
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if (RVC_decoder__parser__parseheaders__DOLLAR__d5080(context, thisActor)) {
            ART_FIRE_ACTION(action45__vld_run_or_direct);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vld7_ID;
            continue;
          }
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5531(context, thisActor)) {
          ART_FIRE_ACTION(action60__do_vld_failure);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vld4_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5531(context, thisActor)) {
          ART_FIRE_ACTION(action60__do_vld_failure);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5183(context, thisActor)) {
          ART_FIRE_ACTION(action49__do_level_lookup);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vld4a_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vld7_ID:
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if (RVC_decoder__parser__parseheaders__DOLLAR__d5088(context, thisActor)) {
            ART_FIRE_ACTION(action46__vld_run);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vld6_ID;
            continue;
          }
        }
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          ART_FIRE_ACTION(action47__vld_direct_read);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vld_direct_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vld6_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5531(context, thisActor)) {
          ART_FIRE_ACTION(action60__do_vld_failure);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5309(context, thisActor)) {
          ART_FIRE_ACTION(action51__do_run_lookup);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vld6a_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vld_direct_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5113(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT3_VALUE) >= 1) && (pinAvailOut_int32_t(OUT2_RUN) >= 1) && (pinAvailOut_bool_t(OUT4_LAST) >= 1)) {
            ART_FIRE_ACTION(action48__vld_direct);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__texac_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vld4a_ID:
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if ((pinAvailOut_int32_t(OUT3_VALUE) >= 1) && (pinAvailOut_int32_t(OUT2_RUN) >= 1) && (pinAvailOut_bool_t(OUT4_LAST) >= 1)) {
            ART_FIRE_ACTION(action50__vld_level_lookup);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__texac_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__vld6a_ID:
        if ((pinAvailIn_bool_t(IN0_bits) >= 1)) {
          if ((pinAvailOut_int32_t(OUT3_VALUE) >= 1) && (pinAvailOut_int32_t(OUT2_RUN) >= 1) && (pinAvailOut_bool_t(OUT4_LAST) >= 1)) {
            ART_FIRE_ACTION(action52__vld_run_lookup);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__texac_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__mag_x_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5443(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT1_MV) >= 1)) {
            ART_FIRE_ACTION(action55__mag_x);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__get_residual_x_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5531(context, thisActor)) {
          ART_FIRE_ACTION(action60__do_vld_failure);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__get_residual_x_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5465(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT1_MV) >= 1)) {
            ART_FIRE_ACTION(action56__get_residual_x);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__mv_y_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__mv_y_ID:
        ART_FIRE_ACTION(action54__mvcode);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__mag_y_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__mag_y_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5474(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT1_MV) >= 1)) {
            ART_FIRE_ACTION(action57__mag_y);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__get_residual_y_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5531(context, thisActor)) {
          ART_FIRE_ACTION(action60__do_vld_failure);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__get_residual_y_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5496(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT1_MV) >= 1)) {
            ART_FIRE_ACTION(action58__get_residual_y);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__mv_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__stuck_1a_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5600(context, thisActor)) {
          ART_FIRE_ACTION(action68__request_byte);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_1b_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__stuck_1b_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5545(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d5548(context, thisActor)) {
          ART_FIRE_ACTION(action63__test_zero_byte);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_2a_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5534(context, thisActor)) {
          ART_FIRE_ACTION(action61__generic_done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_1a_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__stuck_2a_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5600(context, thisActor)) {
          ART_FIRE_ACTION(action68__request_byte);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_2b_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__stuck_2b_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5545(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d5548(context, thisActor)) {
          ART_FIRE_ACTION(action63__test_zero_byte);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_3a_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5534(context, thisActor)) {
          ART_FIRE_ACTION(action61__generic_done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_1a_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__stuck_3a_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5600(context, thisActor)) {
          ART_FIRE_ACTION(action68__request_byte);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_3b_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__stuck_3b_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5589(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d5592(context, thisActor)) {
          ART_FIRE_ACTION(action67__test_one_byte);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_4a_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5545(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d5548(context, thisActor)) {
          ART_FIRE_ACTION(action63__test_zero_byte);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_3a_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5534(context, thisActor)) {
          ART_FIRE_ACTION(action61__generic_done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_1a_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__stuck_4a_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5600(context, thisActor)) {
          ART_FIRE_ACTION(action68__request_byte);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_4b_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__parseheaders__stuck_4b_ID:
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5556(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d5559(context, thisActor)) {
          ART_FIRE_ACTION(action64__test_vo_byte);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_1a_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5567(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d5570(context, thisActor)) {
          ART_FIRE_ACTION(action65__test_vol_byte);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vol_object_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5578(context, thisActor) && RVC_decoder__parser__parseheaders__DOLLAR__d5581(context, thisActor)) {
          ART_FIRE_ACTION(action66__test_vop_byte);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__vop_predict_ID;
          continue;
        }
        if (RVC_decoder__parser__parseheaders__DOLLAR__d5534(context, thisActor)) {
          ART_FIRE_ACTION(action61__generic_done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__parseheaders__stuck_1a_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
    }
  }
  out:
  ART_ACTION_SCHEDULER_EXIT(1, 8)
  return result;
}