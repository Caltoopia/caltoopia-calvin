# serz__top
LOAD ./serz__f
LOAD ./serz__s
NEW serz__f serz__f
NEW serz__s serz__s
CONNECT serz__f.Out serz__s.In
CONNECT serz__s.Out serz__f.In
ENABLE serz__f serz__s
JOIN