import calvin
import time

n = calvin.Node("localhost", 9000, True)
# k = calvin.Node("136.225.61.113", 9000, True)
k = calvin.Node("localhost", 9001, True)
# k = n

n.load("./RVC__decoder__GEN_mgnt_Merger420")
n.load("./RVC__decoder__motion_U__add")
n.load("./RVC__decoder__motion_U__framebuf")
n.load("./RVC__decoder__motion_U__interpolation")
n.load("./RVC__decoder__motion_V__add")
n.load("./RVC__decoder__motion_V__framebuf")
n.load("./RVC__decoder__motion_V__interpolation")
k.load("./RVC__decoder__motion_Y__add")
k.load("./RVC__decoder__motion_Y__framebuf")
k.load("./RVC__decoder__motion_Y__interpolation")
n.load("./RVC__decoder__parser__blkexp")
n.load("./RVC__decoder__parser__mvrecon")
n.load("./RVC__decoder__parser__mvseq")
n.load("./RVC__decoder__parser__parseheaders")
n.load("./RVC__decoder__parser__splitter_420_B")
n.load("./RVC__decoder__parser__splitter_BTYPE")
n.load("./RVC__decoder__parser__splitter_MV")
n.load("./RVC__decoder__parser__splitter_Qp")
n.load("./RVC__decoder__serialize")
n.load("./RVC__decoder__texture_U__DCRecontruction__addressing")
n.load("./RVC__decoder__texture_U__DCRecontruction__invpred")
n.load("./RVC__decoder__texture_U__DCsplit")
n.load("./RVC__decoder__texture_U__IAP")
n.load("./RVC__decoder__texture_U__idct2d__clip")
n.load("./RVC__decoder__texture_U__idct2d__column")
n.load("./RVC__decoder__texture_U__idct2d__retranspose")
n.load("./RVC__decoder__texture_U__idct2d__row")
n.load("./RVC__decoder__texture_U__idct2d__scale")
n.load("./RVC__decoder__texture_U__idct2d__shift")
n.load("./RVC__decoder__texture_U__idct2d__transpose")
n.load("./RVC__decoder__texture_U__IQ")
n.load("./RVC__decoder__texture_U__IS")
n.load("./RVC__decoder__texture_V__DCRecontruction__addressing")
n.load("./RVC__decoder__texture_V__DCRecontruction__invpred")
n.load("./RVC__decoder__texture_V__DCsplit")
n.load("./RVC__decoder__texture_V__IAP")
n.load("./RVC__decoder__texture_V__idct2d__clip")
n.load("./RVC__decoder__texture_V__idct2d__column")
n.load("./RVC__decoder__texture_V__idct2d__retranspose")
n.load("./RVC__decoder__texture_V__idct2d__row")
n.load("./RVC__decoder__texture_V__idct2d__scale")
n.load("./RVC__decoder__texture_V__idct2d__shift")
n.load("./RVC__decoder__texture_V__idct2d__transpose")
n.load("./RVC__decoder__texture_V__IQ")
n.load("./RVC__decoder__texture_V__IS")
k.load("./RVC__decoder__texture_Y__DCRecontruction__addressing")
k.load("./RVC__decoder__texture_Y__DCRecontruction__invpred")
k.load("./RVC__decoder__texture_Y__DCsplit")
k.load("./RVC__decoder__texture_Y__IAP")
k.load("./RVC__decoder__texture_Y__idct2d__clip")
k.load("./RVC__decoder__texture_Y__idct2d__column")
k.load("./RVC__decoder__texture_Y__idct2d__retranspose")
k.load("./RVC__decoder__texture_Y__idct2d__row")
k.load("./RVC__decoder__texture_Y__idct2d__scale")
k.load("./RVC__decoder__texture_Y__idct2d__shift")
k.load("./RVC__decoder__texture_Y__idct2d__transpose")
k.load("./RVC__decoder__texture_Y__IQ")
k.load("./RVC__decoder__texture_Y__IS")

ART_sourceBits = n.new("art_Source_bin", "ART_sourceBits", fileName="./foreman_qcif_30.bit")

ART_display = n.new("art_Display_yuv", "ART_display", title="Foreman_QCIF", width="176", height="144")

