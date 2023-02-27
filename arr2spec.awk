BEGIN {
  FS = ""
  ORS = ""
  last = ""
  count = 0
}

{
  for (i=1; i<=NF; i++) {
    if (count > 0) {
      print $i
    }
    if ($i == "b" && last == "0") {
      print "0b"
      count = 5
    } else if (count > 0) {
      count--
    }
    last = $i
  }
  print "\n"
}

END {

}
