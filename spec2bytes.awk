BEGIN {
  FS = ""
  ORS = ""
  count = 0
  curr = 0
  if (styleName == "") styleName = "style"
  print "#ifndef __STYLE_" toupper(styleName) "_H__\n\n"
  print "const uint8_t PROGMEM", tolower(styleName), "[8][5] = {\n" 
}

{
  for (i=1; i<=NF; i++) {
    if ($i == ".") b[i][count] = 0
    else if ($i == "#") b[i][count] = 1
  }
  if (count++ == 7) {
    count = 0
    printByte()
    delete b
  }
}

function printByte() {
  print "  {\n"
  for (i=1; i<=5; i++) {
    print "    0b"
    for (j=0; j<=8; j++) {
      print b[i][j] 
    }
    if (curr == 5 && i == 5) print "\n  }\n"
    else if (i == 5) print "\n  },\n"
    else print ",\n"
  }
  curr++
}

END {
  print "};\n"
  print "\n#endif"
}
