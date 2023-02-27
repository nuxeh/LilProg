BEGIN {
  FS = ""
  zero = false
  bee = false
  count = 0
}

{
  for (i=1; i<=NF; i++) {
    if (count > 0) {
      print $i
      count--
    }
    if ($i == "0") zero = true
    else if (zero == true && $i == "b") {
      bee = true
      count = 5
    } 
    else {
      zero = false
      bee = false
      count = 0
    }
  }
}

END {

}
