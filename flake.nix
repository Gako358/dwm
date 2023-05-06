{
  description = "MerrinX dwm build";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [
            (final: prev: {
              dwmMX = prev.dwm.overrideAttrs (oldAttrs: rec {
				src = builtins.path {
					path = ./.;
					name = "dwmMX";
				};
                buildInputs = 
					oldAttrs.buildInputs
					++ [
						prev.imlib2
					];
              });
            })
          ];
        };
      in
      rec {
        apps = {
          dwm = {
            type = "app";
            program = "${defaultPackage}/bin/st";
          };
        };

        packages.dwmMX = pkgs.dwmMX;
        defaultApp = apps.dwm;
        defaultPackage = pkgs.dwmMX;

        devShell = pkgs.mkShell {
          buildInputs = with pkgs; [ xorg.libX11 xorg.libXft xorg.libXinerama gcc pkgconfig imlib2 ];
        };
      }
    );
}
