BEGIN {
  FS=""
}

{
  for (i=1; i<=NF; i++) printf "Character "i": " $i"\n"
}

END {

}
