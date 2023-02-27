BEGIN {
  FS = ""
  ORS = ""
  count = 0
  curr = 0
  print 
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
  print "{\n"
  for (i=1; i<=5; i++) {
    print "  0b"
    for (j=0; j<=8; j++) {
      print b[i][j] 
    }
    if (curr == 5 && i == 5) print "\n};\n"
    else if (i == 5) print "\n},\n"
    else print ",\n"
  }
  curr++
}

END {

}