ART_sinkWIDTH = n.new("art_Sink_txt", "ART_sinkWIDTH", fileName="./WIDTH.txt") 
ART_sinkHEIGHT = n.new("art_Sink_txt", "ART_sinkHEIGHT", fileName="./HEIGHT.txt")

RVC_decoder__serialize = n.new("RVC_decoder__serialize")
RVC_decoder__GEN_mgnt_Merger420 = n.new("RVC_decoder__GEN_mgnt_Merger420")
RVC_decoder__motion_V__framebuf = n.new("RVC_decoder__motion_V__framebuf")
RVC_decoder__motion_V__interpolation = n.new("RVC_decoder__motion_V__interpolation")
RVC_decoder__motion_V__add = n.new("RVC_decoder__motion_V__add")
RVC_decoder__motion_U__framebuf = n.new("RVC_decoder__motion_U__framebuf")
RVC_decoder__motion_U__interpolation = n.new("RVC_decoder__motion_U__interpolation")
RVC_decoder__motion_U__add = n.new("RVC_decoder__motion_U__add")
RVC_decoder__motion_Y__framebuf = k.new("RVC_decoder__motion_Y__framebuf")
RVC_decoder__motion_Y__interpolation = k.new("RVC_decoder__motion_Y__interpolation")
RVC_decoder__motion_Y__add = k.new("RVC_decoder__motion_Y__add")
RVC_decoder__texture_V__DCsplit = n.new("RVC_decoder__texture_V__DCsplit")
RVC_decoder__texture_V__IS = n.new("RVC_decoder__texture_V__IS")
RVC_decoder__texture_V__IAP = n.new("RVC_decoder__texture_V__IAP")
RVC_decoder__texture_V__IQ = n.new("RVC_decoder__texture_V__IQ")
RVC_decoder__texture_V__idct2d__scale = n.new("RVC_decoder__texture_V__idct2d__scale")
RVC_decoder__texture_V__idct2d__row = n.new("RVC_decoder__texture_V__idct2d__row")
RVC_decoder__texture_V__idct2d__column = n.new("RVC_decoder__texture_V__idct2d__column")
RVC_decoder__texture_V__idct2d__transpose = n.new("RVC_decoder__texture_V__idct2d__transpose")
RVC_decoder__texture_V__idct2d__retranspose = n.new("RVC_decoder__texture_V__idct2d__retranspose")
RVC_decoder__texture_V__idct2d__shift = n.new("RVC_decoder__texture_V__idct2d__shift")
RVC_decoder__texture_V__idct2d__clip = n.new("RVC_decoder__texture_V__idct2d__clip")
RVC_decoder__texture_V__DCRecontruction__addressing = n.new("RVC_decoder__texture_V__DCRecontruction__addressing")
RVC_decoder__texture_V__DCRecontruction__invpred = n.new("RVC_decoder__texture_V__DCRecontruction__invpred")
RVC_decoder__texture_U__DCsplit = n.new("RVC_decoder__texture_U__DCsplit")
RVC_decoder__texture_U__IS = n.new("RVC_decoder__texture_U__IS")
RVC_decoder__texture_U__IAP = n.new("RVC_decoder__texture_U__IAP")
RVC_decoder__texture_U__IQ = n.new("RVC_decoder__texture_U__IQ")
RVC_decoder__texture_U__idct2d__scale = n.new("RVC_decoder__texture_U__idct2d__scale")
RVC_decoder__texture_U__idct2d__row = n.new("RVC_decoder__texture_U__idct2d__row")
RVC_decoder__texture_U__idct2d__column = n.new("RVC_decoder__texture_U__idct2d__column")
RVC_decoder__texture_U__idct2d__transpose = n.new("RVC_decoder__texture_U__idct2d__transpose")
RVC_decoder__texture_U__idct2d__retranspose = n.new("RVC_decoder__texture_U__idct2d__retranspose")
RVC_decoder__texture_U__idct2d__shift = n.new("RVC_decoder__texture_U__idct2d__shift")
RVC_decoder__texture_U__idct2d__clip = n.new("RVC_decoder__texture_U__idct2d__clip")
RVC_decoder__texture_U__DCRecontruction__addressing = n.new("RVC_decoder__texture_U__DCRecontruction__addressing")
RVC_decoder__texture_U__DCRecontruction__invpred = n.new("RVC_decoder__texture_U__DCRecontruction__invpred")
RVC_decoder__texture_Y__DCsplit = k.new("RVC_decoder__texture_Y__DCsplit")
RVC_decoder__texture_Y__IS = k.new("RVC_decoder__texture_Y__IS")
RVC_decoder__texture_Y__IAP = k.new("RVC_decoder__texture_Y__IAP")
RVC_decoder__texture_Y__IQ = k.new("RVC_decoder__texture_Y__IQ")
RVC_decoder__texture_Y__idct2d__scale = k.new("RVC_decoder__texture_Y__idct2d__scale")
RVC_decoder__texture_Y__idct2d__row = k.new("RVC_decoder__texture_Y__idct2d__row")
RVC_decoder__texture_Y__idct2d__column = k.new("RVC_decoder__texture_Y__idct2d__column") 
RVC_decoder__texture_Y__idct2d__transpose = k.new("RVC_decoder__texture_Y__idct2d__transpose")
RVC_decoder__texture_Y__idct2d__retranspose = k.new("RVC_decoder__texture_Y__idct2d__retranspose")
RVC_decoder__texture_Y__idct2d__shift = k.new("RVC_decoder__texture_Y__idct2d__shift")
RVC_decoder__texture_Y__idct2d__clip = k.new("RVC_decoder__texture_Y__idct2d__clip")
RVC_decoder__texture_Y__DCRecontruction__addressing = k.new("RVC_decoder__texture_Y__DCRecontruction__addressing")
RVC_decoder__texture_Y__DCRecontruction__invpred = k.new("RVC_decoder__texture_Y__DCRecontruction__invpred")
RVC_decoder__parser__parseheaders = n.new("RVC_decoder__parser__parseheaders")
RVC_decoder__parser__mvseq = n.new("RVC_decoder__parser__mvseq") 
RVC_decoder__parser__blkexp = n.new("RVC_decoder__parser__blkexp")
RVC_decoder__parser__mvrecon = n.new("RVC_decoder__parser__mvrecon")
RVC_decoder__parser__splitter_BTYPE = n.new("RVC_decoder__parser__splitter_BTYPE")
RVC_decoder__parser__splitter_MV = n.new("RVC_decoder__parser__splitter_MV")
RVC_decoder__parser__splitter_420_B = n.new("RVC_decoder__parser__splitter_420_B")
RVC_decoder__parser__splitter_Qp = n.new("RVC_decoder__parser__splitter_Qp")

