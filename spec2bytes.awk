BEGIN {
  FS = ""
  ORS = ""
  count = 0
  curr = 0
  o[0] = "maskLN"
  o[1] = "maskLP"
  o[2] = "maskRN"
  o[3] = "maskRP"
  o[4] = "maskMN"
  o[5] = "maskMP"
  o[6] = "offsetL"
  o[7] = "offsetR"
  offsetLeft = 0
  offsetRight = 0
  if (styleName == "") styleName = "style"
  print "#ifndef __STYLE_" toupper(styleName) "_H__\n\n"
  print "#include \"style.h\"\n\n"
  print "const style PROG_DECORATOR", tolower(styleName), "= {\n"
}

NF>=5 {
  for (i=1; i<=NF; i++) {
    if ($i == ".") b[i][count] = 0
    else if ($i == "#") b[i][count] = 1
  }
  if (count++ == 7) {
    count = 0
    calcOffset()
    printByte()
    delete b
  }
}

function printByte() {
  print "  ."o[curr], "= {\n"
  for (i=1; i<=5; i++) {
    print "    0b"
    for (j=0; j<8; j++) {
      print b[i][j]
    }
    if (i == 5) print "\n  },\n"
    else print ",\n"
  }
  curr++
}

# find the first drawable pixel on each side
function calcOffset() {
  if (curr == 0) {
    for (i=1; i<=5; i++) {
      nonZero = 0
      for (j=0; j<8; j++) if (b[i][j] != 0) nonZero = 1
      if (nonZero) break
      offsetLeft++
    }
  } else if (curr == 2) {
    for (i=5; i>0; i--) {
      nonZero = 0
      for (j=0; j<8; j++) if (b[i][j] != 0) nonZero = 1
      if (nonZero) break
      offsetRight++
    }
  }
}

END {
  print "  ." o[6], "=", offsetLeft ",\n"
  print "  ." o[7], "=", offsetRight"\n"
  print "};\n"
  print "\n#endif"
}
