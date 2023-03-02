with import <nixpkgs> {};

stdenv.mkDerivation {
    name = "LilProg";

    buildInputs = [
      gawk
      rustc
      cargo
      inkscape
    ];
}