ART_sourceBits.Out >> RVC_decoder__serialize.in8
RVC_decoder__GEN_mgnt_Merger420.YUV >> ART_display.In
RVC_decoder__motion_V__add.VID >> RVC_decoder__motion_V__framebuf.WD
RVC_decoder__motion_V__framebuf.RD >> RVC_decoder__motion_V__interpolation.RD
RVC_decoder__motion_V__framebuf.halfpel >> RVC_decoder__motion_V__interpolation.halfpel
RVC_decoder__motion_V__interpolation.MOT >> RVC_decoder__motion_V__add.MOT
RVC_decoder__motion_V__add.VID >> RVC_decoder__GEN_mgnt_Merger420.V
RVC_decoder__motion_U__add.VID >> RVC_decoder__motion_U__framebuf.WD
RVC_decoder__motion_U__framebuf.RD >> RVC_decoder__motion_U__interpolation.RD
RVC_decoder__motion_U__framebuf.halfpel >> RVC_decoder__motion_U__interpolation.halfpel
RVC_decoder__motion_U__interpolation.MOT >> RVC_decoder__motion_U__add.MOT
RVC_decoder__motion_U__add.VID >> RVC_decoder__GEN_mgnt_Merger420.U
RVC_decoder__motion_Y__add.VID >> RVC_decoder__motion_Y__framebuf.WD
RVC_decoder__motion_Y__framebuf.RD >> RVC_decoder__motion_Y__interpolation.RD
RVC_decoder__motion_Y__framebuf.halfpel >> RVC_decoder__motion_Y__interpolation.halfpel
RVC_decoder__motion_Y__interpolation.MOT >> RVC_decoder__motion_Y__add.MOT
RVC_decoder__motion_Y__add.VID >> RVC_decoder__GEN_mgnt_Merger420.Y
RVC_decoder__texture_V__DCsplit.AC >> RVC_decoder__texture_V__IS.QFS_AC
RVC_decoder__texture_V__IS.PQF_AC >> RVC_decoder__texture_V__IAP.PQF_AC
RVC_decoder__texture_V__IAP.QF_AC >> RVC_decoder__texture_V__IQ.AC
RVC_decoder__texture_V__IQ.OUT >> RVC_decoder__texture_V__idct2d__scale.SIn
RVC_decoder__texture_V__idct2d__scale.SOut >> RVC_decoder__texture_V__idct2d__row.In
RVC_decoder__texture_V__idct2d__transpose.Out >> RVC_decoder__texture_V__idct2d__column.In
RVC_decoder__texture_V__idct2d__row.Out >> RVC_decoder__texture_V__idct2d__transpose.In
RVC_decoder__texture_V__idct2d__column.Out >> RVC_decoder__texture_V__idct2d__retranspose.In
RVC_decoder__texture_V__idct2d__retranspose.Out >> RVC_decoder__texture_V__idct2d__shift.In
RVC_decoder__texture_V__idct2d__shift.Out >> RVC_decoder__texture_V__idct2d__clip.I
RVC_decoder__texture_V__idct2d__clip.O >> RVC_decoder__motion_V__add.TEX
RVC_decoder__texture_V__DCRecontruction__addressing.A >> RVC_decoder__texture_V__DCRecontruction__invpred.A
RVC_decoder__texture_V__DCRecontruction__addressing.B >> RVC_decoder__texture_V__DCRecontruction__invpred.B
RVC_decoder__texture_V__DCRecontruction__addressing.C >> RVC_decoder__texture_V__DCRecontruction__invpred.C
RVC_decoder__texture_V__DCsplit.DC >> RVC_decoder__texture_V__DCRecontruction__invpred.QFS_DC
RVC_decoder__texture_V__DCRecontruction__invpred.QF_DC >> RVC_decoder__texture_V__IQ.DC
RVC_decoder__texture_V__DCRecontruction__invpred.PTR >> RVC_decoder__texture_V__IAP.PTR
RVC_decoder__texture_V__DCRecontruction__invpred.AC_PRED_DIR >> RVC_decoder__texture_V__IAP.AC_PRED_DIR
RVC_decoder__texture_V__DCRecontruction__invpred.AC_PRED_DIR >> RVC_decoder__texture_V__IS.AC_PRED_DIR
RVC_decoder__texture_V__DCRecontruction__invpred.SIGNED >> RVC_decoder__texture_V__idct2d__clip.SIGNED
RVC_decoder__texture_V__DCRecontruction__invpred.QUANT >> RVC_decoder__texture_V__IQ.QP
RVC_decoder__texture_V__DCRecontruction__invpred.QUANT >> RVC_decoder__texture_V__IAP.QP
RVC_decoder__texture_V__DCRecontruction__invpred.PREV_QUANT >> RVC_decoder__texture_V__IAP.PREV_QP
RVC_decoder__texture_U__DCsplit.AC >> RVC_decoder__texture_U__IS.QFS_AC
RVC_decoder__texture_U__IS.PQF_AC >> RVC_decoder__texture_U__IAP.PQF_AC
RVC_decoder__texture_U__IAP.QF_AC >> RVC_decoder__texture_U__IQ.AC
RVC_decoder__texture_U__IQ.OUT >> RVC_decoder__texture_U__idct2d__scale.SIn
RVC_decoder__texture_U__idct2d__scale.SOut >> RVC_decoder__texture_U__idct2d__row.In
RVC_decoder__texture_U__idct2d__transpose.Out >> RVC_decoder__texture_U__idct2d__column.In
RVC_decoder__texture_U__idct2d__row.Out >> RVC_decoder__texture_U__idct2d__transpose.In
RVC_decoder__texture_U__idct2d__column.Out >> RVC_decoder__texture_U__idct2d__retranspose.In
RVC_decoder__texture_U__idct2d__retranspose.Out >> RVC_decoder__texture_U__idct2d__shift.In
RVC_decoder__texture_U__idct2d__shift.Out >> RVC_decoder__texture_U__idct2d__clip.I
RVC_decoder__texture_U__idct2d__clip.O >> RVC_decoder__motion_U__add.TEX
RVC_decoder__texture_U__DCRecontruction__addressing.A >> RVC_decoder__texture_U__DCRecontruction__invpred.A
RVC_decoder__texture_U__DCRecontruction__addressing.B >> RVC_decoder__texture_U__DCRecontruction__invpred.B
RVC_decoder__texture_U__DCRecontruction__addressing.C >> RVC_decoder__texture_U__DCRecontruction__invpred.C
RVC_decoder__texture_U__DCsplit.DC >> RVC_decoder__texture_U__DCRecontruction__invpred.QFS_DC
RVC_decoder__texture_U__DCRecontruction__invpred.QF_DC >> RVC_decoder__texture_U__IQ.DC
RVC_decoder__texture_U__DCRecontruction__invpred.PTR >> RVC_decoder__texture_U__IAP.PTR
RVC_decoder__texture_U__DCRecontruction__invpred.AC_PRED_DIR >> RVC_decoder__texture_U__IAP.AC_PRED_DIR
RVC_decoder__texture_U__DCRecontruction__invpred.AC_PRED_DIR >> RVC_decoder__texture_U__IS.AC_PRED_DIR
RVC_decoder__texture_U__DCRecontruction__invpred.SIGNED >> RVC_decoder__texture_U__idct2d__clip.SIGNED
RVC_decoder__texture_U__DCRecontruction__invpred.QUANT >> RVC_decoder__texture_U__IQ.QP
RVC_decoder__texture_U__DCRecontruction__invpred.QUANT >> RVC_decoder__texture_U__IAP.QP
RVC_decoder__texture_U__DCRecontruction__invpred.PREV_QUANT >> RVC_decoder__texture_U__IAP.PREV_QP
RVC_decoder__texture_Y__DCsplit.AC >> RVC_decoder__texture_Y__IS.QFS_AC
RVC_decoder__texture_Y__IS.PQF_AC >> RVC_decoder__texture_Y__IAP.PQF_AC
RVC_decoder__texture_Y__IAP.QF_AC >> RVC_decoder__texture_Y__IQ.AC
RVC_decoder__texture_Y__IQ.OUT >> RVC_decoder__texture_Y__idct2d__scale.SIn
RVC_decoder__texture_Y__idct2d__scale.SOut >> RVC_decoder__texture_Y__idct2d__row.In
RVC_decoder__texture_Y__idct2d__transpose.Out >> RVC_decoder__texture_Y__idct2d__column.In
RVC_decoder__texture_Y__idct2d__row.Out >> RVC_decoder__texture_Y__idct2d__transpose.In
RVC_decoder__texture_Y__idct2d__column.Out >> RVC_decoder__texture_Y__idct2d__retranspose.In
RVC_decoder__texture_Y__idct2d__retranspose.Out >> RVC_decoder__texture_Y__idct2d__shift.In
RVC_decoder__texture_Y__idct2d__shift.Out >> RVC_decoder__texture_Y__idct2d__clip.I
RVC_decoder__texture_Y__idct2d__clip.O >> RVC_decoder__motion_Y__add.TEX
RVC_decoder__texture_Y__DCRecontruction__addressing.A >> RVC_decoder__texture_Y__DCRecontruction__invpred.A
RVC_decoder__texture_Y__DCRecontruction__addressing.B >> RVC_decoder__texture_Y__DCRecontruction__invpred.B
RVC_decoder__texture_Y__DCRecontruction__addressing.C >> RVC_decoder__texture_Y__DCRecontruction__invpred.C
RVC_decoder__texture_Y__DCsplit.DC >> RVC_decoder__texture_Y__DCRecontruction__invpred.QFS_DC
RVC_decoder__texture_Y__DCRecontruction__invpred.QF_DC >> RVC_decoder__texture_Y__IQ.DC
RVC_decoder__texture_Y__DCRecontruction__invpred.PTR >> RVC_decoder__texture_Y__IAP.PTR
RVC_decoder__texture_Y__DCRecontruction__invpred.AC_PRED_DIR >> RVC_decoder__texture_Y__IAP.AC_PRED_DIR
RVC_decoder__texture_Y__DCRecontruction__invpred.AC_PRED_DIR >> RVC_decoder__texture_Y__IS.AC_PRED_DIR
RVC_decoder__texture_Y__DCRecontruction__invpred.SIGNED >> RVC_decoder__texture_Y__idct2d__clip.SIGNED
RVC_decoder__texture_Y__DCRecontruction__invpred.QUANT >> RVC_decoder__texture_Y__IQ.QP
RVC_decoder__texture_Y__DCRecontruction__invpred.QUANT >> RVC_decoder__texture_Y__IAP.QP
RVC_decoder__texture_Y__DCRecontruction__invpred.PREV_QUANT >> RVC_decoder__texture_Y__IAP.PREV_QP
RVC_decoder__serialize.out >> RVC_decoder__parser__parseheaders.bits
RVC_decoder__parser__parseheaders.WIDTH >> ART_sinkWIDTH.In
RVC_decoder__parser__parseheaders.HEIGHT >> ART_sinkHEIGHT.In
RVC_decoder__parser__parseheaders.BTYPE >> RVC_decoder__parser__mvseq.BTYPE
RVC_decoder__parser__parseheaders.RUN >> RVC_decoder__parser__blkexp.RUN
RVC_decoder__parser__parseheaders.VALUE >> RVC_decoder__parser__blkexp.VALUE
RVC_decoder__parser__parseheaders.LAST >> RVC_decoder__parser__blkexp.LAST
RVC_decoder__parser__parseheaders.BTYPE >> RVC_decoder__parser__mvrecon.BTYPE
RVC_decoder__parser__parseheaders.MV >> RVC_decoder__parser__mvrecon.MVIN
RVC_decoder__parser__mvseq.A >> RVC_decoder__parser__mvrecon.A
RVC_decoder__parser__parseheaders.BTYPE >> RVC_decoder__parser__splitter_BTYPE.BTYPE
RVC_decoder__parser__splitter_BTYPE.Y >> RVC_decoder__motion_Y__framebuf.BTYPE
RVC_decoder__parser__splitter_BTYPE.Y >> RVC_decoder__motion_Y__add.BTYPE
RVC_decoder__parser__splitter_BTYPE.Y >> RVC_decoder__texture_Y__DCRecontruction__addressing.BTYPE
RVC_decoder__parser__splitter_BTYPE.Y >> RVC_decoder__texture_Y__DCRecontruction__invpred.BTYPE
RVC_decoder__parser__splitter_BTYPE.U >> RVC_decoder__motion_U__framebuf.BTYPE
RVC_decoder__parser__splitter_BTYPE.U >> RVC_decoder__motion_U__add.BTYPE
RVC_decoder__parser__splitter_BTYPE.U >> RVC_decoder__texture_U__DCRecontruction__addressing.BTYPE
RVC_decoder__parser__splitter_BTYPE.U >> RVC_decoder__texture_U__DCRecontruction__invpred.BTYPE
RVC_decoder__parser__splitter_BTYPE.V >> RVC_decoder__motion_V__framebuf.BTYPE
RVC_decoder__parser__splitter_BTYPE.V >> RVC_decoder__motion_V__add.BTYPE
RVC_decoder__parser__splitter_BTYPE.V >> RVC_decoder__texture_V__DCRecontruction__addressing.BTYPE
RVC_decoder__parser__splitter_BTYPE.V >> RVC_decoder__texture_V__DCRecontruction__invpred.BTYPE
RVC_decoder__parser__mvrecon.MV >> RVC_decoder__parser__splitter_MV.MV
RVC_decoder__parser__parseheaders.BTYPE >> RVC_decoder__parser__splitter_MV.BTYPE
RVC_decoder__parser__splitter_MV.Y >> RVC_decoder__motion_Y__framebuf.MV
RVC_decoder__parser__splitter_MV.U >> RVC_decoder__motion_U__framebuf.MV
RVC_decoder__parser__splitter_MV.V >> RVC_decoder__motion_V__framebuf.MV
RVC_decoder__parser__blkexp.OUT >> RVC_decoder__parser__splitter_420_B.B
RVC_decoder__parser__parseheaders.BTYPE >> RVC_decoder__parser__splitter_420_B.BTYPE
RVC_decoder__parser__splitter_420_B.Y >> RVC_decoder__texture_Y__DCsplit.IN
RVC_decoder__parser__splitter_420_B.U >> RVC_decoder__texture_U__DCsplit.IN
RVC_decoder__parser__splitter_420_B.V >> RVC_decoder__texture_V__DCsplit.IN
RVC_decoder__parser__parseheaders.QP >> RVC_decoder__parser__splitter_Qp.QP
RVC_decoder__parser__splitter_Qp.QUANT_Y >> RVC_decoder__texture_Y__DCRecontruction__invpred.QP
RVC_decoder__parser__splitter_Qp.QUANT_U >> RVC_decoder__texture_U__DCRecontruction__invpred.QP
RVC_decoder__parser__splitter_Qp.QUANT_V >> RVC_decoder__texture_V__DCRecontruction__invpred.QP

