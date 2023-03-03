BEGIN {
  FS = ""
  ORS = ""
  last = ""
  count = 0
  count2 = 0
  lastCount = 0
}

{
  for (i=1; i<=NF; i++) {
    lastCount = count
    if (count > 0) {
      if ($i == "0") { print "."; count2++ }
      else if ($i == "1") { print "#"; count2++ }
    }
    if ($i == "b" && last == "0") {
      count = 5
    } else if (count > 0) {
      count--
    }
    last = $i
    if (count == 0 && lastCount != 0) print "\n"
    if (count2 % (40) == 0 && lastCount != 0) print "\n"
  }
}

END {

}
