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
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [
            (final: prev: {
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
            })
          ];
        };

        overlay = final: prev: {
          dwm = prev.dwm;
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

        overlays = {
          default = overlay;
        };
      }
    );
}
