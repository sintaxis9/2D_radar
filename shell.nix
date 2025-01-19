{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "radar-2D";

  buildInputs = [
    pkgs.gcc
    pkgs.pkg-config
    pkgs.sfml
  ];

  shellHook = ''
    export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:${pkgs.sfml}/lib/pkgconfig
    export CXX=g++
    export CC=gcc
  '';
}
