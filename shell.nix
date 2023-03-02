with import <nixpkgs> {};

stdenv.mkDerivation {
    name = "LilProg";

    buildInputs = [
      cargo
      gawk
      git
      inkscape
      rustc
    ];
}
