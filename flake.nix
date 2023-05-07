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
    mkOverlay = system: final: prev: {
      dwm = prev.dwm.overrideAttrs (old: {
        src = builtins.path {
          path = ./.;
          name = "dwm";
        };
        buildInputs =
          old.buildInputs
          ++ [
            prev.imlib2
          ];
      });
    };
  in
    flake-utils.lib.eachDefaultSystem (
      system: let
        overlay = mkOverlay system;
        pkgs = import nixpkgs {
          inherit system;
          overlays = [overlay];
        };
      in rec {
        apps = {
          dwm = {
            type = "app";
            program = "${defaultPackage}/bin/dwm";
          };
        };

        devShell = pkgs.mkShell {
          name = "dwm-dev";
          packages = with pkgs; [
            gcc
            pkgconfig
            imlib2
            xorg.libX11
            xorg.libXft
            xorg.libXinerama
          ];
        };

        packages.dwm = pkgs.dwm;
        defaultApp = apps.dwm;
        defaultPackage = packages.dwm;
        overlays.default = overlay;
      }
    );
}
