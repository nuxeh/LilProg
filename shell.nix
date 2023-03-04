with import <nixpkgs> {};

stdenv.mkDerivation {
    name = "LilProg";

    nativeBuildInputs = [ rustPlatform.bindgenHook ];

    buildInputs = [
      cargo
      gawk
      git
      inkscape
      llvmPackages.libclang
      rustc
    ];

    #shellHook = ''
    #  export LIBCLANG_PATH="${pkgs.llvmPackages.libclang}/lib";
    #'';
}
