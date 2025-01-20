{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "radar-2D";
  buildInputs = [
    pkgs.gcc
    pkgs.pkg-config
    pkgs.sfml
  ];

  shellHook = ''
    echo "CompileFlags:" > .clangd
    echo "  Add:" >> .clangd
    echo "    - \"--std=c++17\"" >> .clangd
    echo "    - \"$(pkg-config --cflags-only-I sfml-graphics | sed 's/-I/--include-directory=/')\"" >> .clangd
    echo "    - \"$(pkg-config --libs-only-L sfml-graphics | sed 's/-L/--library-directory=/')\"" >> .clangd
    echo "Diagnostics:" >> .clangd
    echo "  MissingIncludes: Strict" >> .clangd
    echo "  UnusedIncludes: Strict" >> .clangd
  '';
}