actors = (ART_sourceBits,ART_display,ART_sinkWIDTH,ART_sinkHEIGHT,RVC_decoder__serialize,RVC_decoder__GEN_mgnt_Merger420,RVC_decoder__motion_V__framebuf,RVC_decoder__motion_V__interpolation,RVC_decoder__motion_V__add,RVC_decoder__motion_U__framebuf,RVC_decoder__motion_U__interpolation,RVC_decoder__motion_U__add,RVC_decoder__motion_Y__framebuf,RVC_decoder__motion_Y__interpolation,RVC_decoder__motion_Y__add,RVC_decoder__texture_V__DCsplit,RVC_decoder__texture_V__IS,RVC_decoder__texture_V__IAP,RVC_decoder__texture_V__IQ,RVC_decoder__texture_V__idct2d__scale,RVC_decoder__texture_V__idct2d__row,RVC_decoder__texture_V__idct2d__column,RVC_decoder__texture_V__idct2d__transpose,RVC_decoder__texture_V__idct2d__retranspose,RVC_decoder__texture_V__idct2d__shift,RVC_decoder__texture_V__idct2d__clip,RVC_decoder__texture_V__DCRecontruction__addressing,RVC_decoder__texture_V__DCRecontruction__invpred,RVC_decoder__texture_U__DCsplit,RVC_decoder__texture_U__IS,RVC_decoder__texture_U__IAP,RVC_decoder__texture_U__IQ,RVC_decoder__texture_U__idct2d__scale,RVC_decoder__texture_U__idct2d__row,RVC_decoder__texture_U__idct2d__column,RVC_decoder__texture_U__idct2d__transpose,RVC_decoder__texture_U__idct2d__retranspose,RVC_decoder__texture_U__idct2d__shift,RVC_decoder__texture_U__idct2d__clip,RVC_decoder__texture_U__DCRecontruction__addressing,RVC_decoder__texture_U__DCRecontruction__invpred,RVC_decoder__texture_Y__DCsplit,RVC_decoder__texture_Y__IS,RVC_decoder__texture_Y__IAP,RVC_decoder__texture_Y__IQ,RVC_decoder__texture_Y__idct2d__scale,RVC_decoder__texture_Y__idct2d__row,RVC_decoder__texture_Y__idct2d__column,RVC_decoder__texture_Y__idct2d__transpose,RVC_decoder__texture_Y__idct2d__retranspose,RVC_decoder__texture_Y__idct2d__shift,RVC_decoder__texture_Y__idct2d__clip,RVC_decoder__texture_Y__DCRecontruction__addressing,RVC_decoder__texture_Y__DCRecontruction__invpred,RVC_decoder__parser__parseheaders,RVC_decoder__parser__mvseq,RVC_decoder__parser__blkexp,RVC_decoder__parser__mvrecon,RVC_decoder__parser__splitter_BTYPE,RVC_decoder__parser__splitter_MV,RVC_decoder__parser__splitter_420_B,RVC_decoder__parser__splitter_Qp)

for actor in actors:
  actor.enable()

time.sleep(10)

for actor in actors:
  actor.destroy()
