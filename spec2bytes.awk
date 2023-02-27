BEGIN {
  FS = ""
  ORS = ""
  count = 0
  o[0] = "leftPos"
  o[1] = "leftNeg"
  o[2] = "rightPos"
  o[3] = "rightNeg"
  o[4] = "midPos"
  o[5] = "midNeg"
  curr = 0
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
  print o[curr], "= {\n"
  for (i=1; i<=5; i++) {
    print "  0b"
    for (j=0; j<=8; j++) {
      print b[i][j] 
    }
    if (i == 5) print "\n};\n"
    else print ",\n"
  }
  curr++
}

END {

}
