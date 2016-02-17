mol new result_structure.xyz
mol delrep 0 0

mol selection "type LH"
mol addrep 0
mol modstyle 0 0 VDW 6
mol modcolor 0 0 ColorID 3

mol selection "type LT"
mol addrep 0
mol modstyle 1 0 VDW 6
mol modcolor 1 0 ColorID 2
