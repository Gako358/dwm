{
  description = "MerrinX dwm build";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }: let
    overlay = final: prev: {
      dwm = prev.dwm.overrideAttrs (oldAttrs: rec {
        src = builtins.path {
          path = ./.;
          name = "dwm";
        };
        buildInputs =
          oldAttrs.buildInputs
          ++ [
            prev.imlib2
          ];
      });
    };
  in
    flake-utils.lib.eachDefaultSystem
    (
      system: let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [
            self.overlays.default
          ];
        };
      in rec {
        packages.dwm = pkgs.dwm;
        packages.default = pkgs.dwm;
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            gcc
            pkgconfig
            imlib2
            xorg.libX11
            xorg.libXft
            xorg.libXinerama
          ];
        };
      }
    )
    // {overlays.default = overlay;};
}
